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
  future_to_url = None

  ############################## constructor ##############################

  def __init__(self, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    self.buildThreadPool()

  ########################## build thread pool #########################
    
  def buildThreadPool(self):
    # https://docs.python.org/3.2/library/concurrent.futures.html
    self.executor = concurrent.futures.ThreadPoolExecutor(max_workers = \
      self.maxThreads)

    self.future_to_url = {}

  ########################## load url #########################
    
  def load_url(self, url, localFn):
    result = urllib.request.urlretrieve(url, localFn, timeout=self.timeout)

  ########################## retrieve content #########################
    
  def retrieveContent(self, url, localFn):
    future = self.executor.submit(self.load_url, url, localFn)
    self.future_to_url[future] = url

  ########################## check results #########################
    
  def checkResults(self):
    for future in concurrent.futures.as_completed(self.future_to_url):
      url = self.future_to_url[future]
      if future.exception() is not None:
        self.logError("checkResults returned an exception on", \
                      url, future.exception())
      else:
        return future.result()

### end ###
