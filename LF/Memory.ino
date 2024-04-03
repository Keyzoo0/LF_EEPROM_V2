 #include "addrMem.h"

void saveAll() {
  SLED(1);
  eraseSec(0);
  saveCalib();
  saveHome();
  saveSensorSensivity();
  savePID();
  save_PID();
  saveMaxMinSens();
  SLED(0);
}

void saveIdxAll(){
  SLED(1);
  eraseSec(4096);
  eraseSec(8192);
  saveIdx();
  SLED(0);
}

void saveCP(){
  SLED(1);
  eraseSec(16384);
  for(uint8_t i = 0; i < VAL_CHECKP; i++){
    _saveActCPP1[i] = readCCheckpoint[0][i];  _saveActCPP2[i] = readCCheckpoint[1][i];  
    _saveiDelayCPP1[i] = timerACheckpoint[0][i];  _saveiDelayCPP2[i] = timerACheckpoint[1][i];
    _savetimerACPP1[i] = iDelayCheckpoint[0][i];  _savetimerACPP2[i] = iDelayCheckpoint[1][i];
    _saveReadIdxCPP1[i] = readIdxCheckpoint[0][i];  _saveReadIdxCPP2[i] = readIdxCheckpoint[1][i];

    _saveActCPP3[i] = readCCheckpoint[2][i];  _saveActCPP4[i] = readCCheckpoint[3][i];  
    _saveiDelayCPP3[i] = timerACheckpoint[2][i];  _saveiDelayCPP4[i] = timerACheckpoint[3][i];
    _savetimerACPP3[i] = iDelayCheckpoint[2][i];  _savetimerACPP4[i] = iDelayCheckpoint[3][i];
    _saveReadIdxCPP3[i] = readIdxCheckpoint[2][i];  _saveReadIdxCPP4[i] = readIdxCheckpoint[3][i];

    _saveActCPP5[i] = readCCheckpoint[4][i];  
    _saveiDelayCPP5[i] = timerACheckpoint[4][i];
    _savetimerACPP5[i] = iDelayCheckpoint[4][i];
    _saveReadIdxCPP5[i] = readIdxCheckpoint[4][i];
  }
  memory.writeByteArray(addrACTCP1, _saveActCPP1, VAL_CHECKP);  memory.writeByteArray(addrACTCP2, _saveActCPP2, VAL_CHECKP);
  memory.writeByteArray(addrtimerACP1, _saveiDelayCPP1, VAL_CHECKP);  memory.writeByteArray(addrtimerACP2, _saveiDelayCPP2, VAL_CHECKP);
  memory.writeByteArray(addridelayCP1, _savetimerACPP1, VAL_CHECKP);  memory.writeByteArray(addridelayCP2, _savetimerACPP2, VAL_CHECKP);
  memory.writeByteArray(addrIdxCP1, _saveReadIdxCPP1, VAL_CHECKP);  memory.writeByteArray(addrIdxCP2, _saveReadIdxCPP2, VAL_CHECKP);

  memory.writeByteArray(addrACTCP3, _saveActCPP3, VAL_CHECKP);  memory.writeByteArray(addrACTCP4, _saveActCPP4, VAL_CHECKP);
  memory.writeByteArray(addrtimerACP3, _saveiDelayCPP3, VAL_CHECKP);  memory.writeByteArray(addrtimerACP4, _saveiDelayCPP4, VAL_CHECKP);
  memory.writeByteArray(addridelayCP3, _savetimerACPP3, VAL_CHECKP);  memory.writeByteArray(addridelayCP4, _savetimerACPP4, VAL_CHECKP);
  memory.writeByteArray(addrIdxCP3, _saveReadIdxCPP3, VAL_CHECKP);  memory.writeByteArray(addrIdxCP4, _saveReadIdxCPP4, VAL_CHECKP);

  memory.writeByteArray(addrACTCP5, _saveActCPP5, VAL_CHECKP);
  memory.writeByteArray(addrtimerACP5, _saveiDelayCPP5, VAL_CHECKP);
  memory.writeByteArray(addridelayCP5, _savetimerACPP5, VAL_CHECKP);
  memory.writeByteArray(addrIdxCP5, _saveReadIdxCPP5, VAL_CHECKP);
  delayMicroseconds(100);
  SLED(0);
}

