# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

#https://pillow.readthedocs.io/en/stable/reference/Image.html

import os, sys, math, traceback
import yaml, PIL, pygame
from pgzero.builtins import Actor, animate, keyboard

from PIL import Image
from queue import *
from datetime import *

#########################################################################
############################## Enodia tiled image #######################

class enoTiledImg:

  PIL.Image.MAX_IMAGE_PIXELS = 21000 * 11000

  tileDim            = (512, 512)
  tilesPerSubdir     = 100
  decomposThresh     = 64
  filePrefix         = 'tile'
  imgType            = 'png'
  metadataFn         = 'metadata.yaml'
  cursorFns           = ["cursor01a", "cursor01b"]

  imgTileQueue       = None
  maxImgTilesQueued  = 200 # picking 100 out of thin air.  I've seen assertions that garbage collection will 
                           # auto-reclaim unreferenced pygame-loaded images.  This is an effort to cache but help
  imgTileCache       = None
  img2tileCoords     = None

  imgSrcFn, tmapDir  = None, None
  numTiles           = None
  tmapDirYaml        = None

  imgSrc     = None
  imgSize    = None
  imgPos     = None #top-left
  imgZoom    = None
  imgActor   = None
  screenDim  = (1920,1080)
  generated  = None
  animDuration = .4
  animTween    = 'accel_decel'
  textOnly     = False # print textual output only; no graphics
  animImgPlaceholder = 'placeholder'
  animationActive = None
  verbose         = False

  multiresLevel        = 1
  defaultMultiresLevel = 1
  multiresolution      = False

  features          = None
  featuresResLevel  = None
  featuresTags      = None

  tags, tagActors, tagSize = [None]*3
  tagActorGlobalPos = None
  tagActorScreenPos = None

  ############################## constructor ##############################

  def __init__(self):
    self.imgTileQueue    = Queue()
    self.imgTileCache    = {}
    self.img2tileCoords  = {}
    self.animationActive = False

    self.imgPos  = (0,0)
    self.imgZoom = 1.

  ############################## getDefaultCursorImgFn ##############################
  @classmethod
  def getDefaultCursorImgFn(cls):
    #self.c1  = Actor(self.cursorFns[1],        pos=(200, 200))

    return cls.cursorFns[1]

  ############################## shift image ##############################

  def shiftImg(self, dx, dy):
    if self.imgPos == None: return -1
    x = self.imgPos[0] + dx
    y = self.imgPos[1] + dy
    self.imgPos = (x,y)

  def moveImg(self, x, y):
    self.imgPos = (x,y)

  ############################## shift image ##############################

  def animationFinishedCB(self): self.animationActive = False

  ############################## shift image ##############################

  def animPrefatory(self):
    if self.imgActor == None: self.imgActor = Actor(self.animImgPlaceholder)
    if self.imgPos == None: return -1
    self.imgActor.pos = self.imgPos

  def animImg(self, dx, dy):
    self.animPrefatory()
    x = self.imgPos[0] + dx
    y = self.imgPos[1] + dy

    if self.verbose: print("animImg:", x,y,dx,dy)

    self.imgPos = (x,y)
    animate(self.imgActor, pos=self.imgPos, duration=self.animDuration, tween=self.animTween, 
            on_finished=self.animationFinishedCB)
    self.animationActive = True

  ############################## get mapped screen coords ##############################

  def getMappedScreenCoords(self): # return top-left and bottom-right "global" coordinates in pixel-space
    ix, iy   = self.imgPos
    sdx, sdy = self.screenDim
    result   = [ix, iy, ix+sdx, iy+sdy]
    return result

  ############################## get mapped screen coords ##############################

  def posWithinBounds(self, testpos, pixelbounds, pad=0): #pad helps with sample region
    x, y = testpos
    x1, y1, x2, y2 = pixelbounds 

    if (x + pad) < x1 or (x - pad) > x2: return False
    if (y + pad) < y1 or (y - pad) > y2: return False
    return True

  ############################## get mapped screen coords ##############################

  #def mapWithinBounds(self, testpos, pixelbounds): 

  ############################## anim top, bottom, left, right ##############################

  def animTop(self):
    self.animPrefatory()
    x, y = self.imgPos; y = 0
    self.imgPos = (x,y)
    animate(self.imgActor, pos=self.imgPos, duration=self.animDuration, tween=self.animTween,
            on_finished=self.animationFinishedCB)
    self.animationActive = True

  def animLeft(self):
    self.animPrefatory()
    x, y = self.imgPos; x = 0
    self.imgPos = (x,y)
    animate(self.imgActor, pos=self.imgPos, duration=self.animDuration, tween=self.animTween,
            on_finished=self.animationFinishedCB)
    self.animationActive = True

  def animRight(self):
    self.animPrefatory()
    isx = self.getImageSize()[0]
    x, y = self.imgPos; x = self.screenDim[0] - isx
    self.imgPos = (x,y)
    animate(self.imgActor, pos=self.imgPos, duration=self.animDuration, tween=self.animTween,
            on_finished=self.animationFinishedCB)
    self.animationActive = True

  def animBottom(self):
    self.animPrefatory()
    isy = self.getImageSize()[1]
    x, y = self.imgPos; y = self.screenDim[1] - isy
    self.imgPos = (x,y)
    animate(self.imgActor, pos=self.imgPos, duration=self.animDuration, tween=self.animTween,
            on_finished=self.animationFinishedCB)
    self.animationActive = True

  ############################## imageSize ##############################

  def getImageSize(self):
    if self.multiresolution == False: return self.imgSize
    mrlevel = self.multiresLevel
    if mrlevel in self.imgSize:
      imgsize    = self.imgSize[mrlevel]  #error handling needed
      return imgsize

    print("enoTiledImg getImageSize error: multiresolution=True, and error with self.imgSize:", self.imgSize)
    return None

  ############################## shift image ##############################

  def animUpdateImg(self):
    if self.imgActor == None: return
    x, y = self.imgActor.pos
    self.moveImg(x, y)

  ############################## adjust window placement ##############################

  def adjustWindowPlacement(self, width, height):
    #magic for placing at 0,0
    import platform, pygame
    if platform.system() == "Windows":
      from ctypes import windll
      hwnd = pygame.display.get_wm_info()['window']
      windll.user32.MoveWindow(hwnd, 0, 0, width, height, False)

  ############################## get number of tiles queued ##############################

  def numTilesQueued(self):
    if self.imgTileQueue == None:
      print("enoTiledImg numTilesQueued error: called for empty queue!")
      sys.exit(-1)

    result = self.imgTileQueue.qsize()
    return result

  ############################## generate tile filename ##############################

  def genTileFn(self, xt, yt, multiresLevel=1):
    fn     = '%s/%i/tile%02ix%02i.%s' % (self.tmapDir, multiresLevel, xt, yt, self.imgType) 
    return fn 

  ############################## generate tile directory name ##############################

  def genTileDn(self, xt, yt, multiresLevel=1):  # create directory if it doesn't already exist
    dn = '%s/%i' % (self.tmapDir, multiresLevel)
    if not os.path.isdir(dn): os.mkdir(dn)
    return dn

  ############################## load tile ##############################

  def tileLoaded(self, xt, yt, multiresLevel=1):  
    if xt not in self.imgTileCache:     return False
    if yt not in self.imgTileCache[xt]: return False
    return True

  ############################## load tile ##############################

  def loadTmap(self, tmapDir, multiresLevel=1):
    self.tmapDir = tmapDir
    yfn = '%s/%s' % (tmapDir, self.metadataFn)
    yf  = open(yfn)
    y   = self.tmapDirYaml = yaml.safe_load(yf)
    self.imgSrcFn  = y['origImgFn']
    self.imgSize   = y['imgSize']
    self.tileSize  = y['tileSize']
    self.numTiles  = y['numTiles']
    self.generated = y['generated']
    self.generated = y['generated']

    if 'multiresolution' in y:      self.multiresolution =      y['multiresolution']
    if 'defaultMultiresLevel' in y: 
       self.defaultMultiresLevel = y['defaultMultiresLevel']
       #self.multiresLevel = self.defaultMultiresLevel

    self.multiresLevel = multiresLevel

    if 'features' in y: 
      f = self.features = y['features']
      if 'multiresLevel' in f: self.featuresResLevel = f['multiresLevel']
      if 'tags' in f:          
        self.featuresTags      = f['tags']
        self.buildTagActors()

    yf.close()

  ############################## load tile ##############################

  def buildTagActors(self):
    if self.featuresTags == None:
      self.logError("buildTagActors error: featuresTags is empty")
      return None

    self.tags              = []
    self.tagActors         = {}
    self.tagSize           = {}
    self.tagActorGlobalPos = {}
    self.tagActorScreenPos = {}
    try:
      for tag in self.featuresTags:
        self.tags.append(tag)
        coords = self.featuresTags[tag]
        self.tagActorGlobalPos[tag] = coords

        cfn = self.getDefaultCursorImgFn()
        a = self.tagActors[tag] = Actor(cfn)
        self.tagSize[tag] = a.size

    except: traceback.print_exc()

  ############################## load tile ##############################

  def getTile(self, xt, yt, multiresLevel=1):  
    if self.imgTileCache == None:       return -1
    if xt not in self.imgTileCache or yt not in self.imgTileCache[xt]: 
      self.loadTile(xt, yt, multiresLevel)
    result = self.imgTileCache[xt][yt]
    return result

  ############################## load tile ##############################

  def loadTile(self, xt, yt, multiresLevel=1):  
    if self.imgTileCache == None:       return -1
    if xt not in self.imgTileCache:     self.imgTileCache[xt] = {}
    if yt not in self.imgTileCache[xt]: 
      fn         = self.genTileFn(xt, yt, multiresLevel)
      if self.verbose: print("loadTile", xt, yt, fn)
      if os.path.exists(fn): imgSurface = pygame.image.load(fn)
      else: imgSurface = None

      self.imgTileCache[xt][yt] = imgSurface
      self.imgTileQueue.put(imgSurface)
      self.img2tileCoords[imgSurface] = (xt, yt)

  ########################### unref tile (to allow for garbage collection) #######################

  def dequeueOldestImage(self):
    #print("dequeue called; ignoring"); return
    print("dequeing an image")
    if self.imgTileQueue == None:
       print("enoTiledImg unrefImgQueue error: unref called for empty queue!")
       sys.exit(-1)

    imgSurf = self.imgTileQueue.get() #retrieve from the queue
    if imgSurf not in self.img2tileCoords:
      print("enoTiledImg unrefImgQueue error: unref queue yields unreferenced image")
      sys.exit(-1)

    #if (xt not in imgTileCache) or (yt not in imgTileCache[xt]): return -1
    xt, yt = self.img2tileCoords[imgSurf]
    #self.img2tileCoords[imgSurf].pop()
    self.img2tileCoords.pop(imgSurf)
    #self.imgTileCache[xt][yt].pop()
    self.imgTileCache[xt].pop(yt)
    del imgSurf
    return True

  ############################## draw ##############################

  def draw(self, screen=None):
    tdx, tdy = self.tileDim
    sdx, sdy = self.screenDim

    ix, iy = int(self.imgPos[0]), int(self.imgPos[1])
    mx, my = ix % tdx, iy % tdy
    tx, ty = -int(math.ceil(ix/tdx)), -int(math.ceil(iy/tdy))

    xtilesToDisplay = math.ceil((sdx+mx)/tdx)
    ytilesToDisplay = math.ceil((sdy+my)/tdy)

    sx, sy = ix + tx*tdx, iy + ty*tdy; sx0=sx

    if self.verbose: print("draw", ix, iy, mx, my, "T", tx, ty, sx, sy, xtilesToDisplay, ytilesToDisplay)

    #sx, sy = ix - tx*tdx, iy - ty*tdy; sx0=sx
    #sx, sy = ix, iy; sx0=sx
    mrlevel = self.multiresLevel

    for yt in range(ytilesToDisplay):
      for xt in range(xtilesToDisplay):
        self.drawTile(screen, sx, sy, xt+tx, yt+ty, mrlevel); sx += tdx
      sy += tdy; sx = sx0

  ############################## drawTags ##############################

  def drawTags(self, screen): 
    # tagHash = getTags()
    tagHash = self.tags.keys()

    msc = self.getMappedScreenCoords()
    for tag in tagHash:
      globalTagCoords = self.tagActorGlobalPos[tag]
      size         = self.tagSize[tag]
      pad          = size[0]/2 #initially assume square size; should eventually be refined
      
      if self.posWithinBounds(globalTagCoords, msc, pad):
        print(".")

  ############################## draw tile ##############################

  def drawTile(self, screen, x, y, xt, yt, multiresLevel=1):  
    #if self.textOnly: print("drawTile:", x, y, xt, yt); return
    if self.verbose: print("drawTile:", x, y, xt, yt)
    if not self.tileLoaded(xt, yt):
      if  self.numTilesQueued() >= self.maxImgTilesQueued:  
        self.dequeueOldestImage()
        self.loadTile(xt, yt, multiresLevel)
    imgSurf = self.getTile(xt, yt, multiresLevel)
    if imgSurf is not None: screen.blit(imgSurf, (x,y))  #FOO

  ############################## draw tiles ##############################

  def drawTiles(self, x, y, xt1, yt1, xt2, yt2, multiresLevel=1): 
    for xt in range(xt1, xt2):
      for yt in range(yt1, yt2):
        dx, dy = (xt-xt1) * self.tileDim[0], (yt-yt1) * self.tileDim[1]
        x1, y1 = x+dx, y+dy
        self.drawTile(x1, y1, xt, yt, multiresLevel)

  ############################## generate tile coordinates ##############################

  def genTileCoords(self, xt, yt, multiresLevel=1): #decomposition level not yet accounted
    x1, y1 = xt * self.tileDim[0], yt * self.tileDim[1]
    x2, y2 = x1 + self.tileDim[0], y1 + self.tileDim[1]
    return (x1, y1, x2, y2)

  ############################## generate tile coordinates ##############################

  def extractTile(self, xt, yt, multiresLevel=1):
    tileCoords = self.genTileCoords(xt, yt, multiresLevel)
    im_crop = self.imgSrc.crop(tileCoords)

    dn     = self.genTileDn(xt, yt, multiresLevel) #create directory if it doesn't already exist
    tileFn = self.genTileFn(xt, yt, multiresLevel)
    print("saving", tileFn)
    im_crop.save(tileFn)
    im_crop.close()

  ############################## animation running ##############################

  def animationRunning(self): return self.animationActive

  ############################## load image ##############################

  def decomposImage(self, imgSrcFn, tmapDir):
    self.imgSrcFn  = imgSrcFn
    self.tmapDir = tmapDir
    self.imgSrc    = Image.open(self.imgSrcFn)
    self.imgSize   = self.imgSrc.size
    xdim, ydim     = self.imgSize

    print("decompos image, size", self.imgSize)

    nxt = int(xdim/self.tileDim[0])
    if xdim % nxt != 0: nxt += 1
   
    nyt = int(ydim/self.tileDim[1])
    if ydim % nyt != 0: nyt += 1

    self.numTiles = (nxt, nyt)

    if not os.path.isdir(self.tmapDir): os.mkdir(self.tmapDir)
    mdfn = '%s/%s' % (self.tmapDir, self.metadataFn)
    mdf  = open(mdfn, 'wt')

    ix, iy   = self.imgSize
    tdx, tdy = self.tileDim
    outstr = 'origImgFn:  ' + self.imgSrcFn + '\n';      mdf.write(outstr)
    outstr = 'imgSize:    [%i,%i]\n' % (ix,iy);          mdf.write(outstr)
    outstr = 'tileSize:   [%i,%i]\n' % (tdx,tdy);        mdf.write(outstr)
    outstr = 'numTiles:   ' + str(self.numTiles) + '\n'; mdf.write(outstr)
    outstr = 'generated:  %s\n' % date.today();          mdf.write(outstr)
    mdf.close()

    for xt in range(nxt):
      for yt in range(nyt):
        self.extractTile(xt, yt, 1)

    self.imgSrc.close()

### end ###
