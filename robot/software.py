from typing import Any, Tuple

import cv2
import numpy as np
from math import atan2


class Camera:
    robot_center: tuple[int, int]
    blur: int
    work_width: int
    work_height: int
    work_pos: int
    dt: int

    def __init__(self, camera_input=0):
        self.cap = cv2.VideoCapture(camera_input)
        ret, sample = self.cap.read()
        while not ret:
            ret, sample = self.cap.read()
        self.height, self.width = sample.shape[:2]
        self.set_line_params()

    def set_line_params(self, dt=90, work_pos=80, work_height=20, work_width=60, blur=13):
        self.dt = dt
        self.work_pos = self.height * 0.01 * work_pos
        self.work_height = work_height
        self.work_width = self.width * 0.01 * work_width
        self.blur = blur
        self.robot_center = (self.work_width // 2, self.height - 5)

    def track_line(self, callback=print):
        run = True
        while run:
            ret, img = self.cap.read()
            if not ret:
                break
            crop = img[self.work_pos:self.work_pos + self.work_height,
                   0 + int((self.width - self.work_width) / 2):self.width - int((self.width - self.work_width) / 2)]
            gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
            gray = cv2.GaussianBlur(gray, (self.blur, self.blur), 0)
            _, thrsh1 = cv2.threshold(gray, self.dt, 255, cv2.THRESH_BINARY_INV)
            moments = cv2.moments(thrsh1)
            if moments['m00'] != 0:
                print(moments['m00'])
                if moments['m00'] > self.work_width * self.work_height * 1000:
                    thrsh1 = cv2.bitwise_not(thrsh1, np.ones(thrsh1.shape, thrsh1.dtype))
                    moments = cv2.moments(thrsh1)
                line_center = (int(moments["m10"] / moments["m00"]), int(moments["m01"] / moments["m00"]))
                callback(line_center)

