
/*
 * PID DEFAULT
 * Kp = 6.00 // SPD = 80
 * Kd = 8.10
 * *****************************************
 * Kp = 7.00 // SPD = 120
 * Kd = 11.00
 */
void program(int dataSensor, String flMode) {
  unsigned long interval = timeNowPID - prevTime / 500.0;
  
   if(flMode == "right"){
    switch(dataSensor){
    case 0b11111111111110:       error = -5;    break;
    case 0b11111111111100:       error = -3;    break;
    case 0b11111111111101:       error = -1;    break;
    case 0b11111111111001:       error =  0;    break;
    case 0b11111111111011:       error =  1;     break;
    case 0b11111111110011:       error =  1;     break;
    case 0b11111111110111:       error =  2;     break;
    case 0b11111111100111:       error =  2;     break;
    case 0b11111111101111:       error =  3;     break;
    case 0b11111111001111:       error =  3;     break;
    case 0b11111111011111:       error =  4;     break;
    case 0b11111110011111:       error =  4;     break;
    case 0b11111110111111:       error =  5;     break;
    case 0b11111100111111:       error = 5;      break;
    case 0b11111101111111:       error = 6;      break;
    case 0b11111001111111:       error = 6;      break;
    case 0b11111011111111:       error = 7;      break;
    case 0b11110011111111:       error = 7;      break;
    case 0b11110111111111:       error = 8;      break;
    case 0b11100111111111:       error = 8;      break;
    case 0b11101111111111:       error = 9;      break;
    case 0b11001111111111:       error = 9;      break;
    case 0b11011111111111:       error = 10;      break;
    case 0b10011111111111:       error = 10;     break;
    case 0b10111111111111:       error = 11;     break;
    case 0b00111111111111:       error = 11;     break;
    case 0b01111111111111:       error = 12;     break;

    // BLACK LINE
    case 0b00000000000001:       error = -5;    break;
    case 0b00000000000011:       error = -3;    break;
    case 0b00000000000010:       error = -1;    break;
    case 0b00000000000110:       error =  0;    break;
    case 0b00000000000100:       error =  1;     break;
    case 0b00000000001100:       error =  1;     break;
    case 0b00000000001000:       error =  2;     break;
    case 0b00000000011000:       error =  2;     break;
    case 0b00000000010000:       error =  3;     break;
    case 0b00000000110000:       error =  3;     break;
    case 0b00000000100000:       error =  4;     break;
    case 0b00000001100000:       error =  4;     break;
    case 0b00000001000000:       error =  5;     break;
    case 0b00000011000000:       error = 5;      break;
    case 0b00000010000000:       error = 6;      break;
    case 0b00000110000000:       error = 6;      break;
    case 0b00000100000000:       error = 7;      break;
    case 0b00001100000000:       error = 7;      break;
    case 0b00001000000000:       error = 8;      break;
    case 0b00011000000000:       error = 8;      break;
    case 0b00010000000000:       error = 9;      break;
    case 0b00110000000000:       error = 9;      break;
    case 0b00100000000000:       error = 10;      break;
    case 0b01100000000000:       error = 10;     break;
    case 0b01000000000000:       error = 11;     break;
    case 0b11000000000000:       error = 11;     break;
    case 0b10000000000000:       error = 12;     break;
    }
   }
   else if(flMode == "left"){
    switch(dataSensor){
    case 0b11111111111110:       error = -12;    break;
    case 0b11111111111100:       error = -11;    break;
    case 0b11111111111101:       error = -11;    break;
    case 0b11111111111001:       error = -10;    break;
    case 0b11111111111011:       error = -10;     break;
    case 0b11111111110011:       error =  -9;     break;
    case 0b11111111110111:       error =  -9;     break;
    case 0b11111111100111:       error =  -8;     break;
    case 0b11111111101111:       error =  -8;     break;
    case 0b11111111001111:       error =  -7;     break;
    case 0b11111111011111:       error =  -7;     break;
    case 0b11111110011111:       error =  -6;     break;
    case 0b11111110111111:       error =  -6;     break;
    case 0b11111100111111:       error =  -5;      break;
    case 0b11111101111111:       error =  -5;      break;
    case 0b11111001111111:       error =  -4;      break;
    case 0b11111011111111:       error =  -4;      break;
    case 0b11110011111111:       error =  -3;      break;
    case 0b11110111111111:       error =  -3;      break;
    case 0b11100111111111:       error =  -2;      break;
    case 0b11101111111111:       error =  -2;      break;
    case 0b11001111111111:       error =  -1;      break;
    case 0b11011111111111:       error =  -1;      break;
    case 0b10011111111111:       error =  0;      break;
    case 0b10111111111111:       error =  1;     break;
    case 0b00111111111111:       error =  3;     break;
    case 0b01111111111111:       error =  5;     break;

    // BLACK LINE
    case 0b00000000000001:       error = -12;    break;
    case 0b00000000000011:       error = -11;    break;
    case 0b00000000000010:       error = -11;    break;
    case 0b00000000000110:       error = -10;    break;
    case 0b00000000000100:       error = -10;     break;
    case 0b00000000001100:       error =  -9;     break;
    case 0b00000000001000:       error =  -9;     break;
    case 0b00000000011000:       error =  -8;     break;
    case 0b00000000010000:       error =  -8;     break;
    case 0b00000000110000:       error =  -7;     break;
    case 0b00000000100000:       error =  -7;     break;
    case 0b00000001100000:       error =  -6;     break;
    case 0b00000001000000:       error =  -6;     break;
    case 0b00000011000000:       error =  -5;      break;
    case 0b00000010000000:       error =  -5;      break;
    case 0b00000110000000:       error =  -4;      break;
    case 0b00000100000000:       error =  -4;      break;
    case 0b00001100000000:       error =  -3;      break;
    case 0b00001000000000:       error =  -3;      break;
    case 0b00011000000000:       error =  -2;      break;
    case 0b00010000000000:       error =  -2;      break;
    case 0b00110000000000:       error =  -1;      break;
    case 0b00100000000000:       error =  -1;      break;
    case 0b01100000000000:       error =  0;      break;
    case 0b01000000000000:       error =  1;     break;
    case 0b11000000000000:       error =  3;     break;
    case 0b10000000000000:       error =  5;     break;
    }
   } 
   else { // center Follow
    switch (dataSensor) {
    // WHite LIne
    case 0b11111111111110:       error = -14;    break;
    case 0b11111111111100:       error = -12;    break;
    case 0b11111111111101:       error = -11;    break;
    case 0b11111111111001:       error = -10;    break;
    case 0b11111111111011:       error = -9;     break;
    case 0b11111111110011:       error = -8;     break;
    case 0b11111111110111:       error = -7;     break;
    case 0b11111111100111:       error = -6;     break;
    case 0b11111111101111:       error = -5;     break;
    case 0b11111111001111:       error = -4;     break;
    case 0b11111111011111:       error = -3;     break;
    case 0b11111110011111:       error = -2;     break;
    case 0b11111110111111:       error = -1;     break;
    case 0b11111100111111:       error = 0;      break;
    case 0b11111101111111:       error = 1;      break;
    case 0b11111001111111:       error = 2;      break;
    case 0b11111011111111:       error = 3;      break;
    case 0b11110011111111:       error = 4;      break;
    case 0b11110111111111:       error = 5;      break;
    case 0b11100111111111:       error = 6;      break;
    case 0b11101111111111:       error = 7;      break;
    case 0b11001111111111:       error = 8;      break;
    case 0b11011111111111:       error = 9;      break;
    case 0b10011111111111:       error = 10;     break;
    case 0b10111111111111:       error = 11;     break;
    case 0b00111111111111:       error = 12;     break;
    case 0b01111111111111:       error = 14;     break;

    // BLACK LINE
    case 0b00000000000001:       error = -14;    break;
    case 0b00000000000011:       error = -12;    break;
    case 0b00000000000010:       error = -11;    break;
    case 0b00000000000110:       error = -10;    break;
    case 0b00000000000100:       error = -9;     break;
    case 0b00000000001100:       error = -8;     break;
    case 0b00000000001000:       error = -7;     break;
    case 0b00000000011000:       error = -6;     break;
    case 0b00000000010000:       error = -5;     break;
    case 0b00000000110000:       error = -4;     break;
    case 0b00000000100000:       error = -3;     break;
    case 0b00000001100000:       error = -2;     break;
    case 0b00000001000000:       error = -1;     break;
    case 0b00000011000000:       error = 0;      break;
    case 0b00000010000000:       error = 1;      break;
    case 0b00000110000000:       error = 2;      break;
    case 0b00000100000000:       error = 3;      break;
    case 0b00001100000000:       error = 4;      break;
    case 0b00001000000000:       error = 5;      break;
    case 0b00011000000000:       error = 6;      break;
    case 0b00010000000000:       error = 7;      break;
    case 0b00110000000000:       error = 8;      break;
    case 0b00100000000000:       error = 9;      break;
    case 0b01100000000000:       error = 10;     break;
    case 0b01000000000000:       error = 11;     break;
    case 0b11000000000000:       error = 12;     break;
    case 0b10000000000000:       error = 14;     break;

    // Spesial
    case 0b00000111111111:       error = 0;    break;
    
    case 0b00000011111111:       error = 0;    break;
    case 0b00000001111111:       error = 0;    break;
    case 0b00000000111111:       error = 0;    break;
    case 0b00000011011111:       error = 0;    break;

    case 0b11111011000000:       error = 0;    break;
    case 0b11111100000000:       error = 0;    break;
    case 0b11111110000000:       error = 0;    break;
    case 0b11111111000000:       error = 0;    break;
    case 0b11111111100000:       error = 0;    break;

    case 0b11100000000111:       error = 0;    break;
    case 0b11000000000011:       error = 0;    break;
    case 0b10000000000001:       error = 0;    break;
    case 0b11100011000111:       error = 0;    break;
    case 0b11000011000011:       error = 0;    break;
    case 0b10000011000001:       error = 0;    break;
    case 0b01111011011110:       error = 0;    break;
    case 0b00111011011110:       error = 0;    break;
    case 0b00000111100000:       error = 0;    break;
    case 0b00001111110000:       error = 0;    break;
    }
   }

    P  = error * _Kp[selectPresetPIDPlay];
    D  = (error - lastError) * _Kd[selectPresetPIDPlay] / interval;
    int16_t moveVal = P + D;
    lastError = error;
    int16_t leftW = maxS - moveVal;
    int16_t rightW = maxS + moveVal;
    leftW = constrain(leftW, -255, 255);
    rightW = constrain(rightW, -255, 255);
    pwmMotor(leftW, rightW); // L, R
    prevTime = timeNowPID;
}

