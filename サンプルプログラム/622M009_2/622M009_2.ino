#include <M5StickCPlus.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

int mode = -1; 

void setup() {
  M5.begin(); 
  M5.Imu.Init(); 
  M5.Lcd.setRotation(3);  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10,70); 
  M5.Lcd.println("X");
  M5.Lcd.setCursor(10,90);
  M5.Lcd.println("Y");
  M5.Lcd.setCursor(10,110);
  M5.Lcd.println("Z");
  M5.Lcd.setCursor(5, 10);
  M5.Lcd.println("Pitch   Roll   Yaw");
}

void loop() {
  static float temp = 0;
  M5.update();
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getTempData(&temp);
  M5.Lcd.setCursor(20, 70);
  M5.Lcd.printf("%6.1f",gyroX);
  M5.Lcd.setCursor(20, 90);
  M5.Lcd.printf("%6.1f",gyroY);
  M5.Lcd.setCursor(20, 110);
  M5.Lcd.printf("%6.1f",gyroZ);
  M5.Lcd.setCursor(20, 50);
  M5.Lcd.print("o/s");
  M5.Lcd.setCursor(150, 70);
  M5.Lcd.printf("%5.1f",accX);
  M5.Lcd.setCursor(150, 90);
  M5.Lcd.printf("%5.1f",accY);
  M5.Lcd.setCursor(150, 110);
  M5.Lcd.printf("%5.1f",accZ);
  M5.Lcd.setCursor(190, 50);
  M5.Lcd.print("G");
  M5.Lcd.setCursor(5, 30);
  M5.Lcd.printf("%6.1f%6.1f%6.1f",pitch,roll,yaw);

   if ( mode == -1 || M5.BtnA.wasReleased() ) {
    mode++;
    mode = mode % 3;
    if ( mode == 0 ) {
      Serial.printf("gyroX,gyroY,gyroZ\n");
    } else if ( mode == 1 ) {
      Serial.printf("accX,accY,accZ\n");
    } else if ( mode == 2 ) {
      Serial.printf("pitch,roll,yaw\n");
    }
  }
  
  if ( mode == 0 ) {
    Serial.printf("%6.2f,%6.2f,%6.2f\n", gyroX, gyroY, gyroZ);
  } else if ( mode == 1 ) {
    Serial.printf("%5.2f,%5.2f,%5.2f\n", accX, accY, accZ);
  } else if ( mode == 2 ) {
    Serial.printf("%5.2f,%5.2f,%5.2f\n", pitch, roll, yaw);
  }
  delay(100);
}