void saveHome() {
  _saveHomeScreen[0] = plan;
  _saveHomeScreen[1] = normalSpeed;
  _saveHomeScreen[2] = stopIndex;
  _saveHomeScreen[3] = countCP;
  memory.writeByteArray(addrHome, _saveHomeScreen, 7);
}

void saveCalib(){
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    value[i] = CalAdc[i];
    H[i] = value[i]>>8;
    L[i] = value[i] & 0x00ff;
  }
  memory.writeByteArray(addrCalibA, H, 14);
  memory.writeByteArray(addrCalibB, L, 14);
}

void saveMaxMinSens(){
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    MaxSensH[i] = setMaxVal[i] >> 8;
    MaxSensL[i] = setMaxVal[i] & 0x00ff;
    MinSensH[i] = setMinVal[i] >> 8;
    MinSensL[i] = setMinVal[i] & 0x00ff;
  }
  memory.writeByteArray(addrsetMaxSensH, MaxSensH, 14);
  memory.writeByteArray(addrsetMaxSensL, MaxSensL, 14);
  memory.writeByteArray(addrsetMinSensH, MinSensH, 14);
  memory.writeByteArray(addrsetMinSensL, MinSensL, 14);
}

void saveSensorSensivity() {
  memory.writeByte(addrSensSev, sensorSensivity);
}

void savePID(){
  memory.writeFloat(addrKp, Kp);
  memory.writeFloat(addrKi, Ki);
  memory.writeFloat(addrKd, Kd);
}

void save_PID(){
  for(byte i = 0; i < 7; i++){
    memory.writeFloat(addr_Kp(i), _Kp[i]);
    memory.writeFloat(addr_Kd(i), _Kd[i]);
  }
}

