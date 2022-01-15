/*
  Arduino控制NEMA步进电机测试程序 （2018-09-25）
  by 太极创客（www.taichi-maker.com）
  本示例程序旨在演示如何通过Arduino控制NEMA步进电机。
  用户可通过串口监视器控制电机的各个功能
  如需获得本示例程序详细电路信息以及如何使用Arduino控制电机的更多知识，请参考太极创客网站：
  http://www.taichi-maker.com/homepage/reference-index/motor-reference-index/arduino-a4988-nema-stepper-motor/
  
  控制指令：
  顺时针旋转/逆时针旋转 - x0/x1
  运行步数 - z100(走100步)
  步进方式 - b1(全步),b2(半步),b4(四分),b8(8分),b16(16分)
  速度 - d2000(转动速度2000)
  允许工作/禁止工作(enable/disable) - g1/g0
  睡眠 - m0（sleep)/m1（awake)  
*/
 
// A4988引脚连接Arduino引脚编号
const int dirPin   = 2;   // Direction
const int stepPin  = 3;   // Step
const int sleepPin = 4;   // Sleep
const int resetPin = 5;   // Reset
const int ms3Pin   = 6;   // Ms3
const int ms2Pin   = 7;   // Ms2
const int ms1Pin   = 8;   // Ms1
const int enPin    = 9;   // Enable
 
// 步进电机旋转一周步数
const int STEPS_PER_REV = 200;
 
char cmd;  //用户指令字符
int data;  //用户指令数据
int motorSpeed = 2000;  //电机转速(数值越小速度越小)
 
void setup() { 
  // 设置引脚模式
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(sleepPin,OUTPUT); 
  pinMode(resetPin,OUTPUT);  
  pinMode(ms3Pin,OUTPUT);  
  pinMode(ms2Pin,OUTPUT);  
  pinMode(ms1Pin,OUTPUT); 
  pinMode(enPin,OUTPUT);   
 
  // 初始化引脚状态
  digitalWrite(sleepPin, HIGH);  
  digitalWrite(resetPin, HIGH); 
  digitalWrite(enPin, LOW); 
 
  // 初始化电机步进模式为全步进
  digitalWrite(ms1Pin, LOW); 
  digitalWrite(ms2Pin, LOW); 
  digitalWrite(ms3Pin, LOW); 
 
  Serial.begin(9600);
  Serial.println("++++++++++++++++++++++++++++++++++");     
  Serial.println("+ Taichi-Maker A4988 Steper Demo +");   
  Serial.println("+     www.taichi-maker.com       +");  
  Serial.println("++++++++++++++++++++++++++++++++++");  
  Serial.println("");  
  Serial.println("Please input motor command:"); 
}
 
void loop() {    
  if (Serial.available()) {     // 检查串口缓存是否有数据等待传输 
    cmd = Serial.read();        // 获取电机指令中电机编号信息    
    Serial.print("cmd = ");
    Serial.print(cmd);    
    Serial.print(" , "); 
 
    data = Serial.parseInt();
    Serial.print("data = ");
    Serial.print(data);   
    Serial.println("");    
 
    runUsrCmd();
  }
} 
 
//此函数用于运行用户指令
void runUsrCmd(){
  switch(cmd){ 
    case 'x':    // 设置步进电机旋转(顺时针/逆时针)
      Serial.print("Set Rotation To "); 
      if (data == 0){
        digitalWrite(dirPin, 0);
        Serial.println("Clockwise."); 
      } else {
        digitalWrite(dirPin, 1);
        Serial.println("Counter Clockwise."); 
      }
      break;
    
    case 'g':   // 设置A4988 enable功能
      Serial.print("Set Motor To "); 
      if (data == 0){
        digitalWrite(enPin, 1);
        Serial.println("Disable."); 
      } else {
        digitalWrite(enPin, 0);
        Serial.println("Enable."); 
      }
      break;
      
    case 'm':  // 设置A4988 sleep功能
      Serial.print("Set Motor To "); 
      if (data == 0){
        digitalWrite(sleepPin, 0);
        Serial.println("Sleep."); 
      } else {
        digitalWrite(sleepPin, 1);
        Serial.println("Awake."); 
      }
      break;
 
    case 'b':   // 设置步进模式
      if (data == 1 || data == 2  || data == 4  || data == 8 || data == 16){
        Serial.print("Set Motor Step Control To "); 
        setStepMode(data);
      } else {
        Serial.println("Wrong Step Mode Cmd!");
      }
      break;
 
    case 'z': // 设置步进电机运行步数
      runStepper(motorSpeed, data);
      break;
 
    case 'd': // 设置步进电机运行速度      
      motorSpeed = data;
      Serial.print("Set Motor Speed To ");
      Serial.println(data);
      break;
          
    default:  // 未知指令
      Serial.println("Unknown Command");
  }
}
 
//运行步进电机
void runStepper (int rotationSpeed, int stepNum){
  for(int x = 0; x < stepNum; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(rotationSpeed); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(rotationSpeed); 
  }  
}
 
 //设置步进模式
void setStepMode(int modeNum){ 
  switch(modeNum){ 
    case 1:   // 全步进
    digitalWrite(ms1Pin, LOW); 
    digitalWrite(ms2Pin, LOW); 
    digitalWrite(ms3Pin, LOW);  
    Serial.println(F("Stepping Mode: Full"));
    break; 
 
    case 2:  // 半步进  
    digitalWrite(ms1Pin, HIGH); 
    digitalWrite(ms2Pin, LOW); 
    digitalWrite(ms3Pin, LOW);  
    Serial.println(F("Stepping Mode: 1/2"));
    break; 
 
    case 4:  // 1/4 步进   
    digitalWrite(ms1Pin, LOW); 
    digitalWrite(ms2Pin, HIGH); 
    digitalWrite(ms3Pin, LOW);  
    Serial.println(F("Stepping Mode: 1/4"));
    break;     
 
    case 8:  // 1/8 步进   
    digitalWrite(ms1Pin, HIGH); 
    digitalWrite(ms2Pin, HIGH); 
    digitalWrite(ms3Pin, LOW);  
    Serial.println(F("Stepping Mode: 1/8"));
    break;  
 
    case 16:  // 1/16 步进   
    digitalWrite(ms1Pin, HIGH); 
    digitalWrite(ms2Pin, HIGH); 
    digitalWrite(ms3Pin, HIGH); 
    Serial.println(F("Stepping Mode: 1/16")); 
    break;    
  }      
}
