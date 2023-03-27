# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

from enoTiledImg import *
import sys

WIDTH, HEIGHT=1920, 1080

tmdn = 'rmUS1882a'

eti = enoTiledImg()
#eti.imgPos = (-10, -10)

eti.adjustWindowPlacement(WIDTH, HEIGHT)
eti.loadTmap(tmdn)

def draw():
  global eti
  eti.draw(screen)

### end ###
