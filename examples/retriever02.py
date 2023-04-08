#Test content retriever
#Brygg Ullmer, Clemson University
#https://enodia.computing.clemson.edu/tiled/loc/maps/sc/1970/1/tile00x00.png

from enoContentRetriever import *
from enoContentResolver  import *

ecrs = enoContentResolver()
ecrt = enoContentRetriever()

firstSC = ecrs.getFirstRootYamlMatchUrl('SC')

baseUrl = 'https://enodia.computing.clemson.edu/tiled/loc/maps/sc/1970/1/tile00x'

for i in range(20):
  url = '%s%02i.png' % (baseUrl, i)
  fn  = 'tmp/%02i.png' % i
  print(url, fn)
  ecr.retrieveContent(url, fn, ecr.printUrlLoaded)

with ecr.executor:
  ecr.awaitResults()  

print("done")

### end ###
