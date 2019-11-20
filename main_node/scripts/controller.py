#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from main_node.msg import joystick, joystick_btn, servo

def callback_analog(data):
    rospy.loginfo(rospy.get_caller_id() + 'Received Data: x: %s, y: %s', data.x, data.y)

def callback_jsButton(data):
    rospy.loginfo(rospy.get_caller_id() + 'Button Presed')

def callback_servo(data):
    rospy.loginfo(rospy.get_caller_id() + 'Servo Position: %s', data.pos)

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('main_node', anonymous=True)

    rospy.Subscriber('joystick_analog', joystick, callback_analog)
    rospy.Subscriber('joystick_btn', joystick_btn, callback_jsButton)
    rospy.Subscriber('servo', servo, callback_servo)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
