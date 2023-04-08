# Enodia content retriever
# Brygg Ullmer, Clemson University
# Begun 2023-04-06

# SPDX-FileCopyrightText: © 2023 Brygg Ullmer, Clemson University
# SPDX-License-Identifier: LGPL3
# This work supported in part by NSF "Enodia" MRI CNS-1828611

import os, sys, math, traceback
import urllib.request
from urllib.parse import urlparse

#########################################################################
######################### Enodia Content Resolver #######################

class enoContentRetriever:
  
  maxThreads    = 5 
  executor      = None
  future_to_url = None

  ############################## constructor ##############################

  def __init__(self, **kwargs):
    self.__dict__.update(kwargs) #allow class fields to be passed in constructor
    self.buildThreadPool()

  ########################## build thread pool #########################
    
  def buildThreadPool(self):
    # https://docs.python.org/3.2/library/concurrent.futures.html

### end ###
