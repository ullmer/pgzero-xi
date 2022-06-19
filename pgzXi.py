# PyGame Zero extensions toward supporting multitouch, additional sensors and actuators, ++
# Brygg Ullmer, Clemson University
# Begun 2022-06-16

import pgzero.spellcheck
import pgzero.game
import os

os.environ['SDL_MOUSE_TOUCH_EVENTS'] = '1'

pgzero.spellcheck.VALID_PARAMS['on_finger_down'] = \
  ['finger_id', 'x', 'y']

#  ['touch_id', 'finger_id', 'x', 'y', 'dx', 'dy']

import pgzrun, pygame
from   pgzero.game       import PGZeroGame

#https://pygame-zero.readthedocs.io/en/stable/ide-mode.html
#https://stackoverflow.com/questions/3692159/how-do-i-redefine-functions-in-python

################# PyGame Zero -- Extended Interaction ############
################################################################## 

class pgzXi:
  verbose = False
  pgzg    = None

  EVENT_HANDLERS_MT = {
    pygame.FINGERDOWN:   "on_finger_down",
    pygame.FINGERUP:     "on_finger_up",
    pygame.FINGERMOTION: "on_finger_move",
    pygame.MULTIGESTURE: "on_multigesture"}

  EVENT_HANDLERS_NFC   = {} #NFC handlers
  EVENT_HANDLERS_CAP   = {} #Capacitive sensing handlers
  EVENT_HANDLERS_LIDAR = {} #LIDAR handlers
  EVENT_HANDLERS_LED   = {} #LED ensemble handlers
  EVENT_HANDLERS_ACT   = {} #Actuator handlers

  EVENT_HANDLER_GENRES = \
    {'multitouch': EVENT_HANDLERS_MT,
     'nfc':        EVENT_HANDLERS_NFC,
     'cap':        EVENT_HANDLERS_CAP,
     'lidar':      EVENT_HANDLERS_LIDAR,
     'led':        EVENT_HANDLERS_LED,
     'act':        EVENT_HANDLERS_ACT}
 
  ############## constructor ############## 

  def __init__(self, eventHandlers): 
    self.activateEventHandlers(eventHandlers)

  ############## activateEventHandlers #########

  def activateEventHandlers(self, eventHandlers):
    for eh in eventHandlers: 
      if eh not in self.EVENT_HANDLER_GENRES:
        print("pgzXi:activateEvenHandlers: unknown event handler requested:", eh)
        continue
      else:
        ehd = self.EVENT_HANDLER_GENRES[eh] # event handler dictionary
        print("pgzXi activateEventHandlers:", eh, ehd)

  ############## go ############## 

  def go(self):
    pgzrun.run_mod = self.run_mod
    pgzrun.go()

  ############## PyGame Zero -- runner run_mod replacement #########

  def run_mod(self, mod, **kwargs):

    self.pgzg = PGZeroGame(mod, **kwargs)
   
    self.pgzg.EVENT_HANDLERS[pygame.FINGERDOWN]   = 'on_finger_down'
    self.pgzg.EVENT_HANDLERS[pygame.FINGERUP]     = 'on_finger_UP'
    self.pgzg.EVENT_HANDLERS[pygame.FINGERMOTION] = 'on_finger_move'
    self.pgzg.EVENT_HANDLERS[pygame.MULTIGESTURE] = 'on_multigesture'

    if self.verbose: 
      print("augmenting PyGame Zero event handlers:")
      print(self.pgzg.EVENT_HANDLERS)

    if self.verbose: 
      print("VALID_PARAMS")
      print(pgzero.spellcheck.VALID_PARAMS)

    self.pgzg.run()

### end ###
