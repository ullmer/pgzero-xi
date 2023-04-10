# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

import sys; sys.path.append('c:/git/pgzero-xi')

from enoTiledImg    import *
from enoTiledImgNav import *

WIDTH, HEIGHT=1920, 1080

tmdn = 'resources/ecce001/edu/clemson/map02'

eti    = enoTiledImg()
etinav = enoTiledImgNav(eti)
#eti.imgPos = (-10000, 0)

eti.adjustWindowPlacement(WIDTH, HEIGHT)
eti.loadTmap(tmdn)

c1          = Actor("app_support/cursor01a", pos=(200, 200))
legendRight       = Actor("app_support/legendright02",  pos=(1680, 500))
legendRightCursor = Actor("app_support/legendcursor02", pos=(1680, 905))

############### draw callback ###############

def draw():
  global eti, c1
  screen.clear()
  eti.draw(screen)

  legendRight.draw()
  legendRightCursor.draw()
  #c1.draw()

############### other interaction callbacks ###############

def update():           etinav.update()

def on_key_down(key):   etinav.on_key_down(key)
def on_key_up(key):     etinav.on_key_up(key)
def on_mouse_down(pos): etinav.on_mouse_down(pos)
def on_mouse_up():      etinav.on_mouse_up()
def on_mouse_move(rel, pos): etinav.on_mouse_move(rel, pos)

### end ###
