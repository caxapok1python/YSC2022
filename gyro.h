// #include "wiring_private.h"
// Gyro scope GY-521

#include "GY521.h"

// AD0 connected to GND => 0x68 AD0 connected to VCC => 0x69
GY521 sensor(0x69);

uint32_t counter = 0;

float gyroX, gyroY, gyroZ;
float accelX, accelY, accelZ;

void setupGyro(){
  Wire.begin();

   // adjust when needed.
  sensor.setAccelSensitivity(0);  // 2g
  sensor.setGyroSensitivity(0);   // 250 degrees/s
  sensor.setThrottle(false);

  // set all calibration errors to zero
  sensor.axe = 0;
  sensor.aye = 0;
  sensor.aze = 0;
  sensor.gxe = 0;
  sensor.gye = 0;
  sensor.gze = 0;
}

void calibrateGyro(){
  accelX = accelY = accelZ = 0;
  gyroX = gyroY = gyroZ = 0;
  for (int i = 0; i < 20; i++)
  {
    sensor.read();
    accelX -= sensor.getAccelX();
    accelY -= sensor.getAccelY();
    accelZ -= sensor.getAccelZ();
    gyroX -= sensor.getGyroX();
    gyroY -= sensor.getGyroY();
    gyroZ -= sensor.getGyroZ();
  }

  // adjust calibration errors so table should get all zero's.
  sensor.axe += accelX * 0.05;
  sensor.aye += accelY * 0.05;
  sensor.aze += accelZ * 0.05;
  sensor.gxe += gyroX * 0.05;
  sensor.gye += gyroY * 0.05;
  sensor.gze += gyroZ * 0.05;

  counter++;
  delay(100);
}




