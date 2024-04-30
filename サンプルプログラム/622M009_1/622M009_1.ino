#include <M5StickCPlus.h>
void setup()
{
  M5.begin(); 
  M5.Lcd.setTextSize(3);  
  M5.Lcd.setRotation(3);
}
 void loop()
{M5.update();
 if (M5.BtnA.wasReleased()) 
  {  
    M5.Lcd.print('A');  
  M5.Lcd.print("622M009");
  }
}
