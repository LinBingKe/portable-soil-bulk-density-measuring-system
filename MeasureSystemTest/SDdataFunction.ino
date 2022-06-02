void DataNameInput(){

    Serial.println("Input file name");
    LcdDataStore();
    
    DataNameInitial();//文件名稱初始化
    file_name="";
    
    while(Leave()==false){
      //Serial.println("進入選擇迴圈");
      InputValue();//利用GetValue存取輸入的值
      switch(GetValue) {
        case '1':
          DataNameValue(1);
          break;
        case '2':
          DataNameValue(1);
          break;
        case '3':
          DataNameValue(1);
          break;
        case '4':
          DataNameValue(1);
          break;
        case '5':
          DataNameValue(1);
          break;
        case '6':
          DataNameValue(1);
          break;
        case '7':
          DataNameValue(1);
          break;
        case '8':
          DataNameValue(1);
          break;
        case '9':
          DataNameValue(1);
          break;
        case '0':
          DataNameValue(1);
          break;
        case '.':
          DataNameValue(1);
          break; 
        case 'D':
          DataNameValue(2);
          break;           
        default:
          break;       
      }  
      //Serial.println("離開選擇迴圈"); 
      DataNameShow();
      GetValue='z';
      Leave();
      
      delay(200);
    }
    
    LcdAmodeLeave();
    SetDataName();
    lcd.setCursor(0,0);
    lcd.print("SetDataName     ");
//    lcd.print("                "); 
    delay(2000);   
    SD_write();
    lcd.setCursor(0,0);
    lcd.print("SD write        ");
//    lcd.print("                ");  
    delay(2000);         
    SD_read();
    lcd.setCursor(0,0);
    lcd.print("SD read         ");
//    lcd.print("                ");  
    delay(2000);         
    Update=true;    
  
}

//含水率陣列初始化
void DataNameInitial()
{
  for(int i=0;i<=4;i++){
    DataName[i]='0';
  }
  Serial.println("DataName初始化完畢");
}

//ValueInput陣列(存取輸入的含水率數據)
void DataNameValue(int x1)
{
  if((x1==1)&&(DataNameIndex<5)){
    Serial.print("測試索引值");
    Serial.println(DataNameIndex);
    DataName[DataNameIndex]=GetValue;
    LcdDataName();
    DataNameIndex++;   
  }
  
  if((x1==2)&&(DataNameIndex>0)){
    Serial.print("測試索引值");
    Serial.println(DataNameIndex);        
    DataNameIndex--;   
    DataName[DataNameIndex]='0';
    LcdDataName();
  }
}

//ValueInput陣列(資料顯示)
void DataNameShow()
{ 
  for(int i=0;i<=4;i++){
    Serial.print(DataName[i]);
  }
//  Serial.println("");  
//  Serial.println("測試開始轉換");
//  Serial.println(Change(ValueInput[0]));  
//  Serial.println("測試轉換完畢");
  Serial.println("");
}

//設定WaterContent
void SetDataName()
{
  for(int i=0;i<=4;i++){
    file_name=file_name+DataName[i];
  }
  update_name=file_name;
  file_name=file_name+".csv";   
}



void SD_write()
{
  LcdSD_initial();
  if (!SD.begin(PIN9)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("SD initialization done.");//SD initialization done
  
  myFile = SD.open(file_name, FILE_WRITE);//Open file
  if (myFile) {
    LcdSD_initial();
    Serial.println("prepare to write");
    for(int i=0;i<=240;i++){
      myFile.print(i);
      myFile.print(",");

      switch(i) {
        case 0:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,FirstTime,"); 
          myFile.println(FirstTime);        
          break;
        case 1:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,SecondTime,");
          myFile.println(SecondTime); 
          break;
        case 2:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,FirstTemp,");
          myFile.println(FirstTemp); 
          break;
        case 3:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,SecondTemp,");
          myFile.println(SecondTemp);    
          break;
        case 4:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,PassTime,");
          myFile.println(PassTime);     
          break;
        case 5:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,PassTemp,");
          myFile.println(PassTemp);   
          break;  
        case 6:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,Density,");
          myFile.println(Density);   
          break;
        case 7:
          myFile.print(CollectTemp[i]);
          myFile.print(", ,WaterContent,");
          myFile.println(WaterContent);   
          break; 
        case 8:
          myFile.print(CollectTemp[i]);        
          myFile.print(", ,Capacity,");
          myFile.println(Capacity);   
          break;
        case 59:
          myFile.print(CollectTemp[i]);        
          myFile.print(",heatopen");
          myFile.println(Capacity);   
          break;                                                                                            
        default:
          myFile.println(CollectTemp[i]);
          break;       
      }                                                
      delay(10);
    }    
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
    
}


void SD_read()
{
  Serial.println("prepare to read");
  myFile = SD.open(file_name);
  if (myFile) {
    Serial.println(file_name);  
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening test.txt");// if the file didn't open
  } 
  LcdSD_store();
   
}


void SD_test(){
  lcd.setCursor(0,0);  
  lcd.print("SDcardSingleTest");  
  
  if (!SD.begin(PIN9)) {
    Serial.println("SD initial failed!");
    lcd.setCursor(0,1);  
    lcd.print("Single  Fail    ");        
  }else{
    Serial.println("SD initial success!");
    lcd.setCursor(0,1);   
    lcd.print("Single  Success ");
//    lcd.print("                ");    
  }
  
}


void SD_testfile()
{
  if (!SD.begin(PIN9)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("SD initialization done.");//SD initialization done
  
  myFile = SD.open("test.csv", FILE_WRITE);//Open file
  if (myFile) {
    Serial.println("test write");
    myFile.print("123");
    delay(10);
    myFile.close();
  } else {
    Serial.println("error opening test.csv");
  }
    
}  


  
