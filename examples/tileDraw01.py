# Fragment/split an image into tiles (initially, 512x512)
# Brygg Ullmer, Clemson University
# Begun 2023-03-22

import sys
sys.path.append('c:/git/pgzero-xi')

from enoTiledImg import *

if len(sys.argv) < 2:
  print("Please provide image tilemap directory as argument"); sys.exit(-1)

timgDirFn = sys.argv[1]
eti = enoTiledImg()
#eti.imgPos = (-10, -10)
eti.textOnly = True
eti.loadTmap(timgDirFn)
eti.draw()

### end ###
