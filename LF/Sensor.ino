
int muxChannel[8][3] = {
  {0, 0, 0},
  {1, 0, 0},
  {0, 1, 0},
  {1, 1, 0},
  {0, 0, 1},
  {1, 0, 1},
  {0, 1, 1},
  {1, 1, 1}
};

void setupSensor() {
  pinMode(S1_MUX, OUTPUT);
  pinMode(S2_MUX, OUTPUT);
  pinMode(S3_MUX, OUTPUT);
  pinMode(MUX_Kiri_ADC1, INPUT);
  pinMode(MUX_Kanan_ADC2, INPUT);
  pinMode(ADCBAT, INPUT);
  analogReadResolution(10);
}

unsigned long prevLed = 0;
void ILED(int Tim) {
  if (millis() - prevLed >= Tim) {
    SLED(1);
    prevLed = millis();
  }
  SLED(0);
}

void readMux(byte i) {
  digitalWrite(S1_MUX, muxChannel[i][0]);
  digitalWrite(S2_MUX, muxChannel[i][1]);
  digitalWrite(S3_MUX, muxChannel[i][2]);
}

int readSensor() {
  int16_t bitMask = 0b00000000000000;
  int16_t bitBuf = 0b11111111111111;
//  for (byte i = 0; i < 8; i++) {
//    readMux(i);
////    i == 0 ? adcVal[7] = analogRead(MUX_Kanan_ADC2) : adcVal[i + 7] = analogRead(MUX_Kanan_ADC2);
////    i == 7 ? adcVal[6] = analogRead(MUX_Kiri_ADC1) : adcVal[i - 1] = analogRead(MUX_Kiri_ADC1);
//    if(i == 0) adcVal[7] = analogRead(MUX_Kanan_ADC2);
//    else if (i == 7) adcVal[6] == analogRead(MUX_Kiri_ADC1);
//    else {
//      adcVal[i+7] = analogRead(MUX_Kanan_ADC2);
//      adcVal[i-1] = analogRead(MUX_Kiri_ADC1);
//    }
//  }

  readMux(0);
  adcVal[7] = analogRead(MUX_Kanan_ADC2);
  readMux(1);
  adcVal[0] = analogRead(MUX_Kiri_ADC1);
  adcVal[8] = analogRead(MUX_Kanan_ADC2);
  readMux(2);
  adcVal[1] = analogRead(MUX_Kiri_ADC1);
  adcVal[9] = analogRead(MUX_Kanan_ADC2);
  readMux(3);
  adcVal[2] = analogRead(MUX_Kiri_ADC1);
  adcVal[10] = analogRead(MUX_Kanan_ADC2);
  readMux(4);
  adcVal[3] = analogRead(MUX_Kiri_ADC1);
  adcVal[11] = analogRead(MUX_Kanan_ADC2);
  readMux(5);
  adcVal[4] = analogRead(MUX_Kiri_ADC1);
  adcVal[12] = analogRead(MUX_Kanan_ADC2);
  readMux(6);
  adcVal[5] = analogRead(MUX_Kiri_ADC1);
  adcVal[13] = analogRead(MUX_Kanan_ADC2);
  readMux(7);
  adcVal[6] = analogRead(MUX_Kiri_ADC1);
  
  for (byte i = 0; i < MAXSENSOR; i++) {
    if (adcVal[i] > CalAdc[i]) bitMask = bitMask + (0b10000000000000 >> i);
  }
  if (clrLinePlay == 1) {
    bitBuf = 0b11111111111111 - bitMask;
  } else {
    bitBuf = bitMask;
  }
  return bitBuf;
}

uint16_t estimatePosition(){
  uint32_t avg = 0; 
  uint16_t sum = 0;
  for(byte i = 0; i < MAXSENSOR; i++){
    uint16_t values = adcVal[i];
    avg += (uint32_t) values * (i * 1000);
    sum += values;
  }
  return avg / sum; 
}

