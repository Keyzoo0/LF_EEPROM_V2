void menu() {
  countMenu = 0;

  saveAll();
  delay(10);
  while (1) {
    stopMotor();
    if (touchUp(Button_MIN) && ((halaman == 0) || (halaman == 1))) {
      countMenu--;
      if (countMenu > 4 ) {
        countMenu = 4;
        halaman--;
        if (halaman > 4) halaman = 1;
      }
    }
    if (touchUp(Button_UP)&& ((halaman == 0) || (halaman == 1))) {
      countMenu++;
      if (countMenu > 4) {
        countMenu = 1;
        halaman++; 
        if (halaman > 1) halaman = 0;
      }
    }

    if (touchUp(Button_RUN)) {
      oledClear();
      break;
    }

    if (halaman == 0) {
      headUp(true, false);
      if (countMenu == 1) {
        if (touchUp(Button_OK)) {
          setIDX();
        }
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "1. Setting Index", false, false, false);
      } else {
        lcd_char(1, 2, 15, "1. Setting Index", true, false, false);
      }

      if (countMenu == 2) {
        if (touchUp(Button_OK)) {
          calibSensor();
        }
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "2. Kalibrasi Sensor", false, false, false);
      } else {
        lcd_char(1, 2, 27, "2. Kalibrasi Sensor", true, false, false);
      }

      if (countMenu == 3) {
        if (touchUp(Button_OK)) {
          TunePid();
        }
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "3. Tuning PID", false, false, false);
      } else {
        lcd_char(1, 2, 37, "3. Tuning PID", true, false, false);
      }

      if (countMenu == 4) {
        if (touchUp(Button_OK)) {
          CMIDX();
        }
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "4. Copy/Mirror Plan", false, false, false);
      } else {
        lcd_char(1, 2, 47, "4. Copy/Mirror Plan", true, false, false);
      }
    } else if (halaman == 1) {
      headUp(true, false);
      if (countMenu == 1) {
        if (touchUp(Button_OK)) {
          oledClear();
          byte steps = 0;
          byte speedsR = 0;
          byte speedsL = 0;
          char Sdirection[2][2] = {"F", "B"};
          byte selectDirectR = 0;
          byte selectDirectL = 0;
          menuCount = 0;
          initEncoder(true);
          while (1) {
            headUp(true, false);
            if (touchUp(Button_RUN)) {
              speedsR = speedsL = 0;
              pwmMotor(0, 0);
              stopMotor();
              initEncoder(false);
              break;
            }
            if (touchUp(Button_UP)) {
              menuCount++;
              if (menuCount > 2) menuCount = 1;
            }
            if (touchUp(Button_DOWN)) {
              menuCount--;
              if (menuCount == 0 || menuCount == 255) menuCount == 2;
            }

            if (menuCount == 1) {
              if (touchUp(Button_OK)) {
                steps++;
                if (steps > 2) steps = 0;
              }
              if (steps == 1) {
                lcd_char(1, 65, 30, ">", true, false, false);
                if (touchUp(Button_PLUS)) {
                  selectDirectR++;
                  if (selectDirectR > 1) selectDirectR = 0;
                }
                if (touchUp(Button_MIN)) {
                  selectDirectR--;
                  if (selectDirectR == 255) selectDirectR == 1;
                }
              }
              else if (steps == 2) {
                lcd_char(1, 65, 40, ">", true, false, false);
                if (touchUp(Button_PLUS)) {
                  speedsR+=5;
                  if (speedsR > 255) speedsR = 255;
                }
                if (touchUp(Button_MIN)) {
                  speedsR-=5;
                  if (speedsR < 0) speedsR == 255;
                }
              }
              sprintf(buff, "Direct: %s", Sdirection[selectDirectR]);
              lcd_char(1, 70, 30, buff, true, false, false);
              lcd_char(1, 70, 40, "Speed:" + String(speedsR), true, false, false);
              lcd_char(1, 70, 50, "RPM: " + String(rpmR), true, false, false);
              lcd.fillRoundRect(65, 15, 60, 12, 2, SH110X_WHITE);
              lcd_char(1, 67, 17, "MTR Kanan", false, false, false);
            } else {
               lcd_char(1, 70, 40, "Speed:" + String(speedsR), true, false, false);
               lcd_char(1, 70, 50, "RPM: " + String(rpmR), true, false, false);
               lcd.drawRoundRect(65, 15, 60, 12, 2, SH110X_WHITE);
               lcd_char(1, 67, 17, "MTR Kanan", true, false, false);
            }

            if (menuCount == 2) {
              if (touchUp(Button_OK)) {
                steps++;
                if (steps > 2) steps = 0;
              }
              if (steps == 1) {
                lcd_char(1, 0, 30, ">", true, false, false);
                if (touchUp(Button_PLUS)) {
                  selectDirectL++;
                  if (selectDirectL > 1) selectDirectL = 0;
                }
                if (touchUp(Button_MIN)) {
                  selectDirectL--;
                  if (selectDirectL == 255) selectDirectL == 1;
                }
              }
              else if (steps == 2) {
                lcd_char(1, 0, 40, ">", true, false, false);
                if (touchUp(Button_PLUS)) {
                  speedsL+=5;
                  if (speedsL > 255) speedsL = 255;
                }
                if (touchUp(Button_MIN)) {
                  speedsL-=5;
                  if (speedsL < 0) speedsL == 255;
                }
              }
              sprintf(buff, "Direct: %s", Sdirection[selectDirectL]);
              lcd_char(1, 5, 30, buff, true, false, false);
              lcd_char(1, 5, 40, "Speed:" + String(speedsL), true, false, false);
              lcd_char(1, 5, 50, "RPM: " + String(rpmL), true, false, false);
              lcd.fillRoundRect(0, 15, 60, 12, 2, SH110X_WHITE);
              lcd_char(1, 2, 17, "MTR Kiri", false, false, false);
            } else {
              lcd_char(1, 5, 40, "Speed:" + String(speedsL), true, false, false);
              lcd_char(1, 5, 50, "RPM: " + String(rpmL), true, false, false);
              lcd.drawRoundRect(0, 15, 60, 12, 2, SH110X_WHITE);
              lcd_char(1, 2, 17, "MTR Kiri", true, false, false);
            }
            pwmMotor(selectDirectL == 0 ? speedsL : speedsL * -1, selectDirectR == 0 ? speedsR : speedsR * -1);
//            pwmMotor(selectDirectL == 0 ? map2(speedsL, 0, 100, 0, 255) : map2(speedsL, 0, 100, 0, 255) * -1,  selectDirectR == 0 ? map2(speedsR, 0, 100, 0, 255) : map2(speedsR, 0, 100, 0, 255) * -1);
            lcd.display();
          }
        }
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "5. Motor", false, false, false);
      } else {
        lcd_char(1, 2, 15, "5. Motor", true, false, false);
      }

      if (countMenu == 2) {
        if (touchUp(Button_OK)) {
          oledClear();
          byte steps = 1;
          byte selectPlan = 0;
          menuCount = 0;  
          while (1) {
            headUp(true, false);
            if (touchUp(Button_RUN)) {
              oledClear();
              break;
            }
            if (steps == 1) {
              sprintf(buff, "P:%d Yakin Dihapus ?", selectPlan + 1);
              lcd_char(1, 0, 15, buff, true, false, false);
              lcd_char(1, 20, 35, "Iya ", true, false, false);
              lcd_char(1, 70, 35, "Tidak", true, false, false);
              if(touchUp(Button_MIN)){
                menuCount++;
                if(menuCount > 1) menuCount = 1;
              }
              if(touchUp(Button_UP  )){
                menuCount--;
                if(menuCount == 255) menuCount = 0;
              }
              if(touchUp(Button_PLUS)){
                if(++selectPlan > 4) selectPlan = 4;
              }
              if(touchUp(Button_MIN)){
                if(--selectPlan == 255) selectPlan = 0;
              }
              if(menuCount == 1){
                lcd.drawRoundRect(18, 33, 22, 12, 2, SH110X_WHITE);
                if(touchUp(Button_OK)) steps = 2;
              } else if(menuCount == 0){
                lcd.drawRoundRect(68, 33, 38, 12, 2, SH110X_WHITE);
              }
            }
            else if (steps == 2) {
              for (byte i = 0; i < VAL_INDEX; i++) {
                  idx[selectPlan][i] = 0;
                  logic[selectPlan][i] = 0;
                  sensLogIdx[selectPlan][i] = 0;
                  trigW[selectPlan][i] = 0;
                  spdR[selectPlan][i] = 100;
                  spdL[selectPlan][i] = 100;
                  idelay[selectPlan][i] = 0;
                  timerA[selectPlan][i] = 0;
                  timerB[selectPlan][i] = 0;
                  speedA[selectPlan][i] = 0;
                  speedB[selectPlan][i] = 0;
                  clrLine[selectPlan][i] = 0;
                  pidProfile[selectPlan][i] = 0;
                  modeTIM[selectPlan][i] = 0;
                }
              delay(50);
              steps = 3;
            }
            else if (steps == 3) {
              headUp(true, false);
              lcd_char(1, 30, 35, "Selesai!!", true, false, false);
              saveIdxAll();
              lcd.display();
              delay(2000);
              break;
            }
            lcd.display();
          } // end bracket while true
        }
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "6. Reset Plan", false, false, false);
      } else {
        lcd_char(1, 2, 27, "6. Reset Plan", true, false, false);
      }

      if (countMenu == 3) {
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "7. Update OS", false, false, false);
      } else {

        lcd_char(1, 2, 37, "7. Update OS", true, false, false);
      }

      if (countMenu == 4) {
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "8. System Setting", false, false, false);
        if(touchUp(Button_OK)){
         menuSetting();

        }
      }
       else {
        lcd_char(1, 2, 47, "8. System Setting", true, false, false);
    }
      } 
    lcd.display();
  } // end bracket while
} // end Function Menu()
