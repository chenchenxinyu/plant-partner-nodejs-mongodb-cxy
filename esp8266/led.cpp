#include"Arduino.h"
#include "FastLED.h"
#define NUM_LEDS 46

//变量声明
CRGB leds[NUM_LEDS]; //数组定义
int t1;//表示处理后的时间，即在该周期内处于什么时间，该时间从服务器获取

/////////////////////////////////灯控函数/////////////////////////////
void LedControl()
{
  for (int i = 0; i < 12; i++)
  {
    leds[i] = CRGB(155, 155, 155);
    //FastLED.show();
  }
  for (int i = 12; i <24 ; i++)
  {
    leds[i] = CRGB(155, 0, 0);
    //delay(100);
    //FastLED.show();
  }  
  for (int i = 25; i <36 ; i++)
  {
    leds[i] = CRGB(155, 0, 155);
    //delay(100);
    //FastLED.show();
  }
  for (int i = 36; i <47 ; i++)
  {
    leds[i] = CRGB(0, 0, 155);
    //delay(100);
    
  }
  FastLED.show();
  if (t1==1)
  {
    Serial.println("get the time for led!");
  }
  delay(1000);
}
