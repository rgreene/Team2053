from SimpleCV import *
import collections
import time
from pynetworktables import *
import os

# return val of img processing
point = collections.namedtuple('Point', ['adj', 'angl'])

# global constants
cameraFieldOfView = 60.0
targetHeight_small = 20.0 # SMALL GOAL
goal_height_small = 9.5 
targetHeight = 29.0 # MEDIUM GOAL
goal_height = 8.5

def image_proc(cam):	
	blob_maker = BlobMaker()
	#img = Image('image2_ext.jpg') # multi-goal
	#img = Image('image2.jpg') # flat on
	#img = Image('image6.jpg') # angle
	#img = Image('image5.jpg') # severe angle
	#img = Image('test.jpg')
	#img = Image('image13_40feet.jpg')
	img = cam.getImage()
	img_size = img.size()
	centerX = (img_size[0])/2
	centerY = (img_size[1])/2
	
	# ========= filter on GREEN from LED
	#green_distance = img.colorDistance(Color.GREEN)
	green_distance = img.colorDistance(color=(239,239,239))
	only_green = img - green_distance
        only_green.save("only_green.jpg")
	
	#invert image and turn into binary image
	bin_img = only_green.invert().binarize()#.morphClose()
	
	# ========= filter on GREEN from LED
	
	#close any open goals
	bin_img = bin_img.dilate(7).erode(7)
	
	#bin_img.show()
        bin_img.save("black_rect.jpg")
	goal_dist_array = []
	
	goals = blob_maker.extractFromBinary(bin_img, img, minsize=100, maxsize=-1, appx_level=1)
	num_goals = len(goals)

	#print(num_goals)	

	# determine which goal is closest
	if num_goals > 0:
		for g in range(num_goals):
			centroid = goals[g].coordinates()
			#img.drawText("X", centroid[0], centroid[1], fontsize = 20)
			goal_dist = sqrt((pow((centroid[0] - centerX), 2)) + ((pow((centroid[1] - centerY),2))))
		#	print "Distance to center: %d" % goal_dist
			goal_dist_array.append(goal_dist)
	else:
		p = point(0,-90)
		return p

	# init return values
	robot_adj_pix_X = 0.0
        center_angle = 66.0	
	totalDistance = 0.0

	darr = np.array(goal_dist_array)
	#print(darr.argmin())
	k = darr.argmin()
	
	# Process closest goal 
	if goals[k].isRectangle():
	#if 1:
		centroid = goals[k].coordinates()
		img.drawText("X", centroid[0], centroid[1], fontsize = 20)

		goal_dist = sqrt((pow((centroid[0] - centerX), 2)) + ((pow((centroid[1] - centerY),2))))
		#print "Distance to center: %d" % goal_dist
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
#	p = point(robot_adj_pix_X,totalDistance)
	return p

def setup_networktables():
	ip = u"10.20.53.2"
	NetworkTable.SetIPAddress(ip)
	NetworkTable.SetClientMode()
	NetworkTable.Initialize()

	time.sleep(3)
	table = NetworkTable.GetTable(u"robotMovement")
	time.sleep(3)
	table.PutBoolean(u"tableInUse",False)

	
def main():
	# declare camera object
	no_cam = False
	if os.path.exists('/dev/video4'):
		webcam = Camera(4)
	else:
		if os.path.exists('/dev/video5'):
			webcam = Camera(5)
		else:
			no_cam = True
	
	setup_networktables()
	point = collections.namedtuple('Point', ['adj', 'angl'])

	if ~no_cam:
		while 1:
			if table.GetBoolean(u'adjustEnabled'):
			#if 1:
				if (~table.GetBoolean(u'tableInUse') and table.GetBoolean(u'tableRead')):
					table.PutBoolean(u'tableInUse',True)
					q = point(0,0)
					q = image_proc(webcam)
					#print "returned_adj: %f"%q[0]
					#print "returned_angl: %f"%q[1]	
					table.PutNumber(u'angle',q[1])
					table.PutBoolean(u'tableUpdated',True)
					table.PutBoolean(u'tableInUse',False)
					#table.PutBoolean(u"adjustEnabled",False)
		
		#out = raw_input('press enter to end')
main()
