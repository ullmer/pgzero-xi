#Test content retriever
#Brygg Ullmer, Clemson University
#https://enodia.computing.clemson.edu/tiled/loc/maps/sc/1970/1/tile00x00.png

from enoContentRetriever import *
from enoContentResolver  import *

ecResolv = enoContentResolver()
ecRetr   = enoContentRetriever()

addr1 = ecResolv.getFirstContentMatch('SC')
addrU = ecResolv.getFirstContentMatchUrl('SC')
addrL = ecResolv.getFirstContentMatchLocal('SC')

tprefix = '1/tile00x'

for i in range(20):
  url = '%s%s%02i.png' % (addrU, tprefix, i)
  fn  = '%s%s%02i.png' % (addrL, tprefix, i)
  pn  = addrL + '1'
  #print(url, fn)
  ecResolv.layPath(pn)
  ecRetr.retrieveContent(url, fn, ecRetr.printUrlLoaded)

with ecRetr.executor:
  ecRetr.awaitResults()  

print("done")

### end ###
