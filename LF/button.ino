#define LONG_TIME_PRESS 1000
bool currentStatePress;
bool lastStatePress = false;
unsigned long pressTime;
unsigned long releaseTime;

void initButton() {
  pcf.begin(PCF8574_ADDR, &Wire);
  pcf.pinMode(0, INPUT_PULLUP);
  pcf.pinMode(1, INPUT_PULLUP);
  pcf.pinMode(2, INPUT_PULLUP);
  pcf.pinMode(3, INPUT_PULLUP);
  pcf.pinMode(4, INPUT_PULLUP);
  pcf.pinMode(5, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

bool _readButton(int channel)
{
  uint8_t val = pcf.digitalRead(channel);
  return val;
  delay(10);
}

bool touchUp(int button) {
  if (!_readButton(button)) {
    while (!_readButton(button)) {}
     return true;
  }
  return false;
}


bool touchDown(int button , int del) {
  bool val ;
  if (!_readButton(button)){
    while (_readButton(button))
     val = true;
     delay(del);
     del -=5;
  }else val = false;
  
  return val ;
}

// // PR press up
// bool pressUp (int button){
//   lastStatePress =  currentStatePress;
//   currentStatePress = touchDown(button);
//   if(lastStatePress == false && currentStatePress == true) pressTime = millis();
//   else if(lastStatePress == true && currentStatePress == false) releaseTime = millis();

//   long rangeTime = releaseTime - pressTime;
//   if(rangeTime > LONG_TIME_PRESS){
//     return true;
//   }
//   lastStatePress = currentStatePress;
//   return false;
// }
