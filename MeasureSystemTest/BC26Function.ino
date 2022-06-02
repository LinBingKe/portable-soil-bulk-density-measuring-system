//BC26初始化
void BC26FunctionInit(){
   if (!BC26init()) {
    Serial.println("bc26沒有反應");
    delay (10000); 
    nvic_sys_reset();
    }
   Serial.println("BC26Init初始化完畢");
}

bool Get_ideaschain_data(String attrestopic,String attreqtopic)  //讀取在網站設定的共享屬性資料
{
  Sub_Ideaschain(attrestopic);
  DelayTime=Get_Publish_MQTT(mode,attreqtopic,DelayTime_Text); 
  TempHigh=Get_Publish_MQTT(mode,attreqtopic,TempHigh_Text);
  TempLow=Get_Publish_MQTT(mode,attreqtopic,TempLow_Text);
  
  if (DelayTime.toInt()!=0 && TempHigh.toInt()!=0 && TempLow.toInt()!=0 )
  {
  Serial.println("取得暫停秒數 : " + DelayTime + " 秒");
  Serial.println("取得設定最高溫 : " + TempHigh + " °C");
  Serial.println("取得設定最低溫 : " + TempLow + " °C");
  return true;
  }
  return false;
}


void SendData(){
  if (connect_MQTT(MQTT_Server,MQTT_Port,MQTT_Access_token,MQTT_Access_token)){
    Rset_Count++;
    Serial.println("上傳資料.....");
    delay(500);
    String Sensor1="D"+update_name;
    String Sensor2="W"+update_name; 
    MQTTmessage="\"{\"" + Sensor1 + "\":" +  Density + "," + "\"" + Sensor2 + "\":" +  WaterContent + "}\"";
    if (Publish_MQTT(MQTTtopic,MQTTmessage))
    {
    Rset_Count=0;
    }
  }
  Close_MQTT();
  Serial.println("暫停 " + DelayTime +" 秒後再傳送 !!"); 
  delay (DelayTime.toInt()*1000);
  if (Rset_Count>20) {delay (10000);nvic_sys_reset();}    
}
