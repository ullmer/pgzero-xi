# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

import os, sys, math, traceback
import yaml, sqlite3
import urllib.request
from datetime import *

#########################################################################
######################### Enodia Content Resolver #######################

class enoContentResolver:
  
  defaultDir = 'resources'
  defaultDb  = 'enoContent.db3'
  dbCon      = None

  ############################## constructor ##############################

  def __init__(self, targetContent, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    #https://stackoverflow.com/questions/739625/setattr-with-kwargs-pythonic-or-not

    self.loadTargetContent(targetContent)

  ########################## load content db3 #########################
    
  def loadContentDb3(self):
    fn = '%s/%s' % (self.defaultDir, self.defaultDb)
    if os.path.exists(fn) == False:
      self.logError("loadContentDb3: content resolution dbase doesn't appear to exist"); sys.exit(-1)

    self.dbCon = sqlite3.connect(fn)

  ########################## load target content #########################
    
  def loadTargetContent(self, targetContent):

#eyu = 'https://enodia.computing.clemson.edu/'
#ecr = enoContentResolver(eyu)

### end ###
