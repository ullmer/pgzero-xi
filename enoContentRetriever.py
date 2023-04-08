# Enodia content retriever
# Brygg Ullmer, Clemson University
# Begun 2023-04-06

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

import os, sys, math, traceback
import concurrent.futures
import urllib.request
from urllib.parse import urlparse

#########################################################################
######################### Enodia Content Resolver #######################

class enoContentRetriever:
  
  maxThreads    = 5 
  timeout       = 60
  executor      = None
  futureToUrl   = None
  urlToLocalFn  = None
  urlDlActive   = None
  urlDlComplete = None
  urlDlNewlyComplete   = None
  urlDlNewlyCompleteCB = None

  ############################## constructor ##############################

  def __init__(self, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    self.buildThreadPool()

  ########################## build thread pool #########################
    
  def buildThreadPool(self):
    # https://docs.python.org/3.2/library/concurrent.futures.html
    self.executor = concurrent.futures.ThreadPoolExecutor(max_workers = \
      self.maxThreads)

    self.futureToUrl   = {}
    self.urlToLocalFn  = {}
    self.urlDlActive   = {}
    self.urlDlComplete = {}
    self.urlDlNewlyComplete   = {}
    self.urlDlNewlyCompleteCB = {}

  ########################## load url #########################
    
  def load_url(self, url, localFn):
    result = urllib.request.urlretrieve(url, localFn, timeout=self.timeout)

  ########################## load url #########################
    
  def logError(self, errMsg):
    print("enoContentRetriever error:", errMsg)

  ########################## load url #########################
    
  def clearNewlyCompleteURL(self, url):
    if url in self.urlDlNewlyComplete:
      self.urlDlNewlyComplete[url] = False

  ########################## printUrlLoaded#########################
    
  def printUrlLoaded(self, url):
    print("URL loaded:", url)

  ########################## retrieve content #########################
    
  def retrieveContent(self, url, localFn, whenCompleteCB=None):
    self.urlToLocalFn[url]  = localFn
    self.urlDlActive[url]   = True
    self.urlDlComplete[url] = False
    self.urlDlNewlyComplete[url]   = False
    self.urlDlNewlyCompleteCB[url] = whenCompleteCB
    future = self.executor.submit(self.load_url, url, localFn)
    self.futureToUrl[future] = url

  ########################## check results #########################
    
  def checkResults(self):
    newlyCompleteDLs = []
    for future in concurrent.futures.as_completed(self.futureToUrl):
      url = self.futureToUrl[future]
      self.urlDlActive[url]        = False
      self.urlDlComplete[url]      = True
      self.urlDlNewlyComplete[url] = True
      if self.urlDlNewlyCompleteCB[url] is not None:
        self.urlDlNewlyCompleteCB[url](url)
      newlyCompleteDLs.append(url)

      if future.exception() is not None:
        self.logError("checkResults returned an exception on", \
                      url, future.exception())

    return newlyCompleteDLs 

### end ###
