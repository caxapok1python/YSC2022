#!/usr/bin/env python3
import pyfirmata
import time

k = 1
statpower = 1.0

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
            lpower = (sp * (90 - abs(angle))) / 90
            rpower = sp
        else:
            rpower = (sp * (90 - abs(angle))) / 90
            lpower = sp

        self.left.set_power(lpower)
        self.right.set_power(rpower)

    def set_power(self, lpower, rpower):
        self.left.set_power(lpower)
        self.right.set_power(rpower)


PORT = '/dev/tty.usbmodem14101'
board = pyfirmata.Arduino(PORT)
print("Communication Successfully started")

left = Motor(3, 7, 5)
right = Motor(2, 4, 6)
chassis = Chassis(left, right)

chassis.set_power(0.5, 0.5)
time.sleep(2)
chassis.set_power(0, 0)


