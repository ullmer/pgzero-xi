# Tiled image support library
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

import os, sys, math, traceback
import yaml, sqlite3
import urllib.request
from urllib.parse import urlparse
from datetime import *

#########################################################################
######################### Enodia Content Resolver #######################

class enoContentResolver:
  
  defaultDir = 'resources'
  defaultDb  = 'enoContent.db3'
  dbConn     = None
  dbCursor   = None

  ############################## constructor ##############################

  def __init__(self, targetContent, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    #https://stackoverflow.com/questions/739625/setattr-with-kwargs-pythonic-or-not

    self.loadTargetContent(targetContent)

  ########################## load content db3 #########################
    
  def loadContentDb3(self):
    try:
      fn = '%s/%s' % (self.defaultDir, self.defaultDb)
      if os.path.exists(fn) == False:
        self.logError("loadContentDb3: content resolution dbase " + \
                      "doesn't appear to exist"); sys.exit(-1)

      self.dbConn   = sqlite3.connect(fn)
      self.dbCursor = self.dbConn.cursor()
    except: traceback.print_exc()

  ########################## isAddressMapped #########################
  # See if a row mapping the netloc address to a numbered abbreviation 
  # is present in the dbase
    
  def isAddressMapped(self, netloc): 
    if self.dbCon == None or self.dbCursor == None: self.loadContentDb3()
    queryStr = '''select abbrev, abbrevCount from contentServerEntry
                    where fullAddress="%s";''' % netloc
    self.dbCursor.execute(queryStr)
    result = self.dbCursor.fetchone()
    return result

  ########################## abbrev netloc #########################
    
  def abbrevNetloc(self, netloc):
    # first, look in dbase to see if already existing
    # if so,  use
    # if not, see if abbrev already exists
    # if so,  increment count and return
    # if not, populate and return

    firstLetters1 = ''
    els = netloc.split('.')
    for el in els:
      if len(el) > 0: firstLetters1.append(el[0])
    firstLetters2 = firstLetters1.lower()
    return firstLetters2

  ########################## parse url #########################
    
  def parseUrl(self, targetContent):
    up       = urlparse(targetContent)
    netloc   = up.netloc
    nlAbbrev = self.abbrevNetloc(netloc)

  ########################## load target content #########################
    
  def loadTargetContent(self, targetContent):

#eyu = 'https://enodia.computing.clemson.edu/'
#ecr = enoContentResolver(eyu)

### end ###
