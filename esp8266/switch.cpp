#include"Arduino.h"

int switchA0 = 5;//D1
int switchA1 = 4;//D2
int switchA2 = 0;//D3
char cmd;
int t2;//此时间表示换算对于营养液的控制
double waterFlow = 0;//计算水流
void water()
{
  digitalWrite(switchA0, HIGH);
  digitalWrite(switchA1, HIGH);
  digitalWrite(switchA2, HIGH);
  switch (cmd) {
    case 'a':
      Serial.println("add the A state");
      digitalWrite(switchA0, LOW);
      break;
    case 'b':
      Serial.println("add the B state");
      digitalWrite(switchA1, LOW);
      break;
    case 'w':
      Serial.println("add the water state");
      digitalWrite(switchA2, LOW);
      break;
  }
  digitalWrite(switchA0, LOW);
  delay(1000);
  digitalWrite(switchA1, LOW);
  delay(1000);
  digitalWrite(switchA2, HIGH);
  delay(1000);
}

//void plant1()//Y0 Y1 Y2  对应A B 水
//{
//  digitalWrite(switchA0,LOW);
//  digitalWrite(switchA1,LOW);
//  digitalWrite(switchA2,LOW);
//}
void flow()   //measure the quantity of square wave
{
  waterFlow += 1.0 / 5880.0;
}
