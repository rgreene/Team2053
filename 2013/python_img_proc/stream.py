from SimpleCV import *
cam = Camera()
while 1:
	img = cam.getImage()
	img.show()
