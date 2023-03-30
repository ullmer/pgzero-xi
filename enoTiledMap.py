# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

#https://pillow.readthedocs.io/en/stable/reference/Image.html

from enoTiledImg import *

import os, sys, math
import yaml, PIL, pygame
from pgzero.builtins import Actor, animate, keyboard

from PIL import Image
from queue import *
from datetime import *

#########################################################################
############################## Enodia tiled image #######################

class enoTiledMap(enoTiledImg):

  ############################## constructor ##############################

  def __init__(self):
    super().__init__(x)

  ############################## draw ##############################

  def draw(self, screen=None):
    super().draw(screen)

### end ###
