#Test content retriever
#Brygg Ullmer, Clemson University
#https://enodia.computing.clemson.edu/tiled/loc/maps/sc/1970/1/tile00x00.png

from enoContentResolver import *

ecr     = enoContentResolver()
addr1 = ecr.getFirstContentMatch('SC')
addr2 = ecr.getFirstContentMatchUrl('SC')
print(addr1)
print(addr2)

### end ###