void saveIdx() {
  for (uint8_t i = 0; i < VAL_INDEX; i++) {
    _saveIdxP1[i] = idx[0][i];
    _savelogicP1[i] = logic[0][i];
    _savesensLogIdxP1[i] = sensLogIdx[0][i];
    _savetrigWP1[i] = trigW[0][i];
    _savespdRP1[i] = spdR[0][i];
    _savespdLP1[i] = spdL[0][i];
    _saveidelayP1H[i] = idelay[0][i] >> 8;
    _saveidelayP1L[i] = idelay[0][i] & 0x00ff;
    _savetimerAP1H[i] = timerA[0][i] >> 8;
    _savetimerAP1L[i] = timerA[0][i] & 0x00ff;
    _savetimerBP1H[i] = timerB[0][i] >> 8;
    _savetimerBP1L[i] = timerB[0][i] & 0x00ff;
    _savespeedAP1[i] = speedA[0][i];
    _savespeedBP1[i] = speedB[0][i];
    _saveclrLineP1[i] = clrLine[0][i];
    _saveprofilePIDP1[i] = pidProfile[0][i];
    _saveModeTIMP1[i] = modeTIM[0][i];

    _saveIdxP2[i] = idx[1][i];
    _savelogicP2[i] = logic[1][i];
    _savesensLogIdxP2[i] = sensLogIdx[1][i];
    _savetrigWP2[i] = trigW[1][i];
    _savespdRP2[i] = spdR[1][i];
    _savespdLP2[i] = spdL[1][i];
    _saveidelayP2H[i] = idelay[1][i] >> 8;
    _saveidelayP2L[i] = idelay[1][i] & 0x00ff;
    _savetimerAP2H[i] = timerA[1][i] >> 8;
    _savetimerAP2L[i] = timerA[1][i] & 0x00ff;
    _savetimerBP2H[i] = timerB[1][i] >> 8;
    _savetimerBP2L[i] = timerB[1][i] & 0x00ff;
    _savespeedAP2[i] = speedA[1][i];
    _savespeedBP2[i] = speedB[1][i];
    _saveclrLineP2[i] = clrLine[1][i];
    _saveprofilePIDP2[i] = pidProfile[1][i];
    _saveModeTIMP2[i] = modeTIM[1][i];

    _saveIdxP3[i] = idx[2][i];
    _savelogicP3[i] = logic[2][i];
    _savesensLogIdxP3[i] = sensLogIdx[2][i];
    _savetrigWP3[i] = trigW[2][i];
    _savespdRP3[i] = spdR[2][i];
    _savespdLP3[i] = spdL[2][i];
    _saveidelayP3H[i] = idelay[2][i] >> 8;
    _saveidelayP3L[i] = idelay[2][i] & 0x00ff;
    _savetimerAP3H[i] = timerA[2][i] >> 8;
    _savetimerAP3L[i] = timerA[2][i] & 0x00ff;
    _savetimerBP3H[i] = timerB[2][i] >> 8;
    _savetimerBP3L[i] = timerB[2][i] & 0x00ff;
    _savespeedAP3[i] = speedA[2][i];
    _savespeedBP3[i] = speedB[2][i];
    _saveclrLineP3[i] = clrLine[2][i];
    _saveprofilePIDP3[i] = pidProfile[2][i];
    _saveModeTIMP3[i] = modeTIM[2][i];

    _saveIdxP4[i] = idx[3][i];
    _savelogicP4[i] = logic[3][i];
    _savesensLogIdxP4[i] = sensLogIdx[3][i];
    _savetrigWP4[i] = trigW[3][i];
    _savespdRP4[i] = spdR[3][i];
    _savespdLP4[i] = spdL[3][i];
    _saveidelayP4H[i] = idelay[3][i] >> 8;
    _saveidelayP4L[i] = idelay[3][i] & 0x00ff;
    _savetimerAP4H[i] = timerA[3][i] >> 8;
    _savetimerAP4L[i] = timerA[3][i] & 0x00ff;
    _savetimerBP4H[i] = timerB[3][i] >> 8;
    _savetimerBP4L[i] = timerB[3][i] & 0x00ff;
    _savespeedAP4[i] = speedA[3][i];
    _savespeedBP4[i] = speedB[3][i];
    _saveclrLineP4[i] = clrLine[3][i];
    _saveprofilePIDP4[i] = pidProfile[3][i];
    _saveModeTIMP4[i] = modeTIM[3][i];

    _saveIdxP5[i] = idx[4][i];
    _savelogicP5[i] = logic[4][i];
    _savesensLogIdxP5[i] = sensLogIdx[4][i];
    _savetrigWP5[i] = trigW[4][i];
    _savespdRP5[i] = spdR[4][i];
    _savespdLP5[i] = spdL[4][i];
    _saveidelayP5H[i] = idelay[4][i] >> 8;
    _saveidelayP5L[i] = idelay[4][i] & 0x00ff;
    _savetimerAP5H[i] = timerA[4][i] >> 8;
    _savetimerAP5L[i] = timerA[4][i] & 0x00ff;
    _savetimerBP5H[i] = timerB[4][i] >> 8;
    _savetimerBP5L[i] = timerB[4][i] & 0x00ff;
    _savespeedAP5[i] = speedA[4][i];
    _savespeedBP5[i] = speedB[4][i];
    _saveclrLineP5[i] = clrLine[4][i];
    _saveprofilePIDP5[i] = pidProfile[4][i];
    _saveModeTIMP5[i] = modeTIM[4][i];
  }

  memory.writeByteArray(addrCountIdxP1(1), _saveIdxP1, VAL_INDEX);  memory.writeByteArray(addrCountIdxP2(1), _saveIdxP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(2), _savelogicP1, VAL_INDEX);  memory.writeByteArray(addrCountIdxP2(2), _savelogicP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(3), _savesensLogIdxP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(3), _savesensLogIdxP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(4), _savetrigWP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(4), _savetrigWP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(5), _savespdRP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(5), _savespdRP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(6), _savespdLP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(6), _savespdLP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(7), _saveidelayP1H, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(7), _saveidelayP2H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(8), _savetimerAP1H, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(8), _savetimerAP2H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(9), _savetimerBP1H, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(9), _savetimerBP2H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(10), _savespeedAP1, VAL_INDEX);  memory.writeByteArray(addrCountIdxP2(10), _savespeedAP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(11), _savespeedBP1, VAL_INDEX);  memory.writeByteArray(addrCountIdxP2(11), _savespeedBP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(12), _saveclrLineP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(12), _saveclrLineP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(13), _saveidelayP1L, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(13), _saveidelayP2L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(14), _savetimerAP1L, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(14), _savetimerAP2L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(15), _savetimerBP1L, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(15), _savetimerBP2L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(16), _saveprofilePIDP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(16), _saveprofilePIDP2, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP1(17), _saveModeTIMP1, VAL_INDEX); memory.writeByteArray(addrCountIdxP2(17), _saveModeTIMP2, VAL_INDEX);

  memory.writeByteArray(addrCountIdxP3(1), _saveIdxP3, VAL_INDEX);  memory.writeByteArray(addrCountIdxP4(1), _saveIdxP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(2), _savelogicP3, VAL_INDEX);  memory.writeByteArray(addrCountIdxP4(2), _savelogicP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(3), _savesensLogIdxP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(3), _savesensLogIdxP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(4), _savetrigWP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(4), _savetrigWP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(5), _savespdRP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(5), _savespdRP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(6), _savespdLP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(6), _savespdLP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(7), _saveidelayP3H, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(7), _saveidelayP4H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(8), _savetimerAP3H, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(8), _savetimerAP4H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(9), _savetimerBP3H, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(9), _savetimerBP4H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(10), _savespeedAP3, VAL_INDEX);  memory.writeByteArray(addrCountIdxP4(10), _savespeedAP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(11), _savespeedBP3, VAL_INDEX);  memory.writeByteArray(addrCountIdxP4(11), _savespeedBP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(12), _saveclrLineP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(12), _saveclrLineP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(13), _saveidelayP3L, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(13), _saveidelayP4L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(14), _savetimerAP3L, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(14), _savetimerAP4L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(15), _savetimerBP3L, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(15), _savetimerBP4L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(16), _saveprofilePIDP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(16), _saveprofilePIDP4, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP3(17), _saveModeTIMP3, VAL_INDEX); memory.writeByteArray(addrCountIdxP4(17), _saveModeTIMP4, VAL_INDEX);
  

  memory.writeByteArray(addrCountIdxP5(1), _saveIdxP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(2), _savelogicP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(3), _savesensLogIdxP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(4), _savetrigWP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(5), _savespdRP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(6), _savespdLP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(7), _saveidelayP5H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(8), _savetimerAP5H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(9), _savetimerBP5H, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(10), _savespeedAP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(11), _savespeedBP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(12), _saveclrLineP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(13), _saveidelayP5L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(14), _savetimerAP5L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(15), _savetimerBP5L, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(16), _saveprofilePIDP5, VAL_INDEX);
  memory.writeByteArray(addrCountIdxP5(17), _saveModeTIMP5, VAL_INDEX);
}

