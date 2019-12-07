#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from main_node.msg import lightDetected, fsrTriggered, servoExtend, servoRetract, servoComplete

def callback_lightDetected(data):
    rospy.loginfo(rospy.get_caller_id() + 'High Light Intensity Detected: %s', data.value)

#def callback_servoExtend(data):
#    rospy.loginfo(rospy.get_caller_id() + 'Servo Extending')

#def callback_servoRetract(data):
#    rospy.loginfo(rospy.get_caller_id() + 'Servo Retracting')

#def callback_fsrTriggered(data):
#    rospy.loginfo (rospy.get_caller_id() + 'FSR Triggered with value: %s', data.triggered)

def callback_servoComplete(data):
    rospy.loginfo(rospy.get_caller_id() + 'Servo Completed with FSR Value: %s', data.fsrValue)


def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('main_node', anonymous=True)

    rospy.Subscriber('lightDetected', lightDetected, callback_lightDetected)
    #rospy.Subscriber('fsrTriggered', fsrTriggered, callback_fsrTriggered)
    #rospy.Subscriber('servoExtend', servoExtend, callback_servoExtend)
    #rospy.Subscriber('servoRetract', servoRetract, callback_servoRetract)
    rospy.Subscriber('servoComplete', servoComplete, callback_servoComplete)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
