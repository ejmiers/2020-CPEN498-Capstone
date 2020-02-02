#!/usr/bin/env python

# Node that sits between the drivetrain and device controllers on Raspberry Pi
# Responsible for handling the competition logic
#   Includes PI sequence state logic, instructing the drivetrain to drive, competition timing
#
# Written by Eric Miers, 1/31/2020

import time
import rospy
from main_node.msg import comp_stop, move_dt, move_arm, move_on

class MainNode(object):
    
    def __init__(self):
        # Value to keep track of competition end time - gets intitialization time and adds 180 seconds to it
        self.stopTime = time.time() + 180

        # 500 digits of pi stored as a list (Extremely Optimistic)
        self.PI_LIST = [3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,8,3,2,7,
        9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8,2,0,9,7,4,9,4,4,5,9,2,3,0,
        7,8,1,6,4,0,6,2,8,6,2,0,8,9,9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9,8,
        2,1,4,8,0,8,6,5,1,3,2,8,2,3,0,6,6,4,7,0,9,3,8,4,4,6,0,9,5,5,0,5,8,2,2,3,
        1,7,2,5,3,5,9,4,0,8,1,2,8,4,8,1,1,1,7,4,5,0,2,8,4,1,0,2,7,0,1,9,3,8,5,2,
        1,1,0,5,5,5,9,6,4,4,6,2,2,9,4,8,9,5,4,9,3,0,3,8,1,9,6,4,4,2,8,8,1,0,9,7,
        5,6,6,5,9,3,3,4,4,6,1,2,8,4,7,5,6,4,8,2,3,3,7,8,6,7,8,3,1,6,5,2,7,1,2,0,
        1,9,0,9,1,4,5,6,4,8,5,6,6,9,2,3,4,6,0,3,4,8,6,1,0,4,5,4,3,2,6,6,4,8,2,1,
        3,3,9,3,6,0,7,2,6,0,2,4,9,1,4,1,2,7,3,7,2,4,5,8,7,0,0,6,6,0,6,3,1,5,5,8,
        8,1,7,4,8,8,1,5,2,0,9,2,0,9,6,2,8,2,9,2,5,4,0,9,1,7,1,5,3,6,4,3,6,7,8,9,
        2,5,9,0,3,6,0,0,1,1,3,3,0,5,3,0,5,4,8,8,2,0,4,6,6,5,2,1,3,8,4,1,4,6,9,5,
        1,9,4,1,5,1,1,6,0,9,4,3,3,0,5,7,2,7,0,3,6,5,7,5,9,5,9,1,9,5,3,0,9,2,1,8,
        6,1,1,7,3,8,1,9,3,2,6,1,1,7,9,3,1,0,5,1,1,8,5,4,8,0,7,4,4,6,2,3,7,9,9,6,
        2,7,4,9,5,6,7,3,5,1,8,8,5,7,5,2,7,2,4,8,9,1,2,2,7,9,3,8,1,8,3,0,1,1,9,4,
        9,1,2]

        # Pointer to keep track of placement in list
        self.listPointer = 0
        
        # Initialize the node
        rospy.init_node('main_controller_node')

        # Initiailize subscriber
        rospy.Subscriber('move_on', move_on, self.moveOnCallback)

        # Initialize Publishers
        self.compStopPub = rospy.Publisher('comp_stop', comp_stop, queue_size=1)
        self.moveDtPub = rospy.Publisher('move_dt', move_dt, queue_size=1)
        self.moveArmPub = rospy.Publisher('move_arm', move_arm, queue_size=1)

    # Callback function for "move_on" messages
    # Checks the current sequence of pi and will determine which way to move the drivetrain
    def moveOnCallback(self, msg):
        rospy.loginfo(rospy.get_caller_id() + ": Move On Message Received")
        
        # Verify that the comp time has not expired, publish a halting message if so
        if (time.time() >= self.stopTime):
            self.compStopPub.publish(stop=1)
            exit()
        
        # Get the next element in the sequence and compare it with the current one
        if (msg.moveOn == 1) and (self.listPointer < len(self.PI_LIST) - 1):
            currentDigit = self.PI_LIST[self.listPointer]
            nextDigit = self.PI_LIST[self.listPointer+1]
            
            if (currentDigit > nextDigit):
                #Instruct drivetrain to move left
                self.moveDtPub.publish(direction=0)
            elif (currentDigit < nextDigit):
                #Instruct drivetrain to move right
                self.moveDtPub.publish(direction=1)
            else:
                #Current==Next, drivetrain doesn't need to move, tell arm to move
                self.moveArmPub.publish(move=1)
        
        # Increment the list pointer
        self.listPointer += 1

    def run(self):
        
        # Publish first Message to drivetrain to move left
        self.moveDtPub.publish(direction=0)

        # Main execution Loop
        while not rospy.is_shutdown():
            
            # Verify that the comp time has not expired, publish a halting message if so
            if (time.time() >= self.stopTime):
                self.compStopPub.publish(stop=1)
                exit()
            
            rospy.sleep(1)


if __name__ == '__main__':
    node = MainNode()
    node.run()
