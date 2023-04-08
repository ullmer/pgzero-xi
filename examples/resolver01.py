#Test content retriever
#Brygg Ullmer, Clemson University
#https://enodia.computing.clemson.edu/tiled/loc/maps/sc/1970/1/tile00x00.png

from enoContentResolver import *

ecr     = enoContentResolver()
firstSC = ecr.getFirstRootYamlMatch('SC')
print(firstSC)

### end ###
