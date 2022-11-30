import cv2
import numpy as np

# dts = [10, 20, 30, 40, 50, 70, 90, 100, 110, 150, 170, 200]
dts = [10, 20, 30, 40, 50, ]


def apply_dt(dt, img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (13, 13), 0)
    _, thrsh1 = cv2.threshold(gray, dt, 255, cv2.THRESH_BINARY_INV)
    return thrsh1


cap = cv2.VideoCapture(0)

while True:
    ret, image = cap.read()
    cv2.imwrite('../tmp/tmp.png', image)
    print(image.shape)
    for i in dts:
        th = apply_dt(i, image)
        cv2.imwrite(f'../tmp/{i}.png', th)
    cv2.waitKey(1)
