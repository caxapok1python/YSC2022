import cv2
cap = cv2.VideoCapture(0)
print("started")
detector = cv2.QRCodeDetector()
print("looking for qr")
while True:
    ret, img = cap.read()
    if not ret:
        break
    data, _, _ = detector.detectAndDecode(img)
    if data:
        print(data)
        break

cap.release()