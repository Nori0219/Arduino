#include <M5Core2.h>



void setup() {
  M5.begin();
  explainUsage();//最初に説明を表示
}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased()) {
    displayInfo();//Aを押すと学生情報を表示
  } else if (M5.BtnB.wasReleased()) {
    M5.Lcd.fillScreen(BLACK); //Bを押すと画面を黒でクリア
  } else if (M5.BtnC.wasReleased()) {
    explainUsage();//Cを押すと説明を表示
  }
}

// 学籍番号と名前を表示する関数
void displayInfo() {
  M5.begin();
  M5.Lcd.fillScreen(WHITE); // 画面を白に変更
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(ORANGE);
  M5.Lcd.drawString("420M136", 100, 110); // 画面中央に表示するよう座標設定
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.drawString("SUGII NORICHIKA", 30, 150); // 画面中央に表示するよう座標設定
}
//ボタンの説明を表示する関数
void explainUsage() {
  M5.Lcd.fillScreen(ORANGE); 
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("Button A to show info");
  M5.Lcd.println("Button B to clear screen");
  M5.Lcd.println("Button C to show usage");
}

