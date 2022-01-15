#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ESP8266WiFiMulti.h>   // 使用WiFiMulti库 
#include <ArduinoJson.h>  //json数据解析库
#include "FastLED.h"
#include "led.h"
#include "switch.h"

#define NUM_LEDS 46
#define DATA_PIN 2  //灯引脚定义  D4
#define Addr_SHT30 0x44  //IIC地址为0x44
#define SDA_PIN 14   //温湿度传感器的引脚接口  D5  白色接线
#define SCL_PIN 12   //D6  黄色接线

/////////////////////////////和wifi设置有关的变量和函数声明////////////////////////////////////////////
ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是 'wifiMulti'
bool buttonState;       //存储客户端按键控制数据
int length; //存储客户端发送的浮点型测试数据
int position = 1;     //存储客户端发送的整数型测试数据
int cont = 0;
int LEDcont = 0;
int LEDstatus = HIGH;
const char* host = "47.108.54.157";    // 即将连接服务器网址/IP
const int httpPort = 8001;               // 即将连接服务器端口
String httpResponseString;
/////////////////////////////以下是要向服务器发送的信息///////////////////////////////////////////////////////////////////
float temperature = -1;  //温度数据
float humidity = -1;  //湿度数据
float light = -1;  //光照强度数据
String weather = "";  //天气数据
int id = 1;  //这是传感器的id号，不要写错了
/////此处存疑  double和float不同的数制转换会不会影响编码
int hoursPass = 0;  //这是从种菜开始以来经过的小时数
bool mixWater;  //这是是否要混合水的标志位，以后可以用于远程控制
int loopcont = 0;  //这是循环个数的标志位
int weatherCont = 0;  //这是获取天气数据的标志位
const int bufferLength = 10;
char serialBuffer[bufferLength];

void setup(void)  {
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(9600);                  // 启动串口通讯
  //Serial.println("serial start success!");
  delay(1000);  //延迟保证串口开启
  pinMode(switchA0, OUTPUT);
  pinMode(switchA1, OUTPUT);
  pinMode(switchA2, OUTPUT);
  //waterFlow = 0;
  //attachInterrupt(0, pulse, RISING);

  wifiSetUp();  //进行wifi初始化
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); //灯控初始化
  t1 = 1;
}

void loop(void) {
  if (Serial.available()) {     // 检查串口缓存是否有数据等待传输
    cmd = Serial.read();
    water();
  }
  LedControl();
  water();
  if(loopcont >= 2*10){
      wifiClientRequest();  //向服务器发送信息的函数
      cont = 0;
      weatherCont++;
      if(weatherCont >= 2){
          weatherRequest();
          weatherCont=0;
        }
    }
  
  //delay(20000);
  unsigned int data[6]; //存储获取到的六个数据
  Wire.beginTransmission(Addr_SHT30);
  //发送测量命令 0x2C06,但是因为IIC一次只能发一个8位数据，所以得发两次
  Wire.write(0x2C);
  Wire.write(0x06);
  Wire.endTransmission();
  //等待500ms是等待SHT30器件测量数据，实际上这个时间可以很短
  delay(500);
  //请求获取6字节的数据，然后会存到8266的内存里
  Wire.requestFrom(Addr_SHT30, 6);
  //读取6字节的数据
  //这六个字节分别为：温度8位高数据，温度8位低数据，温度8位CRC校验数据
  //               湿度8位高数据，湿度8位低数据，湿度8位CRC校验数据
  if (Wire.available() == 6)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }
  float cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  //float fTemp = (cTemp * 1.8) + 32;  华氏度
  float humidity1 = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
  temperature = cTemp;  
  humidity = humidity1;
  loopcont++;
}


/////////////////////////////////这是传感器收发传输相关的函数////////////////////////////////////////////
//
void send_sensor_data()
{
  uint8_t charArr[4];//四字节数组
  uint8_t *p;
  p = (uint8_t*) &light;

  for (int i = 0; i < 4; i++) {
    charArr[i] = *p++;
  }

  Serial.write(charArr, 4); //串口得到的是逆序的十六进制数
  Serial.println("send hex success.");
  delay(2000);
}
void receive_sensor_data()
{
  light = Serial.readBytes(serialBuffer, bufferLength);
  for (int i = 0; i < bufferLength; i++)
  { // 然后通过串口监视器输出readBytes
    Serial.print(serialBuffer[i]);  // 函数所读取的信息
  }
  Serial.println("received data.");
  delay(2000);

}



