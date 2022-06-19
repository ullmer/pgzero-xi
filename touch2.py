# PyGame Zero-Xi class-based example of simple multitouch
# Brygg Ullmer, Clemson University
# Begun 2022-06-16

# Here, the class adds extra lines; but it illustrates a path for
#  more cleanly adding state 

from pgzXi import *

WIDTH  = 800
HEIGHT = 600

class Mt: #simple multitouch class
  touch_coords = {} # dictionary with coordinates of active touches
  
  def normalizePos(self, x, y): return (int(x*WIDTH), int(y*HEIGHT))

  def on_finger_down(self, finger_id, x, y):
    self.touch_coords[finger_id] = self.normalizePos(x,y)

  def on_finger_move(self, finger_id, x, y):
    self.touch_coords[finger_id] = self.normalizePos(x,y)

  def on_mouse_up(self, pos):
    self.touch_coords.clear()

  def draw(self):
    screen.clear()
    screen.draw.circle((400, 300), 30, 'white')

    for finger_id in self.touch_coords:
      pos = self.touch_coords[finger_id]
      screen.draw.circle(pos, 50, 'white')

################### draw ###################

pgzx = pgzXi(["multitouch"])
mt = Mt()

def on_finger_down(finger_id, x, y): 
  mt.on_finger_down(finger_id, x, y)

def on_finger_move(finger_id, x, y): 
  mt.on_finger_move(finger_id, x, y)

def on_mouse_up(pos):          mt.on_mouse_up(pos)
def draw():                    mt.draw()

pgzx.go()

### end ###
