#include <M5StickCPlus.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <M5StickCPlus.h>
#include "time.h"

unsigned long time_now;
unsigned long start_time;
unsigned int counter=0;

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
  
  SerialBT.begin("えむごstiiiiick!!!");
  
  M5.Imu.Init(); 
  M5.Lcd.setRotation(3);  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
}

void loop() {
  static float temp = 0;
  M5.update();

  if (M5.BtnA.wasReleased()){
    start_time = millis();
    counter=0;
   }
   while (millis()-start_time < counter*8){
    delayMicroseconds(4);
   }
  time_now = millis();
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getTempData(&temp);
  M5.Lcd.setCursor(80,100);
  M5.Lcd.print(counter*8);
  M5.Lcd.setCursor(100,60);
  M5.Lcd.printf("time");
  counter++;

  
  SerialBT.print("time");
  SerialBT.print(counter*100);
  SerialBT.print(",");
  SerialBT.print(gyroX); 
  SerialBT.print(",");
  SerialBT.print(gyroY);
  SerialBT.print(",");
  SerialBT.print(gyroZ);
  SerialBT.print(",");
  SerialBT.print(accX); 
  SerialBT.print(",");
  SerialBT.print(accY);
  SerialBT.print(",");
  SerialBT.print(accZ);
  SerialBT.print(",");
  SerialBT.print(pitch); 
  SerialBT.print(",");
  SerialBT.print(roll);
  SerialBT.print(",");
  SerialBT.println(yaw);
 
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
}
