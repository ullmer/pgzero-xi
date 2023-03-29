# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

from pgzero.builtins import Actor, animate, keyboard, keys, Rect
from enoTiledImg import *
import sys

############################################################# 
############### Enodia Tiled Image Navigation ###############
############################################################# 

class enoTiledImgNav:
  shiftPressed   = None
  cursorsPressed = None
  mouseDown      = None
  verbose        = True
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

  cursor1Fn           = "cursor01a"
  legendRightFn       = "legendright02"
  legendRightCursorFn = "legendcursor02"
  textboxFn           = "graybox01b"

  ############### constructor ###############
  
  def __init__(self, eti):
    self.eti            = eti
    self.shiftPressed   = False
    self.mouseDown      = False
    self.cursorsPressed = {}
    for k in self.cursorKeys:
      self.cursorsPressed[k] = False

    self.c1                = Actor(self.cursor1Fn,           pos=(200, 200))
    self.legendRight       = Actor(self.legendRightFn,       pos=(1680, 500))
    self.legendRightCursor = Actor(self.legendRightCursorFn, pos=(1680, 905))
    self.labelBg           = Actor(self.textboxFn,           topleft=(0,0))

  ############### draw callback ###############
  
  def draw(self, screen): 
    self.legendRight.draw()
    self.legendRightCursor.draw()
    self.labelBg.draw()

    #screen.draw.filled_rect(self.labelBgBox, self.labelBgBoxColor) #https://pygame-zero.readthedocs.io/en/stable/builtins.html

    #if self.labelTL is not None:
    #  draw.filled_rect(

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
  
  def on_mouse_down(self, pos): self.mouseDown = True
  def on_mouse_up(self):        self.mouseDown = False
  
  ############### mouse move callback ###############
  
  def on_mouse_move(self, rel):
    if self.mouseDown: 
      dx, dy = rel
      x,  y  = self.eti.imgPos[0] + dx, self.eti.imgPos[1] + dy
      self.eti.imgPos = (x,y)
      if self.verbose: print(rel, self.eti.imgPos)
  
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
  
  #def annotList(self, list):

### end ###
