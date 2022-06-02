//Keypad(初始化)
void KeypadInit(){
  for (int i= 0; i <= 3; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);//啟用上拉電阻
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
    digitalWrite(rowPins[i], HIGH);
  }
  Serial.println("Keypad初始化完畢");  
}
    
void InputValue(){//Keypad(檢測觸發的按鍵)
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      digitalWrite(colPins[j], LOW);
      scanVal = digitalRead(rowPins[i]);

      if (scanVal == LOW) {    // 如果輸入值是「低電位」…
        
        GetValue=keymap[i][j];  // 輸出按鍵代表的字元
        delay(40);  // 掃描按鍵的間隔時間
        digitalWrite(colPins[j], HIGH);
        break;       // 跳出迴圈
      }
      digitalWrite(colPins[j], HIGH);

    }
  }
}
 
bool Amode(){//介面(按鍵'A'進入體積含水率介面)
  digitalWrite(colPins[0], LOW);
  scanVal = digitalRead(rowPins[3]);
  if (scanVal == LOW) {    // 如果輸入值是「低電位」…
    
//    Serial.println(keymap[3][0]);  // 輸出按鍵代表的字元
    delay(400);  // 掃描按鍵的間隔時間
    digitalWrite(colPins[0], HIGH);
    return true;       // 跳出迴圈
  }
  digitalWrite(colPins[0], HIGH);  
  return false;
}
     
bool Bmode(){//介面(按鍵'B'進入量測介面)
  digitalWrite(colPins[0], LOW);
  scanVal = digitalRead(rowPins[2]);
  if (scanVal == LOW) {    // 如果輸入值是「低電位」…
    
//    Serial.println(keymap[2][0]);  // 輸出按鍵代表的字元
    delay(600);  // 掃描按鍵的間隔時間
    digitalWrite(colPins[0], HIGH);
    return true;       // 跳出迴圈
  }
  digitalWrite(colPins[0], HIGH);  
  return false;
}
    
bool Cmode(){//介面(按鍵'C'進入數據儲存介面)
  digitalWrite(colPins[0], LOW);
  scanVal = digitalRead(rowPins[1]);
  if (scanVal == LOW) {    // 如果輸入值是「低電位」…
    
//    Serial.println(keymap[1][0]);  // 輸出按鍵代表的字元
    delay(400);  // 掃描按鍵的間隔時間
    digitalWrite(colPins[0], HIGH);
    return true;       // 跳出迴圈
  }
  digitalWrite(colPins[0], HIGH);  
  return false;
}

bool Dmode(){//介面(按鍵'D'進入數據上傳介面)
  digitalWrite(colPins[0], LOW);
  scanVal = digitalRead(rowPins[0]);
  if (scanVal == LOW) {    // 如果輸入值是「低電位」…
    
//    Serial.println(keymap[0][0]);  // 輸出按鍵代表的字元
    delay(400);  // 掃描按鍵的間隔時間
    digitalWrite(colPins[0], HIGH);
    return true;       // 跳出迴圈
  }
  digitalWrite(colPins[0], HIGH);  
  return false;
}
      
bool Leave(){//介面(按鍵'#'離開)
  digitalWrite(colPins[1], LOW);
  scanVal = digitalRead(rowPins[0]);
  if (scanVal == LOW) {    // 如果輸入值是「低電位」…
    
//    Serial.println(keymap[0][1]);  // 輸出按鍵代表的字元
    delay(400);  // 掃描按鍵的間隔時間
    digitalWrite(colPins[1], HIGH);
    return true;       // 跳出迴圈
  }
  digitalWrite(colPins[1], HIGH);  
  return false;
}
