from SimpleCV import *
cam = Camera()
img = cam.getImage()
img.save("test.jpg")