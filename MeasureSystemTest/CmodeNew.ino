//介面D(上傳資料)
void ControlSD(){
  if(Cmode()==true){ 
    LcdSD();
    while(Leave()==false){ 
      InputValue();//利用GetValue存取輸入的值
      switch(GetValue) {//透過Keypad輸入值
        case '1'://重置BC26模組
          SD_test();       
          break;
        case '2'://測試通訊模組是否正常
          LcdSDtest(0);
          SD_testfile();
          LcdSDtest(1);
          break;
        case '3'://上傳資料
          DataNameInput();
          break;        
        default:
          break;       
      }
      GetValue='z';  
      Leave();//判斷結束輸入模式      
      delay(200);       
    }  
  delay(2000);
  LcdBlack();
  } 
}
