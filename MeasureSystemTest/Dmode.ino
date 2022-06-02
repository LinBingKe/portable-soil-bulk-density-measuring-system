//介面D(上傳資料)
void ControlUpdate(){
  if(Dmode()==true){ 
    LcdBC26();   
    while(Leave()==false){ 
      InputValue();//利用GetValue存取輸入的值
      switch(GetValue) {//透過Keypad輸入值
        case '1'://重置BC26模組
          LcdBC26_reset(0);
          digitalWrite(PC13, LOW);
          delay(30);
          digitalWrite(PC13, HIGH);
          delay (3000);
          LcdBC26_reset(1);          
          break;
        case '2'://測試通訊模組是否正常
          LcdBC26_initial(0);
          BC26FunctionInit();
          LcdBC26_initial(1);
          break;
        case '3'://上傳資料
          LcdBC26_store(0);
          SendData();
          LcdBC26_store(1);
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
