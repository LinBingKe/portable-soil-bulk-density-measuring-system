//介面B(啟動量測)
void ControlMeasurement(){
  if(Bmode()==true){
    while((Leave()==false)&&(MeasureFinish==false)){ 
      read31856(1);//顯示環境溫度模式
      delay(500);
      if(Bmode()==true){//進入量測模式
        TimeMove = millis();
        last[0]=TimeMove;
        last[1]=TimeMove;
        last[2]=TimeMove;  
        last[3]=TimeMove;
        last[4]=TimeMove;
        last[5]=TimeMove;                  
//        Serial.println("測試進入數據收集");
        if((TimeMove-last[1])>=intervals[1]){//判斷是否開始量測
          while(CollectTime<=(intervals[4]/1000.0)){//開始量測  
            delay(10);               
//            Serial.println("測試開始收集");
            TimeMove = millis();
            MeasureOpen();//開始量測 
          }
          MeasureFinish=true; 
          LcdBmodeLeave();//Bmode量測完成顯示訊息
          ParameterCaculation();//參數計算                        
        }
        while(Leave()==false){//查看計算的參數
          //Serial.println("進入迴圈輸入含水率");
          InputValue();//利用GetValue存取輸入的值
          switch(GetValue) {//透過Keypad輸入值
            case '1':
              Lcd_TimeTemp();
              break;
            case '2':
              Lcd_PassTimeTemp();
              break;
            case '3':
              Lcd_SoilParameter();
              break;        
            default:
              break;       
          }
          GetValue='z';  
          Leave();//判斷結束輸入模式      
          delay(200);
        }                       
      }    
    }  
  delay(2000);
  LcdBmodeLeave_2(); 
  } 
}


void MeasureOpen(){//開始量測

  if(TimeMove-last[0]>=intervals[0]){//每隔0.5秒量測一次溫度
    last[0]=TimeMove;
    read31856(2); 

    if (HeatControl==1){//判斷是否啟動加熱探針(2)
      HeatControl=0;//禁止加熱探針(2)的判斷
      DelayOpen(); //啟動加熱
      last[3]=TimeMove;
      Serial.print(", heatopen");
  //    Serial.print("收到a ");
  //    Serial.println(a);
      b=1;//允許關閉加熱探針和關閉18V穩壓模組的判斷 
      }  
    if((b==1)&&(TimeMove-last[3]>=intervals[3])){//判斷是否關閉加熱探針
      DelayClose(); 
      }
    if((b==1)&&(TimeMove-last[3]>=(intervals[3]+2000))){//判斷是否關閉18V穩壓模組
      digitalWrite(relay1,HIGH);
      b=0;//禁止關閉加熱探針和關閉18V穩壓模組的判斷   
      }      
    Serial.println("");
  }
  if(((TimeMove-last[2])>=(intervals[2]-5000)) && (repeat==0)){//判斷是否啟動18V穩壓模組
    digitalWrite(relay1,LOW);
  }  
  if(((TimeMove-last[2])>=intervals[2]) && (repeat==0)){//判斷是否啟動加熱探針(1)
    HeatControl=1;
    //Serial.println("加熱");
    repeat=1;
  }
  
  if(TimeMove-last[5]>=intervals[5]){//重複量測
    last[0]=TimeMove;
    last[1]=TimeMove;
    last[2]=TimeMove;  
    last[3]=TimeMove;
    last[4]=TimeMove;   
    last[5]=TimeMove;
    c=0;
    repeat=0;
    //Serial.println("抓到");
    //resetFunc();
  }  
}

void read31856(int x1){//溫度讀取(環境模式/量測模式)
//  Serial.println("測試(進入)read31856");

  delay(10);
  Temp=max.readThermocoupleTemperature();
  
  switch(x1){//選擇模式
    case 1://偵測開啟 記錄關閉
      Serial.print("  31856 : ,");        
      Serial.println(Temp);//在即時監控視窗顯示溫度
      
//      Serial.println("測試進入(a1)"); 
      if((CollectIndex1%2)==0){
//        Serial.println("測試進入(b1)");         
        LcdB_PreMeasure();
//        Serial.println("測試進入(b0)"); 
      }
//      Serial.println("測試離開(a0)");   
       
      CollectIndex1=CollectIndex1+1; 
          
      break;
    case 2://偵測開啟 記錄開啟
      Serial.print("  31856 : ,");
      Serial.print(CollectTime);
      Serial.print(" ,"); 
      Serial.print(Temp);//在即時監控視窗顯示溫度
      CollectTemp[CollectIndex]=Temp;//用陣列儲存溫度
      if((CollectIndex%2)==0){
        LcdB_Measure();//在LCD顯示溫度
      }
      CollectTime=CollectTime+0.5;
      CollectIndex=CollectIndex+1;      
      break;      
    default:
      break; 
  }
//  Serial.println("測試(離開)read31856");           
}
 
void DelayOpen(){//啟動加熱
  digitalWrite(relay2,LOW);
}

void DelayClose(){//關閉加熱
  digitalWrite(relay2,HIGH);
}

//void ControlParameter(){
//  if(Cmode()==true){
//    ParameterCaculation();
////    ShowParameterCaculation();
//  }     
//}
