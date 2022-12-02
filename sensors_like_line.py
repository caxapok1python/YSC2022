from robot import Chassis, Motor
from pyfirmata import ArduinoMega
import cv2

serial = '/dev/ttyUSB0'
max_power = 0.3
k = 3

board = ArduinoMega(serial)
left = Motor(board, *(3, 7, 5))
right = Motor(board, *(2, 4, 6))
chassis = Chassis(left, right, max_power=max_power, k=k)


class Point:
    def __init__(self, x, y, r=0):
        self.x = x
        self.y = y
        if r:
            self.box_points = self.box_points(r)
            rect = cv2.minAreaRect(self.box_points)

    def box_points(self, r):
        points = []
        points.append((self.x-r, self.y-r))  # a
        points.append((self.x+r, self.y-r))  # b
        points.append((self.x+r, self.y+r))  # c
        points.append((self.x-r, self.y+r))  # d
        return points


class Tracker:
    def __init__(self, height, count):
        self.sens_count = count
        self.height = height
        self.points = self.gen_points(count)
        self.vals = [0]*count

    def process(self, image, power=1.0, kp=1.0):
        if not image:
            raise KeyboardInterrupt
        h, w = image.shape[:2]
        if len(self.points) % 2 == 0:
            if self.get_pixel(image, self.points[len(self.points)//2]) > 200:
                pass
        else:
            pass

        matrix = 0

    def get_pixel(self, image, point: Point):
        return image[point.y][point.x]

    def gen_points(self, count):
        points = []
        start = 15
        for i in range(count):
            points.append(Point(start * (i+1), self.height))
        return points

    def gen_vals(self, image):
        vals = []
        for i in range(len(self.points)):
            vals.append(image[self.points[i].y][self.points[i].x])

