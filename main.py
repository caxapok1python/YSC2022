from robot import Robot, Callback

robot = Robot('/dev/ttyUSB0')
robot.setup_motors((3, 5, 7), (2, 4, 6))
robot.setup_camera(0)
robot.camera.set_line_params(dt=90, work_pos=90, work_width=60, work_height=20, blur=13)
robot.stop()

callback = Callback(robot)
robot.camera.track_line(callback.follow_line)