void readIdx() {
  memory.readByteArray(addrCountIdxP1(1), _saveIdxP1, VAL_INDEX);  memory.readByteArray(addrCountIdxP2(1), _saveIdxP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(2), _savelogicP1, VAL_INDEX);  memory.readByteArray(addrCountIdxP2(2), _savelogicP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(3), _savesensLogIdxP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(3), _savesensLogIdxP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(4), _savetrigWP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(4), _savetrigWP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(5), _savespdRP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(5), _savespdRP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(6), _savespdLP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(6), _savespdLP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(7), _saveidelayP1H, VAL_INDEX); memory.readByteArray(addrCountIdxP2(7), _saveidelayP2H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(8), _savetimerAP1H, VAL_INDEX); memory.readByteArray(addrCountIdxP2(8), _savetimerAP2H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(9), _savetimerBP1H, VAL_INDEX); memory.readByteArray(addrCountIdxP2(9), _savetimerBP2H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(10), _savespeedAP1, VAL_INDEX);  memory.readByteArray(addrCountIdxP2(10), _savespeedAP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(11), _savespeedBP1, VAL_INDEX);  memory.readByteArray(addrCountIdxP2(11), _savespeedBP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(12), _saveclrLineP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(12), _saveclrLineP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(13), _saveidelayP1L, VAL_INDEX); memory.readByteArray(addrCountIdxP2(13), _saveidelayP2L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(14), _savetimerAP1L, VAL_INDEX); memory.readByteArray(addrCountIdxP2(14), _savetimerAP2L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(15), _savetimerBP1L, VAL_INDEX); memory.readByteArray(addrCountIdxP2(15), _savetimerBP2L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(16), _saveprofilePIDP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(16), _saveprofilePIDP2, VAL_INDEX);
  memory.readByteArray(addrCountIdxP1(17), _saveModeTIMP1, VAL_INDEX); memory.readByteArray(addrCountIdxP2(17), _saveModeTIMP2, VAL_INDEX);


  memory.readByteArray(addrCountIdxP3(1), _saveIdxP3, VAL_INDEX);  memory.readByteArray(addrCountIdxP4(1), _saveIdxP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(2), _savelogicP3, VAL_INDEX);  memory.readByteArray(addrCountIdxP4(2), _savelogicP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(3), _savesensLogIdxP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(3), _savesensLogIdxP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(4), _savetrigWP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(4), _savetrigWP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(5), _savespdRP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(5), _savespdRP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(6), _savespdLP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(6), _savespdLP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(7), _saveidelayP3H, VAL_INDEX); memory.readByteArray(addrCountIdxP4(7), _saveidelayP4H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(8), _savetimerAP3H, VAL_INDEX); memory.readByteArray(addrCountIdxP4(8), _savetimerAP4H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(9), _savetimerBP3H, VAL_INDEX); memory.readByteArray(addrCountIdxP4(9), _savetimerBP4H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(10), _savespeedAP3, VAL_INDEX);  memory.readByteArray(addrCountIdxP4(10), _savespeedAP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(11), _savespeedBP3, VAL_INDEX);  memory.readByteArray(addrCountIdxP4(11), _savespeedBP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(12), _saveclrLineP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(12), _saveclrLineP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(13), _saveidelayP3L, VAL_INDEX); memory.readByteArray(addrCountIdxP4(13), _saveidelayP4L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(14), _savetimerAP3L, VAL_INDEX); memory.readByteArray(addrCountIdxP4(14), _savetimerAP4L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(15), _savetimerBP3L, VAL_INDEX); memory.readByteArray(addrCountIdxP4(15), _savetimerBP4L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(16), _saveprofilePIDP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(16), _saveprofilePIDP4, VAL_INDEX);
  memory.readByteArray(addrCountIdxP3(17), _saveModeTIMP3, VAL_INDEX); memory.readByteArray(addrCountIdxP4(17), _saveModeTIMP4, VAL_INDEX);

  memory.readByteArray(addrCountIdxP5(1), _saveIdxP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(2), _savelogicP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(3), _savesensLogIdxP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(4), _savetrigWP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(5), _savespdRP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(6), _savespdLP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(7), _saveidelayP5H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(8), _savetimerAP5H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(9), _savetimerBP5H, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(10), _savespeedAP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(11), _savespeedBP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(12), _saveclrLineP5, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(13), _saveidelayP5L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(14), _savetimerAP5L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(15), _savetimerBP5L, VAL_INDEX);
  memory.readByteArray(addrCountIdxP5(16), _saveprofilePIDP5, VAL_INDEX); 
  memory.readByteArray(addrCountIdxP5(17), _saveModeTIMP5, VAL_INDEX);

  for (uint8_t i = 0; i < VAL_INDEX; i++) {
    idx[0][i] = _saveIdxP1[i];
    logic[0][i] = _savelogicP1[i];
    sensLogIdx[0][i] = _savesensLogIdxP1[i];
    trigW[0][i] = _savetrigWP1[i];
    spdR[0][i] = _savespdRP1[i];
    spdL[0][i] = _savespdLP1[i];
    idelay[0][i] = _saveidelayP1H[i] << 8 | (_saveidelayP1L[i] & 0x00ff);
    timerA[0][i] = _savetimerAP1H[i] << 8 | (_savetimerAP1L[i] & 0x00ff);
    timerB[0][i] = _savetimerBP1H[i] << 8 | (_savetimerBP1L[i] & 0x00ff);
    speedA[0][i] = _savespeedAP1[i];
    speedB[0][i] = _savespeedBP1[i];
    clrLine[0][i] = _saveclrLineP1[i];
    pidProfile[0][i] = _saveprofilePIDP1[i];
    modeTIM[0][i] = _saveModeTIMP1[i];

    idx[1][i] = _saveIdxP2[i];
    logic[1][i] = _savelogicP2[i];
    sensLogIdx[1][i] = _savesensLogIdxP2[i];
    trigW[1][i] = _savetrigWP2[i];
    spdR[1][i] = _savespdRP2[i];
    spdL[1][i] = _savespdLP2[i];
    idelay[1][i] = _saveidelayP2H[i] << 8 | (_saveidelayP2L[i] & 0x00ff);
    timerA[1][i] = _savetimerAP2H[i] << 8 | (_savetimerAP2L[i] & 0x00ff);
    timerB[1][i] = _savetimerBP2H[i] << 8 | (_savetimerBP2L[i] & 0x00ff);
    speedA[1][i] = _savespeedAP2[i];
    speedB[1][i] = _savespeedBP2[i];
    clrLine[1][i] = _saveclrLineP2[i];
    pidProfile[1][i] = _saveprofilePIDP2[i];
    modeTIM[1][i] = _saveModeTIMP2[i];

    idx[2][i] = _saveIdxP3[i];
    logic[2][i] = _savelogicP3[i];
    sensLogIdx[2][i] = _savesensLogIdxP3[i];
    trigW[2][i] = _savetrigWP3[i];
    spdR[2][i] = _savespdRP3[i];
    spdL[2][i] = _savespdLP3[i];
    idelay[2][i] = _saveidelayP3H[i] << 8 | (_saveidelayP3L[i] & 0x00ff);
    timerA[2][i] = _savetimerAP3H[i] << 8 | (_savetimerAP3L[i] & 0x00ff);
    timerB[2][i] = _savetimerBP3H[i] << 8 | (_savetimerBP3L[i] & 0x00ff);
    speedA[2][i] = _savespeedAP3[i];
    speedB[2][i] = _savespeedBP3[i];
    clrLine[2][i] = _saveclrLineP3[i];
    pidProfile[2][i] = _saveprofilePIDP3[i];
    modeTIM[2][i] = _saveModeTIMP3[i];

    idx[3][i] = _saveIdxP4[i];
    logic[3][i] = _savelogicP4[i];
    sensLogIdx[3][i] = _savesensLogIdxP4[i];
    trigW[3][i] = _savetrigWP4[i];
    spdR[3][i] = _savespdRP4[i];
    spdL[3][i] = _savespdLP4[i];
    idelay[3][i] = _saveidelayP4H[i] << 8 | (_saveidelayP4L[i] & 0x00ff);
    timerA[3][i] = _savetimerAP4H[i] << 8 | (_savetimerAP4L[i] & 0x00ff);
    timerB[3][i] = _savetimerBP4H[i] << 8 | (_savetimerBP4L[i] & 0x00ff);
    speedA[3][i] = _savespeedAP4[i];
    speedB[3][i] = _savespeedBP4[i];
    clrLine[3][i] = _saveclrLineP4[i];
    pidProfile[3][i] = _saveprofilePIDP4[i];
    modeTIM[3][i] = _saveModeTIMP4[i];

    idx[4][i] = _saveIdxP5[i];
    logic[4][i] = _savelogicP5[i];
    sensLogIdx[4][i] = _savesensLogIdxP5[i];
    trigW[4][i] = _savetrigWP5[i];
    spdR[4][i] = _savespdRP5[i];
    spdL[4][i] = _savespdLP5[i];
    idelay[4][i] = _saveidelayP5H[i] << 8 | (_saveidelayP5L[i] & 0x00ff);
    timerA[4][i] = _savetimerAP5H[i] << 8 | (_savetimerAP5L[i] & 0x00ff);
    timerB[4][i] = _savetimerBP5H[i] << 8 | (_savetimerBP5L[i] & 0x00ff);
    speedA[4][i] = _savespeedAP5[i];
    speedB[4][i] = _savespeedBP5[i];
    clrLine[4][i] = _saveclrLineP5[i];
    pidProfile[4][i] = _saveprofilePIDP5[i];
    modeTIM[4][i] = _saveModeTIMP5[i];
  }
  delay(10);
}

