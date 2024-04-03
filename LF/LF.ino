// Memasukan Library 
#include <Adafruit_PCF8574.h> // ini untuk button 
#include <SPI.h> // ini untuk memori external 
#include <Wire.h> 
#include <SPIMemory.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "addrMem.h"
#include "calc.h"

#define PCF8574_ADDR 0x27
#define OLED_ADDR 0x3C
#define Button_OK 5
#define Button_UP 3
#define Button_DOWN 4
#define Button_RUN 2
#define Button_PLUS 0
#define Button_MIN 1

#define LED 12
#define MUX_Kiri_ADC1 32 // V2 dituker ke 32
#define MUX_Kanan_ADC2 35
#define S1_MUX 13
#define S2_MUX 14
#define S3_MUX 15 // V2 dituker ke 15
#define ENC1A 36
#define ENC1B 39
#define ENC2A 33
#define ENC2B 25

#define MAXSENSOR 14
  
#define SLED(x) digitalWrite(LED, x)
#define eraseSec(x) memory.eraseSector(x)

#pragma wheelCalc
#define CPR 4*104
#define DiameterRoda 17 // satuan mm
float factor = (PI * DiameterRoda) / (CPR);
#pragma endregion

SPIFlash memory;
Adafruit_PCF8574 pcf;
Adafruit_SH1106G lcd = Adafruit_SH1106G(128, 64, &Wire, -1);

hw_timer_t *Timer0_Cfg = NULL;
hw_timer_t *Timer1_Cfg = NULL;
hw_timer_t *Timer2_Cfg = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

#define LED_PIN 12
#define ADCBAT 34

#pragma region variableADC
uint16_t adcVal[14];
uint16_t CalAdc[14];
uint8_t sensorSensivity;
int16_t maxVal[14];
int16_t minVal[14];
int16_t setMaxVal[14];
int16_t setMinVal[14];
#pragma endregion

#pragma region PID
int16_t error = 0;
int16_t lastError = 0;
float Kp;
float Ki;
float Kd;
float _Kp[7] = {6.00, 0.00, 0.00, 0.00, 0.00, 0.00, 7.00};
float _Ki[7];
float _Kd[7] = {8.10, 0.00, 0.00, 0.00, 0.00, 0.00, 11.00};
double P;
double I;
double D;
double sumError;
unsigned long prevTime;
volatile unsigned long timeNowPID;
double dt;
byte selectPresetPID = 0;
byte selectPresetPIDPlay;
#pragma endregion

#pragma region interface
byte modeMPU = 1 ;
byte modeWIFI= 1 ;
byte modeLF = 1 ;
byte modeENC = 1 ;
byte menuSet = 1 ;
byte countMenu = 1;
byte menuHome = 0;
byte halaman = 0;
bool homeS = true;
byte menuIdx = 0;
byte selectSet = 0;
byte halIdx = 0;
byte menuCount = 0;
byte IdIdx;
byte profilePid;
#pragma endregion

#pragma region prototype
char buff[100];
int valueSensor[14];
int sens;
bool stateIdxM = false;
bool stateRun = false;
#pragma endregion

#pragma region checkPointSET
#define VAL_CHECKP 8
byte countCP;
byte checkPoint[VAL_PLAN][VAL_CHECKP];
byte readCCheckpoint[VAL_PLAN][VAL_CHECKP];
byte timerACheckpoint[VAL_PLAN][VAL_CHECKP];
byte iDelayCheckpoint[VAL_PLAN][VAL_CHECKP];
byte readIdxCheckpoint[VAL_PLAN][VAL_CHECKP];
char actCheckpoint[4][10] = {"FORWARD", "LEFT", "RIGHT", "BACKWARD"};
#pragma endregion

#pragma region setting
uint8_t normalSpeed;
uint8_t plan;
uint8_t stopIndex;
byte countIdx;
byte idx[VAL_PLAN][VAL_INDEX];
byte logic[VAL_PLAN][VAL_INDEX];
byte sensLogIdx[VAL_PLAN][VAL_INDEX];
byte trigW[VAL_PLAN][VAL_INDEX];
byte spdR[VAL_PLAN][VAL_INDEX];
byte spdL[VAL_PLAN][VAL_INDEX];
int16_t idelay[VAL_PLAN][VAL_INDEX];
int16_t timerA[VAL_PLAN][VAL_INDEX];
int16_t timerB[VAL_PLAN][VAL_INDEX];
int16_t speedA[VAL_PLAN][VAL_INDEX];
int16_t speedB[VAL_PLAN][VAL_INDEX];
byte clrLine[VAL_PLAN][VAL_INDEX];
byte pidProfile[VAL_PLAN][VAL_INDEX];
byte modeTIM[VAL_PLAN][VAL_INDEX];
#pragma endregion