/////////////////////////////////这是wifi相关的函数///////////////////////////////////////////////////
//wifi初始化函数
void wifiSetUp() {
  wifiMulti.addAP("Chloris", "12344321"); // 将需要连接的一系列WiFi ID和密码输入这里
  wifiMulti.addAP("cxy", "00000000"); // 将需要连接的一系列WiFi ID和密码输入这里
  //wifiMulti.addAP("a", "12345678"); // ESP8266-NodeMCU再启动后会扫描当前网络

  Serial.println("Connecting ...");                            // 则尝试使用此处存储的密码进行连接。

  while (wifiMulti.run() != WL_CONNECTED) { // 尝试进行wifi连接。
    delay(250);
    Serial.print('.');
  }

  // WiFi连接成功后将通过串口监视器输出连接成功信息
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // 通过串口监视器输出连接的WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // 通过串口监视器输出ESP8266-NodeMCU的Ip
}
//wifi发送请求函数
void wifiClientRequest() {
  WiFiClient client;
  // 将需要发送的数据信息放入客户端请求
  String url = "/Chloris/sensorUpload?id=" + String(id) +
               "&temperature=" + String(temperature) + "&light=" + String(light) + "&humidity=" + String(humidity);

  // 建立字符串，用于HTTP请求
  String httpRequest =  String("GET ") + url + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";

  Serial.print("Connecting to ");
  Serial.print(host);

  if (client.connect(host, httpPort)) {  //如果连接失败则串口输出信息告知用户然后返回loop
    Serial.println(" Sucess");
    client.print(httpRequest);          // 向服务器发送HTTP请求
    Serial.print("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
    Serial.println(httpRequest);
    while (client.connected() || client.available()) {
      if (client.available()) {
        httpResponseString = client.readStringUntil('\n');  //这是接收服务器返回的信息
        Serial.println(httpResponseString);
      }
    }
  } else {
    Serial.println(" failed");
  }
  //json数据解析
  DynamicJsonDocument  jsonBuffer(400);
  deserializeJson(jsonBuffer, httpResponseString);
  JsonObject root = jsonBuffer.as<JsonObject>();
  String res = root["absTime"];
  hoursPass = res.toInt();
  String res1 = root["mixFlag"];
  if (res1 == "false") {
    mixWater = false;
  } else {
    mixWater = true;
  }
  Serial.println("All Data Received!");
  client.stop();
}

//wifi发送请求函数
void weatherRequest() {
  WiFiClient client;
  // 将需要发送的数据信息放入客户端请求
  String url = "/Chloris/weather";

  // 建立字符串，用于HTTP请求
  String httpRequest =  String("GET ") + url + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n" +
                        "\r\n";

  Serial.print("Connecting to ");
  Serial.print(host);

  if (client.connect(host, httpPort)) {  //如果连接失败则串口输出信息告知用户然后返回loop
    Serial.println(" Sucess");
    client.print(httpRequest);          // 向服务器发送HTTP请求
    Serial.print("Sending request: ");// 通过串口输出HTTP请求信息内容以便查阅
    Serial.println(httpRequest);
    while (client.connected() || client.available()) {
      if (client.available()) {
        httpResponseString = client.readStringUntil('\n');  //这是接收服务器返回的信息
        Serial.println(httpResponseString);
      }
    }
  } else {
    Serial.println(" failed");
  }
  //json数据解析
  DynamicJsonDocument  jsonBuffer(400);
  deserializeJson(jsonBuffer, httpResponseString);
  JsonObject root = jsonBuffer.as<JsonObject>();
  String res = root["weatherString"];
  Serial.println(res);
  weather = res;
  Serial.println("All Data Received!");
  client.stop();
}


//////////////////////////////////////////////////////////////////////////////////////////////
