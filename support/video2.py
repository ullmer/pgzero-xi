# https://stackoverflow.com/questions/21356439/how-to-load-and-play-a-video-in-pygame

import cv2
import pygame

#cap = cv2.VideoCapture('video.mp4')
cap = cv2.VideoCapture('test2.mp4')
#cap = cv2.VideoCapture('test.mp4')
success, img = cap.read()
shape = img.shape[1::-1]
wn = pygame.display.set_mode(shape)
clock = pygame.time.Clock()

frameIdx = 1
frameCache = {}

while success:
  #clock.tick(60)
  clock.tick(10)

  if frameIdx in frameCache:
    imgBytes = frameCache[frameIdx]

  else:
    success, img = cap.read()

    if success:
      imgBytes = img.tobytes()
      frameCache[frameIdx] = imgBytes
    else: # try again, after resetting to first frame
      frameIdx = 1
      imgBytes = frameCache[frameIdx]
      success = True

  #  cap.set(1,1)
  #  success, img = cap.read()

  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      success = False

  wn.blit(pygame.image.frombuffer(imgBytes, shape, "BGR"), (0, 0))
  pygame.display.update()
  frameIdx += 1

pygame.quit()

#https://gist.github.com/vereperrot/dd2263e220e68555d687f2ed2075d590
# https://stackoverflow.com/questions/33650974/opencv-python-read-specific-frame-using-videocapture
#import numpy as np
#import cv2
#cap = cv2.VideoCapture(video_name) #video_name is the video being called
#cap.set(1,frame_no); # Where frame_no is the frame you want
#ret, frame = cap.read() # Read the frame
#cv2.imshow('window_name', frame) # show frame on window
#If you want to hold the window, until you press exit:

#while True:
#    ch = 0xFF & cv2.waitKey(1) # Wait for a second
#    if ch == 27:
#        break

### end ###
