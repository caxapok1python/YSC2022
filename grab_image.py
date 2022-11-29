import cv2
import numpy as np

dts = [50, 70, 90, 100, 110, 150, 170, 200]


def apply_dt(dt, img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    gray = cv2.GaussianBlur(gray, (13, 13), 0)
    _, thrsh1 = cv2.threshold(gray, dt, 255, cv2.THRESH_BINARY_INV)
    return thrsh1


cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 620)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(cv2.CAP_PROP_FRAME_COUNT, 90)

_, image = cap.read()
cv2.imwrite('../tmp/tmp.png', image)
for i in dts:
    th = apply_dt(i, image)
    cv2.imwrite(f'../tmp/{i}.png', th)
