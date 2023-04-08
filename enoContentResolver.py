# Enodia content resolver
# Brygg Ullmer, Clemson University
# Begun 2023-04-06

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

import os, sys, math, traceback
import yaml, sqlite3
import urllib.request

from urllib.parse        import urlparse
from datetime            import *
from enoContentRetriever import *

#########################################################################
######################### Enodia Content Resolver #######################

class enoContentResolver:
  
  defaultDir    = 'resources'
  defaultYamlFn = 'index.yaml'
  defaultDb     = 'enoContent.db3'
  dbActivated   = False
  imageSuffixes = ['png']
  dbConn        = None
  dbCursor      = None
  lastLocalPath = None
  ecr           = None  #Enodia content retriever
  abbrevCountZPad  = 3 #zero-pad to N digits
  abbrevCountFirst = 1 #start abbreviation counts at this number

  defaultHost = 'enodia.computing.clemson.edu'
  defaultPath = 'tiled'

  hardcodedMappings = 
    {'enodia.computing.clemson.edu': 'ecce001'}

  ############################## constructor ##############################

  def __init__(self, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    #https://stackoverflow.com/questions/739625/setattr-with-kwargs-pythonic-or-not
    if self.dbActivated: self.loadContentDb3()
    if self.ecr is None: self.ecr = enoContentRetriever()

  ########################## load target content #########################
    
  def loadTargetContent(self, targetContent):
    path = self.mapUrl2Local(targetContent)
    self.layPath(path)

    yfn = '%s/%s' % (path, self.defaultYamlFn)
    if os.path.exists(yfn) is False:
      root, ext = os.path.splitext(yfn)
      if ext.lower() in self.imagesSuffixes: 
        result = self.retrieveImage(targetContent, yfn)
        return result
      elif targetContent.find(self.defaultYamlFn): yu = targetContent
      elif targetContent[-1] = '/': 
        yu = '%s/%s' % (targetContent, self.defaultYamlFn)

      urllib.request.urlretrieve(yu, yfn)

    self.loadYaml(ynf) # may require more contemplation

  ########################## load yaml #########################
    
  def loadYaml(self, yfn): pass

  ########################## makePath #########################
    
  def layPath(self, path): 
    if os.path.exists(path): return 

    progressivePath = None; tail = path
    while True:
      head, tail = os.path.split(tail)
      if head is None and tail is None: return #this may require more thought
      if progressivePath is None: progressivePath = head
      else: progressivePath += '/' + head
      if os.path.exists(progressivePath) is False:
        os.mkdir(progressivePath)

  ########################## map url 2 local #########################

  def mapUrl2Local(self, targetContent):
    # to accelerate onward movement, hardcoding for the moment
    o = urlparse(targetContent)
    netloc, path = o.netloc, o.path
    nlAbbrev = self.abbrevNetloc(netloc)

    path = '%s/%s/%s' % (self.defaultDir, nlAbbrev, path)
    self.lastLocalPath = path
    return path

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

  ########################## getAddressMap #########################
  # See if a row mapping the netloc address to a numbered abbreviation 
  # is present in the dbase
    
  def getDbAddressMap(self, netloc): 
    if self.dbCon == None or self.dbCursor == None: self.loadContentDb3()
    queryStr = '''select abbrev, abbrevCount from contentServerEntry
                    where fullAddress="%s";''' % netloc
    self.dbCursor.execute(queryStr)
    result = self.dbCursor.fetchone()
    return result

  ########################## construct db address #########################
    
  def constructDbAddress(self, netloc):
    firstLetters1 = ''
    els = netloc.split('.')
    for el in els:
      if len(el) > 0: firstLetters1.append(el[0])
    firstLetters2 = firstLetters1.lower()

    queryStr = '''select count from contentServerAbbrev
                    where abbrev="%s";''' % firstLetters2
    self.dbCursor.execute(queryStr)
    result = self.dbCursor.fetchone()

    if result is None:
      ac = self.abbrevCountFirst
      queryStr = '''insert into contentServerAbbrev (abbrev, count) 
                      values ("%s", %i);''' % (firstLetters2, ac)
      self.dbCursor.execute(queryStr)
      self.dbConn.commit()
    else: ac = result[0]

    return (firstLetters2, ac)

  ########################## abbrev netloc #########################
    
  def abbrevNetloc(self, netloc):
    # first, look in dbase to see if already existing

    if self.dbActivated is False:
      if netloc in self.hardcodedMappings:
        result = self.hardcodedMappings[netloc]
        return result
      else:
        self.logError("abbrevNetloc: db not activated, and hardedcoded" + \
                      "mappings do not include", netloc); return None

    result = self.getDbAddressMap()

    if result is None:
      result = self.constructDbAddress(netloc)
      if result is None:
        self.logError("abbrevNetloc: constructDbAddress fails on", netloc)
        return None

    abbrev, abbrevCount = result

    result = "%s%s" % (abbrev, str(abbrevCount).zfill(self.abbrevCountZPad)
    return result

  ########################## parse url #########################
    
  def parseUrl(self, targetContent):
    up       = urlparse(targetContent)
    netloc   = up.netloc
    nlAbbrev = self.abbrevNetloc(netloc)

#eyu = 'https://enodia.computing.clemson.edu/'
#ecr = enoContentResolver(eyu)


### end ###
