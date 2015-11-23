int state = 0;
int pins[9] = {4,5,6,7,8,9,10,11,12};

void setLed(){
  for (int i = 0; i<sizeof(pins)/sizeof(pins[0]); i++) {
    digitalWrite(pins[i], LOW);
  }
  digitalWrite(pins[state], HIGH);
  delay(200);
}

void setup(){
  for(int j = 0; j<sizeof(pins)/sizeof(pins[0]); j++) {
    pinMode(pins[j], OUTPUT);
  }
}

void loop(){
  if(state >= sizeof(pins)/sizeof(pins[0])){
    state = 0;
  }
  setLed();
  state++;

}
