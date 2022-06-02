#include "BC26Init.h"
//BC26模組使用
String MQTT_Server="iiot.ideaschain.com.tw";  //MQTT Server 的 IP 位址
String MQTT_Port="1883";                          //MQTT 使用的埠
String MQTT_Access_token="c7rIs1kHgk9WowAqbyK6";      //使用者密碼 ==> IDEAS Chain存取權杖
String MQTTtopic="v1/devices/me/telemetry";   //固定路徑 IDEAS Chain 
String MQTTmessage="";  
String MQTTattrestopic="v1/devices/me/attributes/response/+";  //訂閱資料路徑 IDEAS Chain
String MQTTattreqtopic="v1/devices/me/attributes/request/1";   //訂閱資料路徑 IDEAS Chain
String DelayTime_Text="DelayTime";             // 共享屬性的字串資料來取得暫停傳送的秒數
String TempHigh_Text="TempHigh";               // 共享屬性的字串資料來設定高溫參考值
String TempLow_Text="TempLow";                 // 共享屬性的字串資料來設定低溫參考值
byte mode=0;                                   // 0 => 讀取共享屬性資料  1 => 讀取客戶端屬性資料
String DelayTime;
String TempHigh;
String TempLow;

//intervals[0]採樣頻率(ms)
//intervals[1]開始量測(ms)
//intervals[2]啟動加熱(ms)
//intervals[3]加熱持續時間(ms)
//intervals[4]量測時間(ms)
//intervals[5]重複量測時間(ms)
unsigned long intervals[] = {500,0,30000,10000,120000,120000}; //this defines the interval for each task in milliseconds      
unsigned long last[] = {0,0,0,0,0,0};           
unsigned long TimeMove;

//使用SD卡模組
#include <SPI.h>
#include <SD.h>
#define PIN9 PA4
File myFile;
char DataName[5];//存取數據的陣列
int DataNameIndex;
String file_name="";
String update_name="";
//Keypad的變數宣告

#define PIN1 PB11
#define PIN2 PB10
#define PIN3 PB1
#define PIN4 PB0
#define PIN5 PA3
#define PIN6 PA2
#define PIN7 PA1
#define PIN8 PA0

  
char ValueInput[5];//存取含水率的陣列
int ValueIndex;
char GetValue;
byte scanVal;   // 暫存掃描到的按鍵值
const byte colPins[4] = {PIN1, PIN2, PIN3, PIN4}; // 設定「行」腳位
const byte rowPins[4] = {PIN5, PIN6, PIN7, PIN8}; // 設定「列」腳位
const char keymap[4][4] = {// 設定按鍵的「行、列」代表值
    {'D','#','0','.'}, 
    {'C','9','8','7'}, 
    {'B','6','5','4'},
    {'A','3','2','1'}
};

// 使用adafruit31856 溫度讀取模組 Use software SPI: CS, DI, DO, CLK
#include <Adafruit_MAX31856.h>
#define SCK_PIN PB13
#define SDO_PIN PB14
#define SDI_PIN PB15
#define CS_PIN PB12
Adafruit_MAX31856 max = Adafruit_MAX31856(CS_PIN,SDI_PIN,SDO_PIN,SCK_PIN);

float Temp;

//LCD顯示
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//繼電器用
#define relay1 PB3
#define relay2 PA15

//
int b=0;
int HeatControl=0;
int repeat=0;//重複量測
bool LCDcontrol;

//記錄溫度並計算最高溫度,經過時間
float CollectTemp[360];
float CollectTime=0;
int CollectIndex1=0;
int CollectIndex=0;
float PassTime;
float PassTemp;


float Capacity;
float GetTaylorSeries;
float Density;

//參數抓取和參數計算
float FirstTime;
float SecondTime;
float FirstTemp;
float SecondTemp;
float EnvAverage=0;
float CollectTemp2[360];

//計算熱容量
float Power = 450.0*0.71;
float HeatTime = 10.0;
float Radius = 0.008;
double WaterContent;
float SolidCapacity = 0.9;  
  
//定義判斷
bool MStart=false;
bool MENCcalibrate=false;
bool MeasureFinish=false;
bool MHeating=false;
bool MCollect=false;
bool DParameter=false;
bool DCapacity=false;
bool MBluetooth=false;
bool Update=false;

int again=0;

float c=0;
// the setup function runs once when you press reset or power the board

//重置
//void(* resetFunc) (void) = 0;

void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("測試(進入)setup");

// 各項參數開始初始化=============

  delay(100);
  pinMode(PC13,OUTPUT);//BC26初始化
  digitalWrite(PC13, LOW);
  delay(30);
  digitalWrite(PC13, HIGH);
  delay (3000);
  KeypadInit();//Keypad感測器初始化
  LCDsensorInit();//LCD顯示器初始化 
  A_ValueInitial();//含水率陣列初始化
  DataNameInitial();//文件名稱初始化
  //感模組初始化
  if (!max.begin()) {
    Serial.println("Could not initialize thermocouple.");
    while (1) delay(400);
  }
  max.setThermocoupleType(MAX31856_TCTYPE_K);  
  Serial.println("Max31856初始化完畢");   
  //加熱繼電器初始化
  pinMode(relay1,OUTPUT);
  digitalWrite(relay1,HIGH);
  pinMode(relay2,OUTPUT);
  digitalWrite(relay2,HIGH); 
  Serial.println("加熱繼電器初始化完畢"); 
//============ 各項參數初始化完畢

  Serial.println("(測試)離開setup"); 
}

// the loop function runs over and over again forever
void loop()
{
  ControlInputWatercontent();
  ControlMeasurement();
  ParameterCaculation();
  ControlSD();
  ControlUpdate();

//  delay(10000000); 
}
