#!/usr/bin/env python3
import pyfirmata
import cv2
import numpy as np
from math import atan2
import time

k = 1
statpower = 1.0
line_bin = 150

work_pos = 50
work_height = 20
work_width = 600
blur_size = 13

last_turn = 0


class Motor:
    def __init__(self, inA: int, inB: int, pwm: int):
        global board
        self.inA = board.digital[inA]
        self.inB = board.digital[inB]
        self.pwm = board.digital[pwm]
        self.pwm.mode = pyfirmata.PWM

    def set_power(self, power: float):
        if power == 0:
            self.inA.write(0)
            self.inB.write(1)
            self.pwm.write(0)
            return
        elif power > 0:
            power = abs(power)
            self.inA.write(1)
            self.inB.write(1)
            self.pwm.write(power)
            return
        power = abs(power)
        self.inA.write(1)
        self.inB.write(0)
        self.pwm.write(power)


class Chassis:
    def __init__(self, leftside: Motor, rightside: Motor):
        self.left = leftside
        self.right = rightside

    def direction(self, angle: float):
        '''
        :param angle: float between -90 and 90
        :return: None
        '''
        global statpower, k
        sp = statpower
        if angle > 0:
            lpower = (sp * (90 - abs(angle))) / 90 * k
            rpower = sp
        else:
            rpower = (sp * (90 - abs(angle))) / 90 * k
            lpower = sp

        self.left.set_power(lpower)
        self.right.set_power(rpower)

    def set_power(self, lpower, rpower):
        self.left.set_power(lpower)
        self.right.set_power(rpower)


PORT = '/dev/tty.usbmodem14101'
board = pyfirmata.Arduino(PORT)
print("Communication Successfully started")

left = Motor(3, 5, 7)
right = Motor(2, 4, 6)
chassis = Chassis(left, right)

cap = cv2.VideoCapture(0)

while True:
    ret, img = cap.read()
    if not ret:
        break
    h, w = img.shape[:2]
    robot_center = (work_width // 2, h - 5)
    crop = img[work_pos:work_pos + work_height, 0 + int((w - work_width) / 2):w - int((w - work_width) / 2)]
    gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (blur_size, blur_size), 0)
    _, thrsh1 = cv2.threshold(gray, line_bin, 255, cv2.THRESH_BINARY_INV)
    moments = cv2.moments(thrsh1)
    if moments['m00'] != 0:
        print(moments['m00'])
        if moments['m00'] > work_width * work_height * 100:
            thrsh1 = cv2.bitwise_not(thrsh1, np.ones(thrsh1.shape, thrsh1.dtype))
            moments = cv2.moments(thrsh1)
        line_center = (int(moments["m10"] / moments["m00"]), int(moments["m01"] / moments["m00"]))
        alc = (0 + int((w - work_width) / 2) + line_center[0], work_pos + line_center[1])
        dx = robot_center[0] - alc[0]
        dy = robot_center[1] - alc[1]
        angle = float(np.degrees(atan2(dx, dy)))
    else:
        angle = 90 * last_turn

    chassis.direction(angle)
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q') or key == 27:
        break

chassis.set_power(0, 0)
cv2.destroyAllWindows()
cap.release()
