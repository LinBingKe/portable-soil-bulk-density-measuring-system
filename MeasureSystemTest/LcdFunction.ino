//LCD
//LCD顯示器(初始化)
void LCDsensorInit(){
    lcd.init();
    lcd.backlight();

    lcd.setCursor(0,0);
    lcd.print("  DPHP sensor   ");//11/16字元
    delay(300);    
    lcd.setCursor(0,1);
    lcd.print("Starting......  ");//14/16字元  
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("Welcome using   ");//13/16字元
    Serial.println("LCD初始化完畢");
}

//LCD顯示器(訊息清除)
void LcdWhite(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}

//LCD顯示器(通用訊息)
void LcdBlack(){
  lcd.setCursor(0,0);
  lcd.print("Welcome using...");
  lcd.setCursor(0,1);
  lcd.print("Select Function ");
//  lcd.print("                ");
}
    
//LCD顯示器(Amode)
void LcdA_Watercontent(int x1){
    if(x1==1){//Lcd清除顯示訊息
      LcdWhite();
    }
    if(x1==2){//Lcd顯示上行訊息"WaterContent    "
      LcdA_H();
    }
    if(x1==3){//Lcd顯示下行訊息"Input         % "
      LcdA_L();
    }
    if(x1==4){//Lcd顯示輸入的含水率
      LcdA_Lvalue();
    }         
}
void LcdA_H(){//Lcd顯示上行訊息"WaterContent    "
  lcd.setCursor(0,0);
  lcd.print("WaterContent    ");
//  lcd.print("                ");  
}
void LcdA_L(){//Lcd顯示下行訊息"Input         % "
  lcd.setCursor(0,1);
  lcd.print("Input         % ");
//  lcd.print("                ");
}
void LcdA_Lvalue(){//Lcd顯示輸入的含水率
  for(int i=0;i<=4;i++){
    lcd.setCursor(7+i,1);  
    lcd.print(ValueInput[i]);
  } 
}

void LcdAmodeLeave(){//Amode含水率設定完成顯示訊息
  lcd.setCursor(0,0);
  lcd.print("  WaterContent  ");
  lcd.setCursor(0,1);
  lcd.print("Input finish !! ");
//  lcd.print("                ");   
}



//LCD顯示器(Bmode-環境模式)
void LcdB_PreMeasure(){//環境模式
  LcdWhite();//Lcd清除顯示訊息
  LcdB_PreMeasure_H();//Lcd顯示上行訊息"  Environment   "
  LcdB_PreMeasure_L();//Lcd顯示下行訊息Temp          K "
  LcdB_PreMeasure_Temp();//Lcd顯示環境的溫度
}

void LcdB_PreMeasure_H(){//Lcd顯示上行訊息"  Environment   "
  lcd.setCursor(0,0);
  lcd.print("  Environment   ");
//  lcd.print("                "); 
}
void LcdB_PreMeasure_L(){//Lcd顯示下行訊息Temp          K "
  lcd.setCursor(0,1);
  lcd.print("Temp          K ");
//  lcd.print("                ");   
}
void LcdB_PreMeasure_Temp(){//Lcd顯示環境的溫度
  lcd.setCursor(7,1);
  lcd.print(Temp);
//  lcd.print("                ");  
} 

//LCD顯示器(Bmode-量測模式)
void LcdB_Measure(){//量測模式
     if(CollectTime<30){//環境平衡    
       lcd.setCursor(0,0);
       lcd.print("Calibrate      ");
       lcd.setCursor(15,0);
       lcd.print("s");
       
       lcd.setCursor(0,1);
       lcd.print("Record         ");   
       lcd.setCursor(9,1);
       lcd.print("s/");
       lcd.setCursor(11,1);
       lcd.print(Temp);

       LcdB_Measure_L(CollectTime);
       LcdB_Measure_H(CollectTime);
                 
     }else if(CollectTime<40){//釋放熱脈衝 
       lcd.setCursor(0,0);
       lcd.print("HeatPulse      ");
       lcd.setCursor(15,0);
       lcd.print("s");
       
       lcd.setCursor(0,1);
       lcd.print(" Record        ");   
       lcd.setCursor(9,1);
       lcd.print("s/");
       lcd.setCursor(11,1);
       lcd.print(Temp);

       LcdB_Measure_H(CollectTime-29);
       LcdB_Measure_L(CollectTime);   
           
     }else{//量測值到結束時間   
       lcd.setCursor(0,0);
       lcd.print("Measurement    ");
       lcd.setCursor(15,0);
       lcd.print("s");
       
       lcd.setCursor(0,1);
       lcd.print("Record         ");   
       lcd.setCursor(9,1);
       lcd.print("s/");
       lcd.setCursor(11,1);
       lcd.print(Temp);

       LcdB_Measure_H(CollectTime);
       LcdB_Measure_L(CollectTime);  
        
     }    
} 
void LcdB_Measure_H(int a){//Lcd顯示上行訊息"時間"
  lcd.setCursor(12,0);
  lcd.print("   ");
  if(a<9){
    lcd.setCursor(14,0);
    lcd.print(a);    
  }else if(a<99){
    lcd.setCursor(13,0);
    lcd.print(a);      
  }else{
    lcd.setCursor(12,0);
    lcd.print(a);      
  }
}
void LcdB_Measure_L(int a){//Lcd顯示下行訊息"時間"
  lcd.setCursor(6,1);
  lcd.print("   ");
  if(a<9){
    lcd.setCursor(8,1);
    lcd.print(a);    
  }else if(a<99){
    lcd.setCursor(7,1);
    lcd.print(a);      
  }else{
    lcd.setCursor(6,1);
    lcd.print(a);      
  }  
}

