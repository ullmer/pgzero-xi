#Test content retriever
#Brygg Ullmer, Clemson University
#https://enodia.computing.clemson.edu/tiled/loc/maps/sc/1970/1/tile00x00.png

from enoContentRetriever import *
from enoContentResolver  import *

ecrs = enoContentResolver()
ecrt = enoContentRetriever()

addr1 = ecrs.getFirstContentMatch('SC')
addrU = ecrs.getFirstContentMatchUrl('SC')
addrL = ecrs.getFirstContentMatchLocal('SC')

tprefix = '1/tile00x'

for i in range(20):
  url = '%s%s%02i.png' % (addrU, tprefix, i)
  fn  = '%s%s%02i.png' % (addrL, tprefix, i)
  print(url, fn)
  #ecr.retrieveContent(url, fn, ecr.printUrlLoaded)

#with ecr.executor:
#  ecr.awaitResults()  

print("done")

### end ###
