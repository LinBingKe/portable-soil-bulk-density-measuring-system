//介面C(計算參數)
//void ParameterCaculation(){
////  for(int i=0;i<CollectIndex;i++){
////      Serial.print("Index");
////      Serial.print(i);
////      Serial.print("   ");
////      Serial.println(CollectTemp[i]);
////  }  
//  C_firstTT();
//  C_secondTT();   
//  Serial.println("測試");
//  Serial.print("初始溫度的時間");
//  Serial.println(FirstTime);
//  Serial.print("初始溫度");
//  Serial.println(FirstTemp);
//  Serial.print("最大溫度的時間");
//  Serial.println(SecondTime);
//  Serial.print("最大溫度");
//  Serial.println(SecondTemp);
//
//  PassTime=SecondTime-FirstTime;
//  PassTemp=SecondTemp-FirstTemp;     
//  Serial.print("最大上升溫度");
//  Serial.println(PassTemp);
//  Serial.print("經過時間");
//  Serial.println(PassTime);
//
//  GetTaylorSeries=TaylorSeries(HeatTime,PassTime); //泰勒展開式
//  Capacity=(Power*HeatTime/M_E/M_PI/Radius/Radius/PassTemp)*(GetTaylorSeries/1000000);//計算體積熱容量
//
//  Serial.println("顯示Capacity");
//  Serial.println(Capacity);
//  Density = (Capacity-4180000.0*WaterContent)/SolidCapacity/1000000;
//  //      Serial.print("Power");
//  //      Serial.println(SetParameter(1));
//  //      Serial.print("HeatTime");
//  //      Serial.println(SetParameter(2));
//  //      Serial.print("Radius");
//  //      Serial.println(SetParameter(3));
//  //      Serial.print("TimePass");
//  //      Serial.println(SetParameter(4));
//  //      Serial.print("TemperPass");
//  //      Serial.println(SetParameter(5));
//  //      Serial.print("GetTaylorSeries");
//  //      Serial.println(GetTaylorSeries);
//}

void ParameterCaculation(){
  double eTime[9]={48,39.5,45,36.5,35,48.5,37,40.5,38.5};
  double eTemp[9]={2.25,2.48,2.49,2.93,2.77,2.97,2.74,2.77,3.02};
  double eWater[9]={0.245,0.285,0.3,0.25,0.2,0.195,0.185,0.19,0.19};
  double Capacity[9];
  double Density[9];
  
  for(int i=0;i<=8;i++){
    GetTaylorSeries=TaylorSeries(HeatTime,eTime[i]); //泰勒展開式
    Capacity[i]=(Power*HeatTime/M_E/M_PI/Radius/Radius/eTemp[i])*(GetTaylorSeries/1000000);//計算體積熱容量
    Serial.print(Capacity[i]); 
    Serial.print(","); 
  }
  Serial.println(""); 
  for(int i=0;i<=8;i++){
    Density[i] = (Capacity[i]-4180000.0*eWater[i])/SolidCapacity/1000000;
    Serial.print(Density[i]);
    Serial.print(",");        
  }  
}

//紀錄起始溫度和時間
void C_firstTT(){  
    FirstTime=30; 
//    for(int i=0;i<30;i++){
//      EnvAverage=EnvAverage+CollectTemp[i];
//    }

    FirstTemp=CollectTemp[59];
    
//    for(int i=0;i<CollectIndex;i++){
//      CollectTemp2[i]=CollectTemp[i];
//    }  
}

//紀錄到達最高溫和時間
void C_secondTT(){
    SecondTemp=CollectTemp[59];
    SecondTime=30;
  //   Serial.println(CollectIndex);
    
    for(int i=59;i<CollectIndex;i++){
      if(SecondTemp<CollectTemp[i]){
         SecondTemp=CollectTemp[i];
         SecondTime=i;
         
  //        Serial.println("第一階層換");
  //        Serial.print(i);
  //        Serial.print(" ");
  //        Serial.println(SecondTemp);
        
         for(int j=i;j<CollectIndex;j++){
            if (SecondTemp < CollectTemp2[j]){
              SecondTemp=CollectTemp[j];
              SecondTime=j;
              
  //              Serial.println("第二階層換");
  //              Serial.print(j);
  //              Serial.print(" ");
  //              Serial.println(SecondTemp);
  
            }   
         }
      }
      
  //      Serial.print("比較次數");
  //      Serial.println(i);
    }

    SecondTime=SecondTime/2.0;  
}
    
//泰勒展開式
float TaylorSeries(int t0 ,int tm){ 
  float a=(float)t0/tm;//使用float強制轉型
  float simply1;
  float simply2;
  float simply3;
  float simply4;
  simply1=5000000/2+7000000*t0/tm/3;
  simply2=simply1*t0/tm/8+1000000/3;
  simply3=simply2*t0/tm+1000000/3;
  simply4=1000000-simply3*t0*t0/tm/tm/8;
  return simply4;
// Serial.println("a"); 
// Serial.println(a,7);
// Serial.println("simply1"); 
// Serial.println(simply1,7);
// Serial.println("simply2");
// Serial.println(simply2,7);
// Serial.println("simply3");
// Serial.println(simply3,7);
// Serial.println("simply4");
// Serial.println(simply4,7);
}