void calibSensor() {
  oledClear();
  countMenu = 0;
  byte _stepsCalib;
  while (1) {
    headUp(true, false);
    if (touchUp(Button_RUN)) {
      oledClear();
      saveAll();
      break;
    }

    if (touchUp(Button_UP)) {
      delay(10);
      while (1) {
        headUp(true, false);
        if (touchUp(Button_RUN)) {
          _stepsCalib = 0;
          break;
        }

        if (touchUp(Button_OK)) {
          _stepsCalib++;
        }

        if (_stepsCalib == 0) {
          if (touchUp(Button_PLUS)) {
            sensorSensivity++;
            if (sensorSensivity > 100) sensorSensivity = 0;
          }
          if (touchUp(Button_MIN)) {
            sensorSensivity--;
            if (sensorSensivity == 255) sensorSensivity = 100;
          }
          sprintf(buff, "Set Sensivity : %d", sensorSensivity);
          lcd_char(1, 2, 16, buff, true, false, false);
        }

        else if (_stepsCalib == 1) {
          for (byte i = 0; i < MAXSENSOR; i++) {
            setMinVal[i] = minVal[i] = 1023;
            setMaxVal[i] = maxVal[i] = 0;
          }
          delayMicroseconds(500);
          while (1) {
            headUp(true, false);
            lcd_char(1, 2, 16, "Majukno Robotmu", true, false, false);
            lcd_char(1, 2, 26, "Sampe Kenek Garis", true, false, false);
            lcd_char(1, 2, 36, "Press OK for Save", true, false, false);
            int buffSens = readSensor();
            for (int x = 0; x < MAXSENSOR; x++) {
              if (adcVal[x] > maxVal[x]) {
                maxVal[x] = adcVal[x];
              }
              if (adcVal[x] < minVal[x]) {
                minVal[x] = adcVal[x];
              }
            }
            lcd.display();
            if (touchUp(Button_OK)) {
              delay(50);
              _stepsCalib = 2;
              break;
            }
          }
        } // steps 1
        else if (_stepsCalib == 2) {
          for (int i = 0; i < MAXSENSOR; i++) {
            CalAdc[i] = ((maxVal[i] - minVal[i]) * (float)((100.0 - sensorSensivity) / 100.0)) + minVal[i];
          }
          lcd_char(1, 2, 16, "Success Calibration", true, false, false);
          sprintf(buff, "Sensor %d : %u" , sens, CalAdc[sens]);
          lcd_char(1, 2, 32, buff, true, false, false);
          delay(300);
          sens++;
          if(sens > 13) sens = 0;
        }
        lcd.display();
      } // end while bracket
      lcd.fillRoundRect(25, 25, 25, 10, 2, SH110X_WHITE);
      lcd_char(1, 26, 26, "Auto", false, false, false);
    } else {
      lcd.drawRoundRect(25, 25, 25, 10, 2, SH110X_WHITE);
      lcd_char(1, 26, 26, "Auto", true, false, false);
    }

    if (touchUp(Button_PLUS)) {
      countMenu = 1;
      selectSet = 0;
      while(1){
        headUp(true, false);
        dispSensor(readSensor());
        if(touchUp(Button_RUN)){
          saveAll();
          oledClear();
          break;
        }
        if(touchUp(Button_UP)){
          selectSet = 0;
          if(++countMenu > 14) countMenu = 14;
        }
        if(touchUp(Button_DOWN)){
          selectSet = 0;
          if(--countMenu < 1 ) countMenu = 1;
        }
        if(touchUp(Button_OK)){
         if(++selectSet > 4 ) selectSet = 1;
        }

        if(selectSet == 1){
          lcd.drawRoundRect(0, 38, 53, 12, 2, SH110X_WHITE);
          if(touchUp(Button_PLUS)){
            setMaxVal[countMenu - 1]++;
            if(setMaxVal[countMenu - 1] > 1023) setMaxVal[countMenu - 1] = 1023;
          }
          if(touchUp(Button_MIN)){
            setMaxVal[countMenu - 1]--;
            if(setMaxVal[countMenu - 1] < 0) setMaxVal[countMenu - 1] = 0;
          }
        }
        else if(selectSet == 2){
          lcd.drawRoundRect(0, 48, 53, 12, 2, SH110X_WHITE);
          if(touchUp(Button_PLUS)){
            setMinVal[countMenu - 1]++;
            if(setMinVal[countMenu - 1] > 1023) setMinVal[countMenu - 1] = 1023;
          }
          if(touchUp(Button_MIN)){
            setMinVal[countMenu - 1]--;
            if(setMinVal[countMenu - 1] < 0) setMinVal[countMenu - 1] = 0;
          }
        }
        else if(selectSet == 3){
          lcd.drawRoundRect(56, 38, 65, 12, 2, SH110X_WHITE);
        }
        else if(selectSet == 4){
          lcd.drawRoundRect(56, 48, 65, 12, 2, SH110X_WHITE);
          if(touchUp(Button_PLUS)){
            CalAdc[countMenu - 1]++;
            if(CalAdc[countMenu - 1] > 1024) CalAdc[countMenu - 1] = 1024;
          }
          if(touchUp(Button_MIN)){
            CalAdc[countMenu - 1]--;
            if(CalAdc[countMenu - 1] < 0) CalAdc[countMenu - 1] = 0;
          }
        }
        lcd_char(1, 2, 40, "MAX :" + String(setMaxVal[countMenu - 1]), true, false, false);
        lcd_char(1, 2, 50, "MIN :" + String(setMinVal[countMenu - 1]), true, false, false);
        lcd_char(1, 58, 40, "READ :" + String(adcVal[countMenu - 1]), true, false, false);
        lcd_char(1, 58, 50, "SET  :" + String(CalAdc[countMenu - 1]), true, false, false);
        lcd.setCursor(17 + (7 * (countMenu - 1)), 30);
        lcd.write(0x1E);
        lcd.display();
      }
      lcd.fillRoundRect(55, 25, 38, 10, 2, SH110X_WHITE);
      lcd_char(1, 57, 26, "Manual", false, false, false);
    } else {
      lcd.drawRoundRect(55, 25, 38, 10, 2, SH110X_WHITE);
      lcd_char(1, 57, 26, "Manual", true, false, false);
    }
    lcd.display();
  } // end while calib bracket
}

float readBattery() {
  float adcVal_Bat = analogRead(ADCBAT);
  float valueAdc = (3.3f / 1023.0f) * ((10000 + 3300) / 3300);
  float vout = adcVal_Bat * valueAdc;
  return vout;
}
