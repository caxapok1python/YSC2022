import sys

from robot import Robot, Callback
import cv2

while True:
    # robot = Robot('/dev/tty.usbmodem14201')  # with motors macbook
    robot = Robot('/dev/ttyUSB0')  # with motors rasbberry pi

    robot.setup_motors((3, 7, 5), (2, 4, 6), max_power=0.6, k=7)
    robot.setup_camera(0)
    if int(sys.argv[1]) < 0:
        robot.camera.set_line_params(dt=0, work_pos=400, work_width=245, work_height=20, blur=13)
        callback = Callback(robot)
        robot.camera.track_line2(callback.follow_line)
    else:
        robot.camera.set_line_params(dt=int(sys.argv[1]), work_pos=400, work_width=245, work_height=20, blur=13)
        callback = Callback(robot)
        robot.camera.track_line(callback.follow_line)