#pragma region idxVar
const unsigned int sensLog[23] {
  0b11111111111111, 0b00000000000000, 0b00000000000001, 0b10000000000000, 0b00000000000010, 0b01000000000000,
  0b00000000000100, 0b00100000000000, 0b00000000000011, 0b11000000000000, 0b00000000001100, 0b00110000000000,
  0b00000000000111, 0b11100000000000, 0b10000000000001, 0b01000000000010, 0b10000111100000, 0b00000111100001,
  0b11000111100000, 0b00000111100011, 0b11000000000011, 0b11100000000111, 0b11110000001111
};
char logika[4][3] = {"OR", "AD", "TM", "XR"};
char slctTrig[2][3] = {"MT", "LN"};
char act[10][10] = {"STOP", "FORWARD", "LEFT", "RIGHT", "BACKWARD", "PICK", "DROP", "TLEFT", "TRIGHT", "FAN"};
char clrLineI[2][6] = {"Black", "White"};
char slctPID[7][9] = {"Normal", "Profil 1", "Profil 2", "Profil 3", "Profil 4", "Profil 5", "Profil 6"};
char slctMode[3][5] = {"mS", "CmR", "CmL"};
char slctFLMODE[3][4] = {"FLC", "FLR", "FLL"};
#pragma endregion

#pragma region Encoder
int16_t countEnc_A;
int16_t countEnc_B;
int16_t rpmR, rpmL;
int16_t pulseL;
int16_t pulseR;
unsigned long lastTimeRPM;
#pragma endregion

#pragma region play
int dataSensor;
int16_t maxS;
byte countIdxPlay;
uint16_t timerSpeedA;
uint16_t timerSpeedB;
uint16_t TA;
uint16_t TB;
int16_t sensLogPlay;
bool clrLinePlay;
bool playAction = false;
long lastTimA;
long lastTimB;
#pragma endregion

#pragma region Tim
volatile long timeIdxPlay;
unsigned long lastTimeIdxPlay;
volatile long timeIdxTA;
unsigned long lastTimeIdxTA;
volatile long timeIdxTB;
unsigned long lastTimeIdxTB;
volatile long timeCountSpeed;
unsigned long lastCountSpeed;
#pragma endregion

