from SimpleCV import *
import collections

#return val of img processing
point = collections.namedtuple('Point', ['adj', 'angl'])

def image_proc():
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
	#img = Image('test.jpg')
	#img = Image('image13_40feet.jpg')
	cam = Camera()
	img = cam.getImage()
	img_size = img.size()
	centerX = (img_size[0])/2
	centerY = (img_size[1])/2
	
	# ========= filter on GREEN from LED
	green_distance = img.colorDistance(Color.GREEN)
	only_green = img - green_distance
	
	#invert image and turn into binary image
	bin_img = only_green.invert().binarize().morphClose()
	
	# ========= filter on GREEN from LED
	
	#close any open goals
	bin_img = bin_img.dilate(10).erode(10)
	
	#bin_img.show()
	goal_dist_array = []
	
	goals = blob_maker.extractFromBinary(bin_img, img, minsize=5, maxsize=-1, appx_level=3)
	num_goals = len(goals)
	
	# determine which goal is closest
	for g in range(num_goals):
		centroid = goals[g].coordinates()
		img.drawText("X", centroid[0], centroid[1], fontsize = 20)
		goal_dist = sqrt((pow((centroid[0] - centerX), 2)) + ((pow((centroid[1] - centerY),2))))
	#	print "Distance to center: %d" % goal_dist
		goal_dist_array.append(goal_dist)
		
	darr = np.array(goal_dist_array)
	#print(darr.argmin())
	k = darr.argmin()
	
	# Process closest goal 
	if goals[k].isRectangle():
		centroid = goals[k].coordinates()
		img.drawText("X", centroid[0], centroid[1], fontsize = 20)

		goal_dist = sqrt((pow((centroid[0] - centerX), 2)) + ((pow((centroid[1] - centerY),2))))
	#	print "Distance to center: %d" % goal_dist
		goal_dist_array.append(goal_dist)
		
		# Get corners
		goal_corners = goals[k].corners()
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

		min_bounding_height = goals[k].minRectHeight()
		min_bounding_width = goals[k].minRectWidth()
		goal_ratio = min_bounding_height/min_bounding_width

		if (goal_ratio > .4):
			print "Medium Goal"
			totalDistance = (((targetHeight*img_size[1])/goal_height_pix))/tan(((cameraFieldOfView*3.14159)/180.0)/2.0)
			print "Goal Distance: %f"%(((totalDistance)/12.0))
			#print "Goal Height: %f"%(goal_height)
			center_angle = atan(goal_height/((totalDistance/12.0)))*(180.0/3.14159)
			#print "Goal Angle: %f"%(center_angle)
		else:
			print "Small Goal"
			totalDistance = (((targetHeight_small*img_size[1])/goal_height_pix))/tan(((cameraFieldOfView*3.14159)/180.0)/2.0)
			print "Goal Distance: %f"%(((totalDistance)/12.0))
			#print "Goal Height: %f"%(goal_height_small)
			center_angle = atan(goal_height_small/((totalDistance/12.0)))*(180.0/3.14159)
			#print "Goal Angle: %f"%(center_angle)

		robot_adj_pix_X = centerX - centroid[0]
		abs_adj = abs(robot_adj_pix_X)		
		#if robot_adj_pix_X < 0.0:
		#	print "Rotate left: %f"%(abs_adj)
		#	print "Adjust Angle to: %f"%(center_angle)
		#else:
		#	if robot_adj_pix_X > 0.0:
		#		print "Rotate Right: %f"%(abs_adj)
		#		print "Adjust Angle to: %f"%(center_angle)
		#	else:
		#		print "Adjust Angle to: %f"%(center_angle)

	img.drawText("O", centerX, centerY, fontsize = 20)
	
	# Uncomment the following to see what goal it chose
	goals.show()
	
	p = point(robot_adj_pix_X,center_angle)
	return p
	
def main():
		#point = collections.namedtuple('Point', ['adj', 'angl'])
		q = point(0,0)
		q = image_proc()
		print "returned_adj: %f"%q[0]
		print "returned_angl: %f"%q[1]
		
		out = raw_input('press enter to end')

main()