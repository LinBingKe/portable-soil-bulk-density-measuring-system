//介面A(體積含水率)
void ControlInputWatercontent(){
  if(Amode()==true){
    Serial.println("Input water(%)");
    LcdA_Watercontent(1);
    LcdA_Watercontent(2);
    LcdA_Watercontent(3);
    LcdA_Watercontent(4);
    
    while(Leave()==false){//進入迴圈輸入含水率
      //Serial.println("進入迴圈輸入含水率");
      InputValue();//利用GetValue存取輸入的值
      switch(GetValue) {//透過Keypad輸入值
        case '1':
          Value(1);
          break;
        case '2':
          Value(1);
          break;
        case '3':
          Value(1);
          break;
        case '4':
          Value(1);
          break;
        case '5':
          Value(1);
          break;
        case '6':
          Value(1);
          break;
        case '7':
          Value(1);
          break;
        case '8':
          Value(1);
          break;
        case '9':
          Value(1);
          break;
        case '0':
          Value(1);
          break;
        case '.':
          Value(1);
          break; 
        case 'D':
          Value(2);
          break;           
        default:
          break;       
      }  
      ValueShow();//ValueInput陣列(資料顯示) 
      GetValue='z';
      Leave();//判斷結束輸入模式      
      delay(200);
    }
    LcdAmodeLeave();//Amode含水率設定完成顯示訊息
    delay(100);
    Input_Water();//設定含水率 
    delay(100);     
  }
}

//含水率陣列初始化
void A_ValueInitial(){
  for(int i=0;i<=4;i++){
  ValueInput[i]=32;
  }
  Serial.println("A_ValueInitial初始化完畢");
}

void Value(int x1){//ValueInput陣列(存取輸入的含水率數據)
  if((x1==1)&&(ValueIndex<5)){//輸入
    Serial.print("測試索引值");
    Serial.println(ValueIndex);
    ValueInput[ValueIndex]=GetValue;
    LcdA_Lvalue();
    ValueIndex++;   
  }
  if((x1==2)&&(ValueIndex>0)){//刪除
    Serial.print("測試索引值");
    Serial.println(ValueIndex);        
    ValueIndex--;   
    ValueInput[ValueIndex]=32;
    LcdA_Lvalue();
  }
}

void ValueShow(){//ValueInput陣列(資料顯示) 
  
  Serial.println("");
  for(int i=0;i<=4;i++){
    Serial.print(ValueInput[i]);
  }
//  Serial.println("");  
//  Serial.println("測試開始轉換");
//  Serial.println(Change(ValueInput[0]));  
//  Serial.println("測試轉換完畢");
  Serial.println("");
}

void Input_Water(){//完成設定WaterContent存取輸入值
  String test;
  for(int i=0;i<=4;i++){
    if(ValueInput[i]=='.'){
      if(i==1){
        WaterContent=Change(ValueInput[0])*1000+Change(ValueInput[2])*100+Change(ValueInput[3])*10;
      }
      if(i==2){
        WaterContent=Change(ValueInput[0])*10000+Change(ValueInput[1])*1000+Change(ValueInput[3])*100+Change(ValueInput[4])*10;
      }

      Serial.println("測試InputWatercontent()   ");

      Serial.println(WaterContent);
      WaterContent=double(WaterContent/100000.0);
      Serial.println(double(WaterContent));
      Serial.println("測試完畢InputWatercontent()");      
      
    }
  }
}

int Change(char xValue){//輸入值變數型態轉換(char->int)
      switch(xValue) {
        case '1':
          return 1;
          break;
        case '2':
          return 2;
          break;
        case '3':
          return 3;
          break;
        case '4':
          return 4;
          break;
        case '5':
          return 5;
          break;
        case '6':
          return 6;
          break;
        case '7':
          return 7;
          break;
        case '8':
          return 8;
          break;
        case '9':
          return 9;
          break;
        case '0':
          return 0;
          break;          
        default:
          break;       
      }    
}
