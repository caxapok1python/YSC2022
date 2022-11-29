import cv2
cap = cv2.VideoCapture(0)

detector = cv2.QRCodeDetector()

while True:
    ret, img = cap.read()
    if not ret:
        break
    data, _, _ = detector.detectAndDecode(img)
    if data:
        print(data)
        break

cap.release()
