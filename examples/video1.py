# https://stackoverflow.com/questions/21356439/how-to-load-and-play-a-video-in-pygame

import cv2
import pygame

cap = cv2.VideoCapture('video.mp4')
success, img = cap.read()
shape = img.shape[1::-1]
wn = pygame.display.set_mode(shape)
clock = pygame.time.Clock()

while success:
  clock.tick(60)
  success, img = cap.read()
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      success = False
  wn.blit(pygame.image.frombuffer(img.tobytes(), shape, "BGR"), (0, 0))
  pygame.display.update()

pygame.quit()

### end ###
