# Enodia "spun video" support library
# Brygg Ullmer, Clemson University
# Begun 2023-04-08
# Use toward behaviors resemblant of Quicktime VR

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

#https://pillow.readthedocs.io/en/stable/reference/Image.html

import os, sys, math, traceback
import numpy as np
import cv2
import yaml

from PIL import Image, ImageFont, ImageDraw
from queue import *
from datetime import *

#draws from https://gist.github.com/vereperrot/dd2263e220e68555d687f2ed2075d590
# by vereperrot@github

#########################################################################
############################## Enodia tiled image #######################

class enoSpunImage:

  frameDim           = (512, 512)
  decomposThresh     = 64

  frameQueue      = None
  maxImgssQueued  = 100 # picking 100 out of thin air.  I've seen assertions 
                        # that garbage collection will auto-reclaim 
                        # unreferenced pygame-loaded images.  This is 
                        # an effort to cache but help
  frameCache      = None

  vidSrcFn        = None
  numFrames       = None
  vcap            = None

  currentFrameIdx = None 
  lastFrameIdx    = None 

  screenDim    = (1920,1080)
  generated    = None
  animDuration = .4
  animTween    = 'accel_decel'
  textOnly     = False # print textual output only; no graphics
  animImgPlaceholder = 'app_support/placeholder'
  animationActive = None
  verbose         = False

  ############################## constructor ##############################

  def __init__(self, enoSpunVidFn, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    #https://stackoverflow.com/questions/739625/setattr-with-kwargs-pythonic-or-not

    self.loadSpunVid(enoSpunVidFn)

  ############################## load tile ##############################
  def loadSpunVid(self, spunVidFn, targetFrameIdx=1):
    self.vidSrcFn = spunVidFn
    self.vcap = cv2.VideoCapture(spunVidFn)

    self.currentFrameIdx = targetFrameIdx
    self.vcap.set(1, targetFrameIdx)
    ret, frame = self.vcap.read()

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

  ####################### unref tile (to allow for garbage collection) #######

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
    self.img2tileCoords.pop(imgSurf)
    self.imgTileCache[xt].pop(yt)
    del imgSurf
    return True

### end ###