/*
  void program(int dataSensor) {
  uint32_t now = millis();
  uint32_t interval = now - prevTime;
  if (interval >= 5) {
    int8_t errorSensor[14] = { -26, -22, -18, -14, -10, -5, -1, 1, 5, 10, 14, 18, 22, 26};
    int8_t onSensor[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float sumOnSensor = 0;
    for (int8_t i = 0; i < 14; i++) {
      onSensor[i] = bitRead(dataSensor, 14 - i);
      sumOnSensor += onSensor[i];
      errorSensor[i] = errorSensor[i] * onSensor[i];
      error += errorSensor[i];
    }
    error = error / sumOnSensor;
    int16_t rateSensor = error - lastError;
    lastError = error;

    int16_t moveVal = int((error * Kp) + (rateSensor * Kd));
    int leftW = maxS - moveVal;
    int rightW = maxS + moveVal;
    leftW = constrain(leftW, -255, 255);
    rightW = constrain(rightW, -255, 255);
    Serial.println(moveVal);
    Serial.print("Motor Kiri : "); Serial.print(leftW); Serial.print("\t");
    Serial.print("Motor Kanan : "); Serial.print(rightW); Serial.print("\t");
    Serial.println();
    pwmMotor(leftW, rightW); // L, R
    prevTime = now;
  }
  }
*/