void IRAM_ATTR Timer0_ISR(){ // timer for calculate RPM
  portENTER_CRITICAL_ISR(&timerMux);
  rpmL = pulseL * 6000 / 104;
  rpmR = pulseR * 6000 / 104 * (-1);
  pulseL = pulseR = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR Timer1_ISR(){ // timer for calculate play
  portENTER_CRITICAL_ISR(&timerMux);
  timeIdxTA++;
  timeIdxTB++;
  timeIdxPlay++;
  timeCountSpeed++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR Timer2_ISR(){
  portENTER_CRITICAL_ISR(&timerMux);
  timeNowPID++;
  if(timeNowPID > 4290000000) timeNowPID = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(240);
  initDisplay();
  memory.begin();

  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 10000, true);
  timerAlarmEnable(Timer0_Cfg);

  Timer1_Cfg = timerBegin(1, 80, true);
  timerAttachInterrupt(Timer1_Cfg, &Timer1_ISR, true);
  timerAlarmWrite(Timer1_Cfg, 10000, true);
  timerAlarmEnable(Timer1_Cfg);

  Timer2_Cfg = timerBegin(2, 80, true);
  timerAttachInterrupt(Timer2_Cfg, &Timer2_ISR, true);
  timerAlarmWrite(Timer2_Cfg, 1000, true);
  timerAlarmEnable(Timer2_Cfg);
  
  pinMode(LED, OUTPUT);
  pinMode(ENC1A, INPUT);
  pinMode(ENC1B, INPUT);
  pinMode(ENC2A, INPUT);
  pinMode(ENC2B, INPUT);
  setupSensor();
  initMotor();
  initButton();
  initEncoder(true);

  readCalib();
  readHome();
  read_PID();
  sensorSensivity = memory.readByte(addrSensSev);
  readIdx();
  readMaxMinSens();
  readCP();

  delay(500);
  oledClear();
}

void loop() {
  stopMotor();
homeSC:
  initEncoder(false);
  while (homeS) {
    headUp(true, false);
    dispSensor(readSensor());
    if (touchUp(Button_DOWN)) {
      menuHome++;
      if (menuHome > 5) menuHome = 1;
    }
    if (touchUp(Button_UP)) {
      menuHome--;
      if (menuHome == 255) menuHome = 5;
    }
    if (touchUp(Button_RUN)) {
      oledClear();
      stateRun = true;
      homeS = false;
      break;
    }

    if (menuHome == 1) {
      if (touchUp(Button_PLUS)) {
        plan++;
        if (plan > 4) plan = 0;
      }
      if (touchUp(Button_MIN)) {
        plan--;
        if (plan < 0) plan = 4;

        if (plan == 255) plan = 0;
      }

      lcd.fillRoundRect(32, 0, 23, 10, 3, SH110X_WHITE);
      sprintf(buff, "P:%d", plan + 1);
      lcd_char(1, 36, 2, buff, false, false, false);
    } else {
      lcd.drawRoundRect(32, 0, 23, 10, 3, SH110X_WHITE);
      sprintf(buff, "P:%d", plan + 1);
      lcd_char(1, 36, 2, buff, true, false, false);
    }

    if (menuHome == 3) {
      if (touchUp(Button_PLUS)) {
        countCP++;
        if (countCP > 8)  countCP = 0;
      }
      if (touchUp(Button_MIN)) {
        countCP--;
        if (countCP <0)  countCP = 8;

        if (countCP == 255) countCP = 0;
      }
      if(touchUp(Button_OK)){
        oledClear();
        selectSet = 0;
        menuCheckpoint();
      }
      lcd.fillRoundRect(0, 46, 30, 15, 3,  SH110X_WHITE);
      sprintf(buff, "CP:%01d", countCP);
      lcd_char(1, 2, 51, buff, false, false, false);
    } else {
      lcd.drawRoundRect(0, 46, 30, 15, 3,  SH110X_WHITE);
      sprintf(buff, "CP:%01d", countCP);
      lcd_char(1, 2, 51, buff, true, false, false);
    }

    if (menuHome == 4) {
      if (touchDown(Button_PLUS , 100)) {
        stopIndex++;
        if (stopIndex > 100) stopIndex = 0;
        delay(10);
      }
      if (touchDown(Button_MIN, 100)) {
        stopIndex--;
        if (stopIndex < 0) stopIndex = 100;
        if (plan == 255) plan = 0;
        delay(10);
      }
      lcd.fillRoundRect(32, 46, 52, 15, 3,  SH110X_WHITE);
      sprintf(buff, "STOP:%03d", stopIndex);
      lcd_char(1, 34, 51, buff, false, false, false);
    } else {
      lcd.drawRoundRect(32, 46, 52, 15, 3,  SH110X_WHITE);
      sprintf(buff, "STOP:%03d", stopIndex);
      lcd_char(1, 34, 51, buff, true, false, false);
    }

    if (menuHome == 2) {
      if (touchDown(Button_PLUS , 50)) {
        normalSpeed += 5;
        if (normalSpeed >= 255) normalSpeed = 0;
      }
      if (touchDown(Button_MIN , 50 )) {
        normalSpeed -= 5;
        if (normalSpeed <= 0) normalSpeed = 255;
      }
      lcd.fillRoundRect(48, 30, 35, 15, 3,  SH110X_WHITE);
      sprintf(buff, "N:%03d", normalSpeed);
      lcd_char(1, 51, 34, buff, false, false, false);
    } else {
      lcd.drawRoundRect(48, 30, 35, 15, 3,  SH110X_WHITE);
      sprintf(buff, "N:%03d", normalSpeed);
      lcd_char(1, 51, 34, buff, true, false, false);
    }

    if (menuHome == 5) {
      if (touchUp(Button_OK)) {
        lcd.clearDisplay();
        menu();
      }
      lcd.fillRoundRect(90, 46, 35, 15, 3,  SH110X_WHITE);
      lcd_char(1, 96, 51, "MENU", false, false, false);
    } else {
      lcd.drawRoundRect(90, 46, 35, 15, 3,  SH110X_WHITE);
      lcd_char(1, 96, 51, "MENU", true, false, false);
    }
    lcd.display();
  } // end bracket While true

  if (stateRun) {
    if(countCP != 0){
        readCounter(readCCheckpoint[plan][countCP]);
        countIdxPlay = readIdxCheckpoint[plan][countCP];
    }
    while (1) {
      dataSensor = readSensor();
      sensLogPlay = sensLog[sensLogIdx[plan][countIdxPlay]];
      selectPresetPIDPlay = pidProfile[plan][countIdxPlay];
      clrLine[plan][countIdxPlay] == 0 ? clrLinePlay = false : clrLinePlay = true;

      switch (logic[plan][countIdxPlay]) {
        case 0: // Or
//          dataSensor = readSensor();
          if (clrLinePlay) {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if (~(readSensor()) & sensLogPlay) {
                SLED(1);
                playAction = true;
                break;
              }
            }
          } else {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if (readSensor() & sensLogPlay) {
                SLED(1);
                playAction = true;
                break;
              }
            }
          }
          break;

        case 1: // And
//          dataSensor = readSensor();
          if (clrLinePlay) {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if ((~(readSensor()) & sensLogPlay) == sensLogPlay) {
                SLED(1);
                playAction = true;
                break;
              }
            }
          } else {
            while(1){
              maxS = normalSpeed;
              program(readSensor(), "center");
              if ((readSensor() & sensLogPlay) == sensLogPlay) {
               SLED(1);
               playAction = true;
               break;
              }
            }
          }
          break;

        case 2: // TIM
          dataSensor = readSensor();
          SLED(1);
          playAction = true;
          maxS = normalSpeed;
          break;

        case 3: // XOR
          dataSensor = readSensor();
          if (clrLinePlay) {
            byte logSen = sensLogIdx[plan][countIdxPlay];
            if (logSen == 16) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b10000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 17) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b00000000000001) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 18) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b11000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 19) {
              if (~(dataSensor) & 0b00000111100000) {
                if (~(dataSensor) & 0b00000000000011) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
          } else {
            byte logSen = sensLogIdx[plan][countIdxPlay];
            if (logSen == 16) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b10000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 17) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b00000000000001) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 18) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b11000000000000) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
            else if (logSen == 19) {
              if (dataSensor & 0b00000111100000) {
                if (dataSensor & 0b00000000000011) {
                  SLED(1);
                  playAction = true;
                }
              } else {
                ILED(500);
                maxS = normalSpeed;
                program(dataSensor, "center");
                playAction = false;
              }
            }
          }
          break;
      }

      if (playAction) { 
        readCounter(idx[plan][countIdxPlay]);
        dataSensor = readSensor();
        SLED(0);
        TA = timerA[plan][countIdxPlay];
        timerSpeedA = speedA[plan][countIdxPlay];
        int16_t sTA = timerSpeedA / 4;
        lastTimeIdxTA = timeIdxTA;
        countEnc_B = countEnc_A = 0;
        initEncoder(true);
        while (1) {
          if (speedA[plan][countIdxPlay] == 0) {
            maxS = 0;
            stopMotor();
          }
          else if (sTA < speedA[plan][countIdxPlay]) {
            sTA += 2;
            if (sTA < 40) maxS = 40;
            else if (sTA >= speedA[plan][countIdxPlay]) maxS = speedA[plan][countIdxPlay];
            else maxS = sTA;
          }
          program(readSensor(), "center");
          if(modeTIM[plan][countIdxPlay] == 0){
            if (timeIdxTA - lastTimeIdxTA >= TA) break;
          }
          if(modeTIM[plan][countIdxPlay] == 1){
            if(measureLengthR() >= TA) break;
          }
          if(modeTIM[plan][countIdxPlay] == 2){
            if(measureLengthL() >= TA) break;
          }
        }

        TB = timerB[plan][countIdxPlay];
        timerSpeedB = speedB[plan][countIdxPlay];
        int16_t sTB = timerSpeedB / 4;
        lastTimeIdxTB = timeIdxTB;
        while (1) {
          if (speedB[plan][countIdxPlay] == 0) {
            maxS = 0;
            stopMotor();
          }
          else if (timerA[plan][countIdxPlay] == 0) {
            sTB += 2;
            if (sTB < 40) maxS = 40;
            else maxS = sTB;
            if (sTB >= speedB[plan][countIdxPlay]) maxS = speedB[plan][countIdxPlay];
          } else if ( speedB[plan][countIdxPlay] > speedA[plan][countIdxPlay]) {
            timerSpeedA += 2;
            maxS = timerSpeedA;
            if ( timerSpeedA > speedB[plan][countIdxPlay]) maxS = speedB[plan][countIdxPlay];
          } else if ( speedB[plan][countIdxPlay] < speedA[plan][countIdxPlay]) {
            timerSpeedA -= 3;
            maxS = timerSpeedA;
            if ( timerSpeedA <= speedB[plan][countIdxPlay]) maxS = speedB[plan][countIdxPlay];
          }
          program(readSensor(), "center");
          if (timeIdxTB - lastTimeIdxTB >= TB) break;
        }

        if (countIdxPlay > stopIndex) {
          TA = TB = maxS = 0;
          stopMotor();
        } else if (touchUp(Button_OK)){
          TA = TB = countIdxPlay = 0;
          break;
        }
        playAction = false;
      } // end bracket playAction
      TA = TB = 0;
      countIdxPlay++;

      if (countIdxPlay > stopIndex) {
        stopMotor();
        TA = TB = maxS = countIdxPlay = 0;
        stateRun = playAction = false;
        homeS = true;
        break;
        goto homeSC;
      }

      if (touchUp(Button_OK)) {
        TA = TB = maxS = countIdxPlay = 0;
        stateRun = playAction = false;
        homeS = true;
        stopMotor();
        break;
        goto homeSC;
      }
    } // end while bracket
  } // if stateRun

} // end void loop
