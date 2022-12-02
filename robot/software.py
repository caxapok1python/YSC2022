from typing import Any, Tuple

import cv2
import numpy as np
from math import atan2


class Camera:
    AUTO = -1

    def __init__(self, camera_input=0, height=480, width=620, fps=90):
        self.robot_center = None
        self.blur = None
        self.work_width = None
        self.work_height = None
        self.work_pos = None
        self.dt = None

        self.cap = cv2.VideoCapture(camera_input)
        # self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
        # self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
        # self.cap.set(cv2.CAP_PROP_FRAME_COUNT, fps)

        self.height, self.width = 480, 640

        self.set_line_params()

    def set_line_params(self, dt=70, work_pos=400, work_height=20, work_width=300, blur=13):
        self.work_pos = work_pos
        self.work_height = work_height
        self.work_width = work_width
        self.blur = blur
        self.robot_center = (self.work_width // 2, self.height - 5)

        if dt < 0:
            _, img = self.cap.read()
            self.dt = self.autoconf_dt(img)
            print(f"[+] AUTOCONFIGURATED DT: {self.dt}")
            return
        self.dt = dt

    def autoconf_dt(self, img):
        dt = []
        crop = img[self.work_pos:self.work_pos + self.work_height,
               0 + int((self.width - self.work_width) / 2):self.width - int((self.width - self.work_width) / 2)]
        gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray, (self.blur, self.blur), 0)
        for i in range(0, 256):
            _, thrsh1 = cv2.threshold(gray, i, 255, cv2.THRESH_BINARY_INV)
            m = cv2.moments(thrsh1)['m00']
            if 255 * self.work_height * 30 < m < 255 * self.work_height * 60:
                dt.append(i)
        if len(dt):
            median = dt[len(dt) // 2]
            return median
        return 115

    def track_line(self, callback=print):
        while True:
            try:
                ret, img = self.cap.read()
                # cv2.imwrite('../tmp/work_full.png', img)
                if not ret:
                    break
                crop = img[self.work_pos:self.work_pos + self.work_height,
                       0 + int((self.width - self.work_width) / 2):self.width - int((self.width - self.work_width) / 2)]
                # cv2.imwrite('../tmp/work.png', crop)
                gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
                gray = cv2.GaussianBlur(gray, (self.blur, self.blur), 0)
                _, thrsh1 = cv2.threshold(gray, self.dt, 255, cv2.THRESH_BINARY_INV)
                moments = cv2.moments(thrsh1)
                print(moments['m00'])
                if moments['m00'] > 5000:
                    if moments['m00'] > self.work_width * self.work_height * 1000:
                        thrsh1 = cv2.bitwise_not(thrsh1, np.ones(thrsh1.shape, thrsh1.dtype))

                        moments = cv2.moments(thrsh1)
                    line_center = (int(moments["m10"] / moments["m00"]), int(moments["m01"] / moments["m00"]))
                    callback(line_center)
                # cv2.imshow("image", thrsh1)
                key = cv2.waitKey(1) & 0xFF
            except KeyboardInterrupt:
                break
        self.stop()

    def track_line2(self, callback=print):
        while True:
            try:
                ret, img = self.cap.read()
                # cv2.imwrite('../tmp/work_full.png', img)
                if not ret:
                    break
                crop = img[self.work_pos:self.work_pos + self.work_height,
                       0 + int((self.width - self.work_width) / 2):self.width - int((self.width - self.work_width) / 2)]
                # cv2.imwrite('../tmp/work.png', crop)
                gray = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
                gray = cv2.GaussianBlur(gray, (self.blur, self.blur), 0)

                # Apply adaptive thresholding
                thrsh1 = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 31, 15)
                thrsh1 = cv2.bitwise_not(thrsh1, np.ones(thrsh1.shape, thrsh1.dtype))

                moments = cv2.moments(thrsh1)
                print(moments['m00'])
                if moments['m00'] > 5000:
                    if moments['m00'] > self.work_width * self.work_height * 1000:
                        thrsh1 = cv2.bitwise_not(thrsh1, np.ones(thrsh1.shape, thrsh1.dtype))

                        moments = cv2.moments(thrsh1)
                    line_center = (int(moments["m10"] / moments["m00"]), int(moments["m01"] / moments["m00"]))
                    callback(line_center)
                # cv2.imshow("image", thrsh1)
                key = cv2.waitKey(1) & 0xFF
            except KeyboardInterrupt:
                break
        self.stop()

    def stop(self):
        self.cap.release()
        cv2.destroyAllWindows()

