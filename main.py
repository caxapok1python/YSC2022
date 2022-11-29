import sys

from robot import Robot, Callback
import cv2

while True:
    a = input()
    if (a):
        break

    # robot = Robot('/dev/tty.usbmodem14201')  # with motors macbook
    robot = Robot('/dev/ttyUSB0')  # with motors rasbberry pi
    robot.setup_motors((3, 7, 5), (2, 4, 6), max_power=0.3, k=3)
    # robot = Robot()  # without motors
    robot.setup_camera(0)
    robot.camera.set_line_params(dt=70, work_pos=400, work_width=300, work_height=20, blur=13)
    # _, img = robot.camera.cap.read()
    # img = cv2.imread('test1.png')
    # dt = robot.camera.autoconf_dt(img)
    # print(dt)

    callback = Callback(robot)
    # robot.camera.track_line(print)
    robot.camera.track_line(callback.follow_line)



