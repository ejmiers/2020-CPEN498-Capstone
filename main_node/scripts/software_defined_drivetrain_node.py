#!/usr/bin/env python

# Node that emulates communication functions of the drivetrain
# Used for device testing purposes
#
# Written by Eric Miers, 1/31/2020

import rospy
from main_node.msg import comp_stop, light_detected, move_dt, move_arm

class SDDT(object):
	
	def __init__(self):
		# Initialize the node
		rospy.init_node('software_defined_drivetrain_node')

		# Initiailize subscriber
		rospy.Subscriber('comp_stop', comp_stop, self.compStopCallback)
		rospy.Subscriber('light_detected', light_detected, self.lightDetectedCallback)
		rospy.Subscriber('move_dt', move_dt, self. moveDtCallback)
		
		# Initialize Publisher
		self.moveArmPub = rospy.Publisher('move_arm', move_arm, queue_size=1)

	# Callback to shutdown the node when competition time expiration message is received
	def compStopCallback(self, msg):
		rospy.loginfo(rospy.get_caller_id() + ": Time has expired. Shutting down...")
		if (msg.stop == 1):
			exit()

	# Callback to publish the "move_arm" message when light detected message is received
	def lightDetectedCallback(self, msg):
		if (msg.detected == 1):
			rospy.loginfo(rospy.get_caller_id() + ": Light Detected!")
			rospy.sleep(1)
			
			self.moveArmPub.publish(move=1)
		
	# Callback to print "move_dt" message contents to terminal when message is received
	def moveDtCallback(self, msg):
		if (msg.direction == 0):
			rospy.loginfo(rospy.get_caller_id() + ": Drivetrain instructed to go LEFT")
		elif (msg.direction == 1):
			rospy.loginfo(rospy.get_caller_id() + ": Drivetrain instructed to go RIGHT")
		else:
			rospy.loginfo(rospy.get_caller_id() + ": ERROR: move_dt.direction contains an unknown value: %s", msg.direction)
		
		
	def run(self):
		# spin() simply keeps python from exiting until this node is stopped
		rospy.spin()


if __name__ == '__main__':
    node = SDDT()
    node.run()
