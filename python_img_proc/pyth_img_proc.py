from SimpleCV import *

cameraFieldOfView = 60.0
targetHeight_small = 20.0 # SMALL GOAL
goal_height_small = 9.5 
targetHeight = 29.0 # MEDIUM GOAL
goal_height = 8.5

blob_maker = BlobMaker()
#img = Image('image2_ext.jpg') # multi-goal
#img = Image('image2.jpg') # flat on
#img = Image('image6.jpg') # angle
#img = Image('image5.jpg') # severe angle
img = Image('test.jpg')
#img = Image('image13_40feet.jpg')
#cam = Camera()
#img = cam.getImage()
img_size = img.size()
centerX = (img_size[0])/2
centerY = (img_size[1])/2

# ========= filter on GREEN from LED
green_distance = img.colorDistance(Color.GREEN)
only_green = img - green_distance

#invert image and turn into binary image
bin_img = only_green.invert().binarize().morphClose()

# ========= filter on GREEN from LED
# ========= filter on WHITE from LED
#white_distance = img.colorDistance(Color.WHITE)
#only_white = img - white_distance
#
##invert image and turn into binary image
#bin_img = only_white.invert().binarize().morphClose()
# ========= filter on WHITE from LED

# ========= Hue Saturation Value stuff
#HSVImg = img.toHSV()
#(img_h, img_s, img_v) = HSVImg.splitChannels(False)
#HSVImg = HSVImg - img_s
#(HSVImg).binarize().invert().show()
# ========= Hue Saturation Value stuff

#close any open goals
bin_img = bin_img.dilate(10).erode(10)

#bin_img.show()

goals = blob_maker.extractFromBinary(bin_img, img, minsize=5, maxsize=-1, appx_level=3)
num_goals = len(goals)
for g in range(num_goals):
    if goals[g].isRectangle():
#    if 1:
#		centroid = goals[g].centroid()
		centroid = goals[g].coordinates()
		img.drawText("X", centroid[0], centroid[1], fontsize = 20)
		
		# Get corners
		goal_corners = goals[g].corners()
		cornerXY1 = goal_corners[0]
		cornerX1 = cornerXY1[0]
		cornerY1 = cornerXY1[1]
		cornerXY2 = goal_corners[1]
		cornerX2 = cornerXY2[0]
		cornerY2 = cornerXY2[1]
		cornerXY3 = goal_corners[2]
		cornerX3 = cornerXY3[0]
		cornerY3 = cornerXY3[1]
		cornerXY4 = goal_corners[3]
		cornerX4 = cornerXY4[0]
		cornerY4 = cornerXY4[1]

		# Draw Corners
		img.drawText("1", cornerX1,cornerY1, fontsize = 20)
		img.drawText("2", cornerX2,cornerY2, fontsize = 20)
		img.drawText("3", cornerX3,cornerY3, fontsize = 20)
		img.drawText("4", cornerX4,cornerY4, fontsize = 20)
		
		goal_height_pix = cornerY4 - cornerY1
		goal_width_pix = cornerX2 - cornerX1
		
		min_bounding_height = goals[g].minRectHeight()
		min_bounding_width = goals[g].minRectWidth()
		goal_ratio = min_bounding_height/min_bounding_width

		if (goal_ratio > .4):
			print "Medium Goal"
			totalDistance = (((targetHeight*img_size[1])/goal_height_pix))/tan(((cameraFieldOfView*3.14159)/180.0)/2.0)
			print "Goal Distance: %f"%(((totalDistance)/12.0))
			print "Goal Height: %f"%(goal_height)
			center_angle = atan(goal_height/((totalDistance/12.0)))*(180.0/3.14159)
			print "Goal Angle: %f"%(center_angle)
		else:
			print "Small Goal"
			totalDistance = (((targetHeight_small*img_size[1])/goal_height_pix))/tan(((cameraFieldOfView*3.14159)/180.0)/2.0)
			print "Goal Distance: %f"%(((totalDistance)/12.0))
			print "Goal Height: %f"%(goal_height_small)
			center_angle = atan(goal_height_small/((totalDistance/12.0)))*(180.0/3.14159)
			print "Goal Angle: %f"%(center_angle)
			
		

img.drawText("O", centerX, centerY, fontsize = 20)

#Goal diatance from Robot


print "Total number of goals in img: %d" %(num_goals)
goals.show()
out = raw_input('press enter to end')