void readCP(){
  memory.readByteArray(addrACTCP1, _saveActCPP1, VAL_CHECKP); memory.readByteArray(addrACTCP2, _saveActCPP2, VAL_CHECKP);
  memory.readByteArray(addrtimerACP1, _saveiDelayCPP1, VAL_CHECKP); memory.readByteArray(addrtimerACP2, _saveiDelayCPP2, VAL_CHECKP);
  memory.readByteArray(addridelayCP1, _savetimerACPP1, VAL_CHECKP); memory.readByteArray(addridelayCP2, _savetimerACPP2, VAL_CHECKP);
  memory.readByteArray(addrIdxCP1, _saveReadIdxCPP1, VAL_CHECKP); memory.readByteArray(addrIdxCP2, _saveReadIdxCPP2, VAL_CHECKP);

  memory.readByteArray(addrACTCP3, _saveActCPP3, VAL_CHECKP); memory.readByteArray(addrACTCP4, _saveActCPP4, VAL_CHECKP);
  memory.readByteArray(addrtimerACP3, _saveiDelayCPP3, VAL_CHECKP); memory.readByteArray(addrtimerACP4, _saveiDelayCPP4, VAL_CHECKP);
  memory.readByteArray(addridelayCP3, _savetimerACPP3, VAL_CHECKP); memory.readByteArray(addridelayCP4, _savetimerACPP4, VAL_CHECKP);
  memory.readByteArray(addrIdxCP3, _saveReadIdxCPP3, VAL_CHECKP); memory.readByteArray(addrIdxCP4, _saveReadIdxCPP4, VAL_CHECKP);

  memory.readByteArray(addrACTCP5, _saveActCPP5, VAL_CHECKP);
  memory.readByteArray(addrtimerACP5, _saveiDelayCPP5, VAL_CHECKP);
  memory.readByteArray(addridelayCP5, _savetimerACPP5, VAL_CHECKP);
  memory.readByteArray(addrIdxCP5, _saveReadIdxCPP5, VAL_CHECKP);
  for(uint8_t i = 0; i < VAL_CHECKP; i++){
    readCCheckpoint[0][i] = _saveActCPP1[i];  readCCheckpoint[1][i] = _saveActCPP2[i];
    timerACheckpoint[0][i] = _saveiDelayCPP1[i]; timerACheckpoint[1][i] = _saveiDelayCPP2[i];
    iDelayCheckpoint[0][i] = _savetimerACPP1[i];  iDelayCheckpoint[1][i] = _savetimerACPP2[i];
    readIdxCheckpoint[0][i] = _saveReadIdxCPP1[i];  readIdxCheckpoint[1][i] = _saveReadIdxCPP2[i];

    readCCheckpoint[2][i] = _saveActCPP3[i];  readCCheckpoint[3][i] = _saveActCPP4[i];
    timerACheckpoint[2][i] = _saveiDelayCPP3[i]; timerACheckpoint[3][i] = _saveiDelayCPP4[i];
    iDelayCheckpoint[2][i] = _savetimerACPP3[i];  iDelayCheckpoint[3][i] = _savetimerACPP4[i];
    readIdxCheckpoint[2][i] = _saveReadIdxCPP3[i];  readIdxCheckpoint[3][i] = _saveReadIdxCPP4[i];

    readCCheckpoint[4][i] = _saveActCPP5[i];
    timerACheckpoint[4][i] = _saveiDelayCPP5[i];
    iDelayCheckpoint[4][i] = _savetimerACPP5[i];
    readIdxCheckpoint[4][i] = _saveReadIdxCPP5[i];
  }
  delayMicroseconds(100);
}

