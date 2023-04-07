# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

import os, sys, math, traceback
import yaml, PIL, pygame
import urllib.request
from datetime import *

#########################################################################
############################## Enodia tiled image #######################

class enoTiledImg:

  ############################## constructor ##############################

  def __init__(self, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    #https://stackoverflow.com/questions/739625/setattr-with-kwargs-pythonic-or-not

eyu = 'https://enodia.computing.clemson.edu/'
ecr = enoContentResolver(eyu)

### end ###
