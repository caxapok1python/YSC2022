import cv2
cap = cv2.VideoCapture(0)
print("started")
detector = cv2.QRCodeDetector()
print("looking for qr")
while True:
    ret, img = cap.read()
    if not ret:
        break
    cv2.imwrite('../tmp/qr_work.png', img)
    data, _, _ = detector.detectAndDecode(img)
    if data:
        print(data)
        break

cap.release()
