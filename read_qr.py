import cv2
import pyzbar.pyzbar as zbar
cap = cv2.VideoCapture(0)
print("started")
detector = cv2.QRCodeDetector()
print("looking for qr")
while True:
    ret, img = cap.read()
    decodedObjects = zbar.decode(img)
    if not len(decodedObjects):
        continue
    print(decodedObjects[0].data)
    break

cap.release()