//void pidTestEstimate() {
//  int sensBuff;
//  sensBuff = readSensor();
//  error = 6250 - estimatePosition();
//  sumError += error;
//  P = error * Kp;
//  I = sumError * Ki;
//  D = (error - lastError) * Kd;
//  lastError = error;
//  moveVal = P + D;
//  uint16_t leftW = 100 - moveVal;
//  uint16_t rightW = 100 + moveVal;
//  if (leftW > 150) leftW = 150;
//  else if (rightW > 150) rightW = 150;
//  if (leftW < 0) leftW = 0;
//  else if (rightW < 0) rightW = 0;
//  pwmMotor(leftW, rightW);
//}

void TunePid() {
  selectSet = 1;
  selectPresetPID = 0;
  int selectFLMODETest = 0;
  while (1) {
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      maxS = selectSet = 0;
      saveAll();
      delay(50);
      break;
    }
    if (touchUp(Button_DOWN)) {
      selectSet++;
      if (selectSet > 6) selectSet = 1;
    }
    if (touchUp(Button_UP)) {
      selectSet--;
      if (selectSet < 1) selectSet = 6;
    }
    
    if (selectSet == 1) {
      lcd.drawRoundRect(18, 13, 81, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) {
        selectPresetPID++;
        if(selectPresetPID > 6) selectPresetPID = 0;
        }
      if (touchUp(Button_MIN)) {
        selectPresetPID--;
        if(selectPresetPID == 255) selectPresetPID = 6;
      }
    }
    if (selectSet == 2) {
      lcd.drawRoundRect(3, 28, 60, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) _Kp[selectPresetPID] += 0.1;
      if (touchUp(Button_MIN)) _Kp[selectPresetPID] -= 0.1;
    }
    if (selectSet == 3) {
      lcd.drawRoundRect(63, 28, 60, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) _Kd[selectPresetPID] += 0.1;
      if (touchUp(Button_MIN)) _Kd[selectPresetPID] -= 0.1;
    }
    if (selectSet == 4) {
      lcd.drawRoundRect(4, 39, 70, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) maxS += 10;
      if (touchUp(Button_MIN)) maxS -= 10;
    }
    if (selectSet == 5){
      lcd.drawRoundRect(74, 39, 50, 12, 3, SH110X_WHITE);
      if (touchUp(Button_PLUS)) {
        selectFLMODETest++;
        if(selectFLMODETest > 2) selectFLMODETest = 0;
      }
      if (touchUp(Button_MIN)) {
        selectFLMODETest--;
        if(selectFLMODETest < 0) selectFLMODETest = 2;
      }
    }
    if (selectSet == 6) {
      lcd.drawRoundRect(30, 50, 56, 12, 3, SH110X_WHITE);
      if (touchUp(Button_OK)) {
        oledClear();
        selectPresetPIDPlay = selectPresetPID;
        while (1) {
          int bufDataSensor = readSensor();
          headUp(true, false);
          dispSensor(bufDataSensor);
          if(selectFLMODETest == 0){
            program(bufDataSensor, "center");
          } else if(selectFLMODETest == 1){
            program(bufDataSensor, "right");
          } else if(selectFLMODETest == 2) {
            program(bufDataSensor, "left");
          }
          if (touchUp(Button_RUN)) {
            oledClear();
            selectSet = 1;
            selectPresetPIDPlay = 0;
            stopMotor();
            break;
          }
          lcd.display();
        }
      }
    }
    lcd_char(1, 20, 15, "Preset:" + (String)slctPID[selectPresetPID], true, false, false);
    lcd_char(1, 5, 30, "Kp: " + String(_Kp[selectPresetPID], 2), true, false, false);
    lcd_char(1, 65, 30, "Kd: " + String(_Kd[selectPresetPID], 2), true, false, false);
    lcd_char(1, 5, 42, "Speed : " + String(maxS), true, false, false);
    lcd_char(1, 76, 42, "FL :" + String(slctFLMODE[selectFLMODETest]), true, false, false);
    lcd_char(1, 33, 53, "Coba PID", true, false, false);
    lcd.display();
  }
}
