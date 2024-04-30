#include <M5StickCPlus.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <M5StickCPlus.h>
#include "time.h"

unsigned long time_now;
unsigned long start_time;
unsigned int count=0;

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
    count=0;
   }
   while (millis()-start_time < count*8){
    delayMicroseconds(4);
   }
  time_now = millis();
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getTempData(&temp);
  M5.Lcd.setCursor(80,100);
  M5.Lcd.printf("%8d",count*8);
  M5.Lcd.setCursor(100,60);
  M5.Lcd.printf("time");
 

  
  SerialBT.print("time");
  SerialBT.print(count*100);
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

  count++;
  
  
  Serial.printf("%8d,%6.2f,%6.2f,%6.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f\n",count*8, gyroX, gyroY, gyroZ, accX, accY, accZ, pitch, roll, yaw);
 
    }
   
