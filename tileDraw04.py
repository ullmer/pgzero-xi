# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

from enoTiledImg import *
import sys

WIDTH, HEIGHT=1920, 1080

tmdn = 'rmUS1882b'

eti = enoTiledImg()
#eti.imgPos = (-10, -10)

eti.adjustWindowPlacement(WIDTH, HEIGHT)
eti.loadTmap(tmdn)

def draw():
  global eti
  screen.clear()
  eti.draw(screen)

def on_key_down(key):
  global eti
  nudge = 250

  if key is keys.LEFT:  eti.animImg(-nudge, 0)
  if key is keys.RIGHT: eti.animImg( nudge, 0)
  if key is keys.UP:    eti.animImg(0, -nudge)
  if key is keys.DOWN:  eti.animImg(0,  nudge)

def update():
  global eti
  eti.animUpdateImg()

### end ###