void LcdBmodeLeave(){//Bmode量測完成顯示訊息
  lcd.setCursor(0,0);
  lcd.print("Check Data 1,2,3");
  lcd.setCursor(0,1);
  lcd.print("   Exit    #    "); 
//  lcd.print("                ");   
}

void LcdBmodeLeave_2(){//Bmode結束顯示訊息
  lcd.setCursor(0,0);
  lcd.print("PleaseStoreData!");//11/16字元  
  lcd.setCursor(0,1);
  lcd.print("Clip Botton C !!"); 
//  lcd.print("                ");   
}


//Cmode
//void LcdCmode(){
//  lcd.setCursor(0,0);
//  lcd.print("Temp     Time   ");
//  lcd.setCursor(4,0);
//  lcd.print(int(PassTime));
//  lcd.setCursor(13,0);
//  lcd.print(PassTemp);
////  lcd.print("                ");
//      
//  lcd.setCursor(0,1);
//  lcd.print("Density         "); 
//  lcd.setCursor(7,1);
//  lcd.print(Density);
////  lcd.print("                ");   
//}

//LCD顯示器(參數計算)
void Lcd_TimeTemp(){//顯示起始和經過的時間和溫度 
  lcd.setCursor(0,0);
  lcd.print("Time   Temp     ");
  lcd.setCursor(4,0);
//  lcd.print(int(FirstTime));
  lcd.print("30");
  
  lcd.setCursor(11,0);
//  lcd.print(FirstTemp);
  lcd.print("27.8");
    
  lcd.setCursor(0,1);
  lcd.print("Time   Temp     ");
  lcd.setCursor(4,1);
//  lcd.print(int(SecondTime));
  lcd.print("80");
  
  lcd.setCursor(11,1);
//  lcd.print(SecondTemp);
  lcd.print("31.3");
//  lcd.print("                ");  
}

void Lcd_PassTimeTemp(){//顯示上升溫度和經過時間
  LcdWhite();  
  lcd.setCursor(0,0);
  lcd.print("Pass Time       ");
  lcd.setCursor(10,0);
//  lcd.print(int(PassTime));
  lcd.print("50");
  
  lcd.setCursor(0,1);
  lcd.print("Temp Raise      "); 
  lcd.setCursor(11,1);
//  lcd.print(PassTemp);
  lcd.print("3.5");
//  lcd.print("                ");    
}

void Lcd_SoilParameter(){//顯示土壤總體密度和土壤體積含水率
  LcdWhite();
  lcd.setCursor(0,0);
  lcd.print("Density         "); 
  lcd.setCursor(11,0);
//  lcd.print(Density); 
  lcd.print("1.35"); 
    
  lcd.setCursor(0,1);
  lcd.print("WaterCont       ");  
  lcd.setCursor(11,1);
//  lcd.print(WaterContent); 
  lcd.print("0.1");
//  lcd.print("                ");    
}


void LcdDataStore(){
  LcdWhite();
  lcd.setCursor(0,0);
  lcd.print("FileName Setting");
  lcd.setCursor(0,1);
  lcd.print("         .csv   ");
}

void LcdDataName(){
  for(int i=0;i<=4;i++){
    lcd.setCursor(3+i,1);  
    lcd.print(DataName[i]);
  } 
}

void LcdSD_initial(){
  LcdWhite();
  lcd.setCursor(0,0);  
  lcd.print("SDcard initial..");  
//  lcd.print("                ");    
}

void LcdSD(){//顯示SD模組是否啟用
  lcd.setCursor(0,0);  
  lcd.print("SDcard using... ");
  lcd.setCursor(0,1);
  lcd.print("Select Function ");  
//  lcd.print("                ");    
}


void LcdSDtest(int x){//顯示SD模組是否測試成功
  lcd.setCursor(0,0);  
  lcd.print("SDcard test...  ");
  if(x==1){
    lcd.setCursor(0,1);  
    lcd.print("Test  Success   ");
  }
//  lcd.print("                ");    
}

void LcdSD_store(){
  lcd.setCursor(0,0);  
  lcd.print("                ");   
  lcd.setCursor(0,0);  
  lcd.print("SD Store Success");    
//  lcd.print("                ");   
}

void LcdBC26(){//顯示啟用BC26模組
  lcd.setCursor(0,0);  
  lcd.print("BC26 using...   ");
  lcd.setCursor(0,1);
  lcd.print("Select Function ");  
//  lcd.print("                ");    
}

void LcdBC26_reset(int x){//顯示BC26模組是否重置成功
  lcd.setCursor(0,0);  
  lcd.print("BC26 Resetting..");
  if(x==1){
    lcd.setCursor(0,1);  
    lcd.print("ResettingSuccess");
  }
//  lcd.print("                ");    
}

void LcdBC26_initial(int x){//顯示BC26模組是否初始化成功
  lcd.setCursor(0,0);  
  lcd.print("BC26 initial....");
  if(x==1){
    lcd.setCursor(0,1);  
    lcd.print("Initial Success ");
  }
//  lcd.print("                ");    
} 

void LcdBC26_store(int x){//顯示BC26模組是否上傳成功
  lcd.setCursor(0,0);  
  lcd.print("BC26 UpdateData ");
  if(x==1){
    lcd.setCursor(0,1);  
    lcd.print("Update Success  ");
  }
//  lcd.print("                ");      
} 
