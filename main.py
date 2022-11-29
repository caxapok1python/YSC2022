from robot import Robot, Callback
import cv2

robot = Robot('/dev/tty.usbmodem14201')  # with motors
robot.setup_motors((3, 7, 5), (2, 4, 6), max_power=0.5, k=1.0)
# robot = Robot()  # without motors
robot.setup_camera(0)
robot.camera.set_line_params(dt=90, work_pos=410, work_width=300, work_height=20, blur=13)
# _, img = robot.camera.cap.read()
# img = cv2.imread('test1.png')
# dt = robot.camera.autoconf_dt(img)
# print(dt)

callback = Callback(robot)
robot.camera.track_line(print)
# robot.camera.track_line(callback.follow_line)



