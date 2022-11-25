from typing import Tuple

from .hardware import *
from .software import *


class Robot:
    def __init__(self, serial='/dev/ttyUSB0'):
        self.camera = None
        self.chassis = None
        self.right = None
        self.left = None
        self.board = pyfirmata.Arduino(serial)
        print("Communication Successfully started")

    def setup_motors(self, left: Tuple[int, int, int], right: Tuple[int, int, int], max_power=0.5, k=1.0):
        self.left = Motor(self.board, *left)
        self.right = Motor(self.board, *right)
        self.chassis = Chassis(self.left, self.right, max_power, k)

    def setup_camera(self, camera_number=0):
        self.camera = Camera(camera_number)

    def stop(self):
        self.chassis.set_power(0, 0)
        self.camera.stop()


class Callback:
    robot: Robot

    def __init__(self, robot: Robot):
        self.robot = robot

    def calculate_angle(self, line_center):
        alc = (0 + int((self.robot.camera.width - self.robot.camera.work_width) / 2) + line_center[0],
               self.robot.camera.work_pos + line_center[1])
        dx = self.robot.camera.robot_center[0] - alc[0]
        dy = self.robot.camera.robot_center[1] - alc[1]
        return float(np.degrees(atan2(dx, dy)))

    def follow_line(self, *args):
        angle = self.calculate_angle(*args)
        self.robot.chassis.direction(angle)
