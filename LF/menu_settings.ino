void menuSetting (){
      oledClear();
      const char* set[] = {"ON" , "OFF"};
      const char* mode_lf[] = {"TRANSPORTER" , "LINE TRACER"};

      while(1){
      headUp(true, false);
      if(touchUp(Button_RUN))break;
      if(touchUp(Button_UP)) {
        menuSet += 1; 
        if(menuSet > 4 )menuSet = 1;
        }
      if(touchUp(Button_DOWN)){
        menuSet -= 1;
        if(menuSet < 1 )menuSet = 4;
        }
      if (menuSet == 1) {

        if (touchUp(Button_PLUS)) {
          modeMPU++; if(modeMPU>1)modeMPU = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeMPU--; if(modeMPU>0)modeMPU = 1 ;
        }        
        lcd.fillRect(0, 14, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 15, "MPU  : " + String(set[modeMPU]), false, false, false);
      } else {
        lcd_char(1, 2, 15, "MPU  : " + String(set[modeMPU]), true, false, false);
      }

      if (menuSet == 2) {
        if (touchUp(Button_PLUS)) {
          modeENC++; if(modeENC>1)modeENC = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeENC--; if(modeENC>0)modeENC = 1 ;
        }        
        lcd.fillRect(0, 24, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 27, "ENC  : " + String(set[modeENC]) , false, false, false);
      } else {
        lcd_char(1, 2, 27, "ENC  : " + String(set[modeENC]) , true, false, false);
      }


      if (menuSet == 3) {
        if (touchUp(Button_PLUS)) {
          modeWIFI++; if(modeWIFI>1)modeWIFI = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeWIFI--; if(modeWIFI>0)modeWIFI = 1 ;
        }        
        lcd.fillRect(0, 34, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 37, "WIFI : " + String(set[modeWIFI]), false, false, false);
      } else {
        lcd_char(1, 2, 37, "WIFI : " + String(set[modeWIFI]), true, false, false);
      }

      if (menuSet == 4) {
        if (touchUp(Button_PLUS)) {
          modeLF++; if(modeLF>1)modeLF = 0 ;
        }
        if (touchUp(Button_MIN)) {
          modeLF--; if(modeLF>0)modeLF = 1 ;
        }        
        lcd.fillRect(0, 44, 120, 13, SH110X_WHITE);
        lcd_char(1, 2, 47, "MODE : " + String(mode_lf[modeLF]), false, false, false);
      } else {
        lcd_char(1, 2, 47, "MODE : " + String(mode_lf[modeLF]), true, false, false);
      }
      lcd.display();
      }//end while
      

}

