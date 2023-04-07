# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

from enoTiledImg import *
import sys

WIDTH, HEIGHT=1920, 1080

#tmdn = 'rmUS1882a'
#tmdn = 'cuMap2'
tmdn = 'rmUS1882b'

eti = enoTiledImg()
#eti.imgPos = (-10000, 0)

eti.adjustWindowPlacement(WIDTH, HEIGHT)
eti.loadTmap(tmdn)

c1 = Actor("cursor01a", pos=(200, 200))

############### draw callback ###############

def draw():
  global eti, c1
  screen.clear()
  eti.draw(screen)
  c1.draw()

############### keypress callback ###############

def on_key_down(key):
  global eti
  nudge = 250

  if key is keys.LEFT:  eti.animImg(-nudge, 0); print(eti.imgPos)
  if key is keys.RIGHT: eti.animImg( nudge, 0); print(eti.imgPos)
  if key is keys.UP:    eti.animImg(0, -nudge)
  if key is keys.DOWN:  eti.animImg(0,  nudge)

############### mouse down callback ###############

mouseDown = False

def on_mouse_down(pos):
  global mouseDown
  mouseDown = True

def on_mouse_up():
  global mouseDown
  mouseDown = False

############### mouse move callback ###############

def on_mouse_move(rel):
  global eti, mouseDown

  if mouseDown: 
    dx, dy = rel
    x,  y  = eti.imgPos[0] + dx, eti.imgPos[1] + dy
    eti.imgPos = (x,y)
    print(rel, eti.imgPos)

############### update callback ###############

def update():
  global eti
  eti.animUpdateImg()

### end ###
