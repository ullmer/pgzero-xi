# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

from pgzero.builtins import Actor, animate, keyboard, keys, Rect
from enoTiledImg import *

import sys, traceback, yaml

############################################################# 
############### Enodia Tiled Image Navigation ###############
############################################################# 

class enoTiledImgNav:
  verbose        = False

  shiftPressed   = None
  cursorsPressed = None
  mouseDown      = None
  cursorKeys     = ['L', 'R', 'U', 'D']
  bignudge       = 768
  smallnudge     = 50
  eti            = None
  legendRight       = None
  legendRightCursor = None
  c1                = None

  annotationList    = None
  annotationCoords  = None
  labelTL           = None
  labelBg           = None
  labelBgBox        = Rect((0, 0), (300, 75))
  labelBgBoxColor   = 70, 70, 70, 50

  cursorFns           = ["cursor01a", "cursor01b"]
  legendRightFn       = "legendright02"
  legendRightCursorFn = "legendcursor02"
  textboxFn           = "graybox01b"

  textlist            = None
  textlistIdx         = None

  #textlist            = ['Clemson']
  #textlistIdx         = 0

  textpos             = (5,5)
  textcolor           = "white"
  textsize            = 36

  indexFn   = "resources/index.yaml"
  indexY    = None
  indexImgs = None

  ############### constructor ###############
  
  def __init__(self, eti):
    self.eti            = eti
    self.shiftPressed   = False
    self.mouseDown      = False
    self.cursorsPressed = {}
    for k in self.cursorKeys:
      self.cursorsPressed[k] = False

    self.c1                = Actor(self.cursorFns[1],        pos=(200, 200))
    self.legendRight       = Actor(self.legendRightFn,       pos=(1680, 500))
    self.legendRightCursor = Actor(self.legendRightCursorFn, pos=(1680, 905))
    self.labelBg           = Actor(self.textboxFn,           topleft=(0,0))

  ############### load indedx ###############
  
  def loadIndex(self, indexFn = None):
    if indexFn is not None: self.indexFn = indexFn

    try:
      f = open(self.indexFn, 'rt')
      y = self.indexY = yaml.safe_load(f)
      if 'images' in y:
        self.indexImgs = y['images']
      else:
        self.logErrorMsg("loadIndex: 'images:' not in", self.indexFn);

    except: traceback.print_exc()

  ############### draw callback ###############
  
  def draw(self, screen): 
    self.legendRight.draw()
    self.legendRightCursor.draw()
    self.c1.draw()

    #screen.draw.filled_rect(self.labelBgBox, self.labelBgBoxColor) #https://pygame-zero.readthedocs.io/en/stable/builtins.html

    #if self.labelTL is not None:
    #  draw.filled_rect(
    if self.textlistIdx != None and self.textlist != None:
      self.labelBg.draw()
      txt = self.textlist[self.textlistIdx].rstrip() # remove possible trailing newline from readlines/etc.
      screen.draw.text(txt, topleft=self.textpos, color=self.textcolor, fontsize=self.textsize)

  ############### is cursor pressed ###############
  
  def isCursorPressed(self): 
    for k in self.cursorKeys:
      if self.cursorsPressed[k]: return True
    return False
  
  ############### keypress callback ###############
  
  def on_key_down(self, key):
   
    if key == keys.LSHIFT or key == keys.RSHIFT:
      self.shiftPressed = True
  
    if self.shiftPressed:
      nudge = self.smallnudge
      if key is keys.LEFT:  self.eti.shiftImg(-nudge, 0); self.cursorsPressed['L'] = True
      if key is keys.RIGHT: self.eti.shiftImg( nudge, 0); self.cursorsPressed['R'] = True
      if key is keys.UP:    self.eti.shiftImg(0, -nudge); self.cursorsPressed['U'] = True
      if key is keys.DOWN:  self.eti.shiftImg(0,  nudge); self.cursorsPressed['D'] = True
    else:
      nudge = self.bignudge
      if key is keys.LEFT:  self.eti.animImg(-nudge, 0);  self.cursorsPressed['L'] = True
      if key is keys.RIGHT: self.eti.animImg( nudge, 0);  self.cursorsPressed['R'] = True
      if key is keys.UP:    self.eti.animImg(0, -nudge);  self.cursorsPressed['U'] = True
      if key is keys.DOWN:  self.eti.animImg(0,  nudge);  self.cursorsPressed['D'] = True

    if key == keys.T: self.eti.animTop()
    if key == keys.B: self.eti.animBottom()
    if key == keys.L: self.eti.animLeft()
    if key == keys.R: self.eti.animRight()
  
  ############### key release callback ###############
  
  def on_key_up(self, key):
    if key == keys.LSHIFT or key == keys.RSHIFT:
      self.shiftPressed = False
  
    if key is keys.LEFT:  self.cursorsPressed['L'] = False
    if key is keys.RIGHT: self.cursorsPressed['R'] = False
    if key is keys.UP:    self.cursorsPressed['U'] = False
    if key is keys.DOWN:  self.cursorsPressed['D'] = False
  
  ############### mouse down callback ###############
  
  def on_mouse_down(self, pos): 
    if self.shiftPressed: self.mouseDown = True #pan
    else:
      self.recordCoord(pos)
      self.annotNext()

  def on_mouse_up(self):        self.mouseDown = False
  
  ############### mouse move callback ###############
  
  def on_mouse_move(self, rel, pos):
    if self.mouseDown: 
      dx, dy = rel
      x,  y  = self.eti.imgPos[0] + dx, self.eti.imgPos[1] + dy
      self.eti.imgPos = (x,y)
      if self.verbose: print(rel, self.eti.imgPos)
    else:
      self.c1.pos=pos 

  ############### update callback ###############
  
  def update(self):
    nudge = self.smallnudge

    if self.eti.animationRunning(): self.eti.animUpdateImg() #if animation underway

    if self.isCursorPressed() and self.shiftPressed: 
      if self.cursorsPressed['L']: self.eti.shiftImg(-nudge, 0)
      if self.cursorsPressed['R']: self.eti.shiftImg( nudge, 0)
      if self.cursorsPressed['U']: self.eti.shiftImg(0, -nudge)
      if self.cursorsPressed['D']: self.eti.shiftImg(0,  nudge)
  
  ############### annotList ###############
  
  
  def annotList(self, list):
    self.textlist    = list
    self.textlistIdx = 0 

  ############### annotNext ###############
  
  def annotNext(self):
    if self.textlist is not None and self.textlistIdx is not None:
      numAnnots = len(self.textlist)
      self.textlistIdx += 1
      if self.textlistIdx > numAnnots: self.annotComplete()
    
  ############### annotComplete ###############
  
  def annotComplete(self): return None

  def recordCoord(self, pos):
     ipx, ipy = self.eti.imgPos
     px, py   = pos
     x,  y    = px - ipx, py - ipy
     if self.textlist is not None and self.textlistIdx is not None:
       txt = self.textlist[self.textlistIdx].rstrip() # remove possible trailing newline from readlines/etc.
       #print("recordCoord:", txt, self.eti.imgPos, pos, ":", x, y)
       print("  %s: [%i, %i]" % (txt, x, y))

### end ###
