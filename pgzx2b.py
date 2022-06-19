# PyGame Zero extensions toward supporting multitouch, additional sensors and actuators, ++
# Brygg Ullmer, Clemson University
# Begun 2022-06-16

from pgzXi import *

WIDTH  = 800
HEIGHT = 600

touch_coords = {}
  
def normalizePos(x,y): return (int(x*WIDTH), int(y*HEIGHT))

################# on_finger_down ###################

def on_finger_down(finger_id, x, y):
  touch_coords[finger_id] = normalizePos(x,y)

################### on_finger_move ###################

def on_finger_move(finger_id, x, y):
  touch_coords[finger_id] = normalizePos(x,y)

################### on_finger_up ###################

def on_finger_up(finger_id, x, y):
  print("finger UP")

################### on_finger_up ###################

def on_mouse_up(pos):
  print("mouse UP")
  touch_coords.clear()

################### draw ###################

def draw():
  global touch_coords

  screen.clear()
  screen.draw.circle((400, 300), 30, 'white')

  for finger_id in touch_coords:
    pos = touch_coords[finger_id]
    screen.draw.circle(pos, 50, 'white')

################### draw ###################

pgzx = pgzXi(["multitouch"])
pgzx.go()

### end ###
