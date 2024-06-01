#include <BTAddress.h>
#include <BTAdvertisedDevice.h>
#include <BTScan.h>
#include <BluetoothSerial.h>
#include <M5Core2.h>

BluetoothSerial bts;

float accX = 0.0F;  
float accY = 0.0F;  
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

void setup(){
  M5.begin();         
  Serial.begin(2400); 
  bts.begin("M5Core2_test");
  M5.IMU.Init();       
  M5.Lcd.fillScreen(BLACK);  
  M5.Lcd.setTextColor(GREEN,BLACK);            
  M5.Lcd.setTextSize(2);                
  M5.IMU.SetAccelFsr(M5.IMU.AFS_8G);  
}

void loop() {
  M5.update();  

  M5.IMU.getAccelData(&accX, &accY, &accZ);  
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ); 
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);    

  M5.Lcd.setCursor(10, 20); 
  M5.Lcd.printf("gyrX   gyrY   gyrZ");  
  M5.Lcd.setCursor(10, 42);
  M5.Lcd.printf("%5.1f  %5.1f  %5.1f o/s", gyroX, gyroY, gyroZ);

    
  M5.Lcd.setCursor(10, 95);
  M5.Lcd.printf("accX   accY   accZ");
  M5.Lcd.setCursor(10, 117);
  M5.Lcd.printf("%5.1f  %5.1f  %5.1f G", accX, accY, accZ);

    
  M5.Lcd.setCursor(10, 170);
  M5.Lcd.printf("angX   angY   angZ");
  M5.Lcd.setCursor(10, 192);
  M5.Lcd.printf("%5.1f  %5.1f  %5.1f deg", pitch, roll, yaw);

  bts.print(millis());
  bts.println(millis());
  bts.printf(",");
  bts.print(gyroX); 
  bts.printf(",");
  bts.print(gyroY);
  bts.printf(",");
  bts.print(gyroZ);
  bts.printf(",");
  bts.print(accX); 
  bts.printf(",");
  bts.print(accY);
  bts.printf(",");
  bts.print(accZ);
  bts.printf(",");
  bts.print(pitch); 
  bts.printf(",");
  bts.print(roll);
  bts.printf(",");
  bts.println(yaw);

  if (M5.BtnA.isPressed()) {
    char buffer[50]; 
    sprintf(buffer, "accX:%.1f, accY:%.1f, accZ:%.1f", accX, accY, accZ);
    Serial.println(buffer);
  } else if (M5.BtnB.isPressed()) {
    char buffer[50];
    sprintf(buffer, "gyroX:%.1f, gyroY:%.1f, gyroZ:%.1f", gyroX, gyroY, gyroZ);
    Serial.println(buffer);
  } else if (M5.BtnC.isPressed()) {
    char buffer[50];
    sprintf(buffer, "pitch:%.1f, roll:%.1f, yaw:%.1f", pitch, roll, yaw);
    Serial.println(buffer);
  }
  delay(100);
}