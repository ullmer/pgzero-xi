# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

import sys
sys.path.append('c:/git/pgzero-xi')

from enoContentResolver import *
from enoTiledImg        import *
from enoTiledImgNav     import *

WIDTH, HEIGHT=1920, 1080

#ecr = enoContentResolver(eyu)
#ecr = enoContentResolver()
#ecr.
#addrL = ecResolv.getFirstContentMatchLocal('SC')

eti    = enoTiledImg()
etinav = enoTiledImgNav(eti)
#eti.imgPos = (-10000, 0)
multiresLevel = 2
#multiresLevel = 1 

eti.adjustWindowPlacement(WIDTH, HEIGHT)
eti.loadTmap(tmdn, multiresLevel) #needs evolution
etinav.constructIndexGui()

############### draw callback ###############

def draw():
  global eti, c1
  screen.clear()
  eti.draw(screen) 
  etinav.draw(screen)

############### other interaction callbacks ###############

def on_key_down(key):   etinav.on_key_down(key)
def on_key_up(key):     etinav.on_key_up(key)
def on_mouse_down(pos): etinav.on_mouse_down(pos)
def on_mouse_move(rel, pos): etinav.on_mouse_move(rel, pos)
def on_mouse_up():      etinav.on_mouse_up()
def update():           etinav.update()

### end ###
