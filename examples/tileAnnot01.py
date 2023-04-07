# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

from enoTiledImg    import *
from enoTiledImgNav import *
import sys

WIDTH, HEIGHT=1920, 1080

tmdn    = 'resources/loc-sc1970'
cities1Fn = 'resources/scAnnot01a.txt'
cities1F  = open(cities1Fn, 'rt')
cities1   = cities1F.readlines()

#tmdn = 'rmUS1882a'
#tmdn = 'resources/cuMap2'
#tmdn = 'resources/loc-sc1876'
#tmdn = 'rmUS1882b'

eti    = enoTiledImg()
etinav = enoTiledImgNav(eti)
multiresLevel = 2
etinav.annotList(cities1)

#eti.imgPos = (-10000, 0)
#multiresLevel = 1 

eti.adjustWindowPlacement(WIDTH, HEIGHT)
eti.loadTmap(tmdn, multiresLevel)

############### draw callback ###############

def draw():
  global eti, c1
  screen.clear()
  eti.draw(screen) 
  etinav.draw(screen)

############### other interaction callbacks ###############

def update():           etinav.update()
def on_key_down(key):   etinav.on_key_down(key)
def on_key_up(key):     etinav.on_key_up(key)
def on_mouse_down(pos): etinav.on_mouse_down(pos)
def on_mouse_up():      etinav.on_mouse_up()
def on_mouse_move(rel, pos): etinav.on_mouse_move(rel, pos)

### end ###
