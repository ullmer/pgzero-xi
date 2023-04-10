# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

import sys, os
#print("%s" % __file__)
#sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '.')))
#sys.path.append('/cygdrive/c/git/pgzero-xi')
sys.path.append('c:/git/pgzero-xi')

from enoTiledImg    import *
from enoTiledImgNav import *

WIDTH, HEIGHT=1920, 1080

tmdn    = 'resources/ecce001/loc/maps/us/1975aL01'
#states1Fn = 'resources/usAnnot01a.txt'
states1Fn = 'usAnnot01a.txt'
states1F  = open(states1Fn, 'rt')
states1   = states1F.readlines()

eti    = enoTiledImg()
etinav = enoTiledImgNav(eti)
multiresLevel = 2
etinav.annotList(states1)

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
