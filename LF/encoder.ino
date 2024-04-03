/*
       /  \
      /    \
     /      \
   A -------- B

*/

void readENC_A() {
  if (digitalRead(ENC1B) > 0) {
    countEnc_A++;
    pulseL++;
  } else {
    countEnc_A--;
    pulseL--;
  }
}

void readENC_B() {
  if (digitalRead(ENC2B) > 0) {
    countEnc_B++;
    pulseR++;
  } else {
    countEnc_B--;
    pulseR--;
  }
}

void initEncoder(bool state) {
  if (state) {
    attachInterrupt(digitalPinToInterrupt(ENC1A), readENC_A, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC2A), readENC_B, RISING);
  } else {
    detachInterrupt(digitalPinToInterrupt(ENC1A));
    detachInterrupt(digitalPinToInterrupt(ENC2A));
  }
}

int measureLengthR(){
  int measure = countEnc_B * factor * (-1);
  if(measure < 0 ){
    countEnc_B = 0;
    return 0 ;
  } else {
    return measure;
  }
}

int measureLengthL(){
  int measure = countEnc_A * factor;
  if(measure < 0 ){
    countEnc_A = 0;
    return 0 ;
  } else {
    return measure;
  }
}
