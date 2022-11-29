import pyfirmata
# import time


class Motor:
    def __init__(self, board, inA: int, inB: int, pwm: int):
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
    def __init__(self, leftside: Motor, rightside: Motor, max_power=0.3, k=1.5):
        self.left = leftside
        self.right = rightside
        self.k = k
        self.statpower = max_power

    def direction(self, angle: float):
        '''
        :param angle: float between -90 and 90
        :return: None
        '''
        sp = self.statpower
        if angle < 0:
            lpower = sp - (sp * abs(angle) / 90 * self.k)
            if lpower < 0:
                lpower = 0
            rpower = sp
        else:
            rpower = sp - (sp * abs(angle) / 90 * self.k)
            if rpower < 0:
                rpower = 0
            lpower = sp

        print(lpower, rpower)

        self.left.set_power(-1 * lpower)
        self.right.set_power(-1 * rpower)

    def set_power(self, lpower, rpower):
        self.left.set_power(lpower)
        self.right.set_power(rpower)

    def stop(self):
        self.left.set_power(0)
        self.right.set_power(0)