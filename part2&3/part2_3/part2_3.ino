#define M5STACK_MPU6886
#include <M5Core2.h>

// 加速度センサーの各軸の値を格納する変数
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

// ジャイロセンサーの各軸の値を格納する変数
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

// 姿勢角を表す変数
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

unsigned long startTime = 0;//時間
int mode = 0; 

void setup() {
  M5.begin(); 
  Serial.begin(9600); // シリアル出力初期化
  M5.IMU.Init(); // 慣性計測ユニット(IMU)の初期化
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  

 // 出力を囲む枠を描画
 M5.Lcd.drawRect(0, 15, 320, 45, DARKGREY);
 M5.Lcd.drawRect(0, 85, 320, 45, DARKGREY);
 M5.Lcd.drawRect(0, 155, 320, 45, DARKGREY);
 // 設定ボタン項目表示
 M5.Lcd.drawRect(20, 217, 100, 23, DARKGREY);  // ボタン枠
 M5.Lcd.setTextColor(BLACK, DARKGREY);
 M5.Lcd.setCursor(24, 221);    M5.Lcd.print(" change ");  // 0セットボタン
}

void loop() {
  M5.update();

  //慣性センサーの3軸ジャイロデータを関連変数に格納
  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
  M5.IMU.getAccelData(&accX,&accY,&accZ);//三軸加速度センサー
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);//慣性センサーの姿勢

  // ジャイロセンサーの出力
  M5.Lcd.setTextColor(RED, BLACK);
  M5.Lcd.setCursor(20, 20); 
  M5.Lcd.printf("gyroX,  gyroY, gyroZ"); 
  M5.Lcd.setCursor(20, 42);
  M5.Lcd.printf("%6.2f %6.2f%6.2f o/s", gyroX, gyroY, gyroZ);

  // 加速度センサーの出力
  M5.Lcd.setTextColor(BLUE, BLACK);
  M5.Lcd.setCursor(20, 90);
  M5.Lcd.printf("accX,   accY,  accZ");
  M5.Lcd.setCursor(20, 112);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);

  // 姿勢の出力
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setCursor(20, 160);
  M5.Lcd.printf("pitch,  roll,  yaw");
  M5.Lcd.setCursor(20, 182);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f deg", pitch, roll, yaw);

  // Aボタンで測定モード切り替え
  if (M5.BtnA.wasPressed()) { mode++; } 
  if (mode == 3) { mode = 0; }
  switch (mode) { // modeによって出力データを切り替え
  case 0:
    Serial.printf("accX, accY, accZ");     
    Serial.printf("%7.2f, %7.2f, %7.2f\n", accX, accY, accZ);   // 加速度
    break;
  case 1:
    Serial.printf("gyroX, gyroY, gyroZ");      
    Serial.printf("%7.2f, %7.2f, %7.2f\n", gyroX, gyroY, gyroZ);// 角速度
    break;
  case 2:
    Serial.printf("pitch, roll, yaw"); 
    Serial.printf("%7.2f, %7.2f, %7.2f\n", pitch, roll, yaw);   // 姿勢角
    break;
  }

  // unsigned long elapsedTime = millis() - startTime; // 経過時間を計算
  // float seconds = elapsedTime / 1000.0; // 秒に変換

  // Serial.printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", seconds, accX, accY, accZ, gyroX, gyroY, gyroZ, pitch, roll, yaw);
  delay(150);
}
