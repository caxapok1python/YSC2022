import pyfirmata
import time


PORT = '/dev/ttyACM0'
board = pyfirmata.Arduino(PORT)
print("Communication Successfully started")
f = False
t = 0.3

while True:
    board.digital[13].write(f)
    time.sleep(t)
    f = not f