void readPID(){
  Kp = memory.readFloat(addrKp);
  Ki = memory.readFloat(addrKi);
  Kd = memory.readFloat(addrKd);
//  if(Kp >= 255) Kp = 0;
//  else if (Kp < 0 ) Kp = 0;
//  if(Ki >= 255) Ki = 0;
//  else if (Ki < 0) Ki = 0;
//  if( Kd >= 255) Kd = 0;
//  else if (Kd < 0) Kd = 0;
}

void read_PID(){
  for(byte i = 0; i < 7; i++){
    _Kp[i] = memory.readFloat(addr_Kp(i));
    _Kd[i] = memory.readFloat(addr_Kd(i));
  }
}

void readHome() {
  memory.readByteArray(addrHome, _valDumpHome, 8);
  plan = _valDumpHome[0];
  normalSpeed = _valDumpHome[1];
  stopIndex = _valDumpHome[2];
}

void readCalib(){
  memory.readByteArray(addrCalibA, H, 14);
  memory.readByteArray(addrCalibB, L, 14);
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    CalAdc[i] = H[i]<<8 | (L[i] & 0x00ff);
  }
}

void readMaxMinSens(){
  memory.readByteArray(addrsetMaxSensH, MaxSensH, 14);
  memory.readByteArray(addrsetMaxSensL, MaxSensL, 14);
  memory.readByteArray(addrsetMinSensH, MinSensH, 14);
  memory.readByteArray(addrsetMinSensL, MinSensL, 14);
  for(uint8_t i = 0; i < MAXSENSOR; i++){
    setMaxVal[i] = MaxSensH[i] << 8 | (MaxSensL[i] & 0x00ff);
    setMinVal[i] = MinSensH[i] << 8 | (MinSensL[i] & 0x00ff);
  }
}
