//以下必要なdefineを設定する。新型は異なる場合があるので注意！stickも無論異なる。
#define M5STACK_MPU6886 
// #define M5STACK_MPU9250 
// #define M5STACK_MPU6050
// #define M5STACK_200Q

//以下のヘッダーファイルも適切に書き換えること。
#include <M5Stack.h>

//以下はタイマー制御とSDカード処理のための必要なので残してあります
#include "time.h" //時間

//タイマー制御関連ヘッダ―
#include <BlynkSimpleEsp32_BT.h>
BlynkTimer timer;

//SDカード関連ヘッダー
#include <SD.h>
#include <SPI.h>


//タイマー制御用変数
unsigned long time_now;
unsigned long old_time;

//SDカード関連変数
char fileName[16];
int fileNum = 0;
File logFile;
int file_flg=0;



//タイマー制御関数部分（一定周期毎に以下のmyTimerEventが呼び出されてその中身が処理される。サンプリング関係の処理のみをこちらに入れる)
void myTimerEvent() {

　//一定周期毎に呼び出されるので必要な処理を書く。



　//ここより下はタイマーの値を呼び出し、SDカードにデータを書き出す部分なので必要に応じて修正すること。

  time_now=millis(); //現在の内部タイマーの値を読む
  
  if(file_flg==1){
    logFile.println((String)time_now+","+(String)gyroX+","+(String)gyroY+","+(String)gyroZ+","+(String)accX+","+(String)accY+","+(String)accZ+","+(String)Vdc);    
  }

  //タイマー周期表示（確認したい場合にはコメントアウトを解除すること
  //M5.Lcd.setCursor(0, 175);
  //M5.Lcd.printf("Samp. Time: %d ms", (time_now-old_time));
  //old_time=time_now;

}


// 以下のsetup()部分はM5stack起動時に１回だけ処理を行う
void setup(){

 //M5stackの初期化関係はここで処理を行うこと。





　//タイマー関連（消さない）
  unsigned long timer_millis_start = millis();

  //SDカード挿入の確認（消さない）
  if(!SD.begin(4)){
    // SDカードがない場合はエラーを出して止まる
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("No SD card!");
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(0, 30); 
    M5.Lcd.print("<< RED Button:Two click POWER OFF"); 
    M5.Lcd.setTextColor(WHITE);
    while(1){
      ;
    }
  }
  //サンプリング周期設定[単位はmsで設定]
  timer.setInterval(10L, myTimerEvent);
}


//以下がメインで処理されるループ
void loop() {
  M5.update();
  
  if (M5.BtnA.wasPressed()&&file_flg==0) {//データロギング開始
    //ファイルネーム設定
    String filenm;
    while(1){
      filenm = "/DAT";
      if (fileNum < 10) {
        filenm += "00";
      }
      else if(fileNum < 100) {
        filenm += "0";
      }
      filenm += fileNum;
      filenm += ".csv";
      filenm.toCharArray(fileName, 16);
      if(!SD.exists(fileName)) break;
      fileNum++;
    }

    //設定ファイル名表示
    M5.Lcd.setCursor(0, 180);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(RED,BLACK);
    M5.Lcd.printf("REC. file:%s ",fileName);
    M5.Lcd.setTextColor(WHITE,BLACK);
    M5.Lcd.setTextSize(1);

    //ファイルオープンとそのチェック
    logFile=SD.open(fileName,FILE_WRITE);
    if(logFile){
      file_flg=1; //書き込み処理開始フラグ
    }else{
      // ファイルが開けない場合はエラーを出して止まる
      M5.Lcd.setTextColor(RED);
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.print("File Open Error!");
      M5.Lcd.setTextSize(1);
      M5.Lcd.setTextColor(WHITE,BLACK);
      while(1){
        ;
      }      
    }
  }
  if (M5.BtnB.wasPressed()&&file_flg==1) {//データロギング停止
    M5.Lcd.setCursor(0, 180);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(WHITE,BLACK);
    M5.Lcd.printf("Close file:%s  ",fileName);
    M5.Lcd.setTextSize(1);
    file_flg=0; //書き込み停止フラグ
    logFile.close();
  }



  timer.run();
}
