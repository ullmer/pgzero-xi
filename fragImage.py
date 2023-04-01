# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

from enoTiledImg import *
import sys

if len(sys.argv) < 3:
  print("Please provide image source filename and target directory as arguments"); sys.exit(-1)

imgSrcFn, dirTargFn = sys.argv[1:3]
eti = enoTiledImg()
eti.decomposImage(imgSrcFn, dirTargFn)

### end ###
