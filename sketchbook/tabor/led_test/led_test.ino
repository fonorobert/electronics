#include "VirtualWire.h"

int rx_pin = 2;

int led[9] = {4,5,6,7,8,9,10,11,12};
int step = 0;


void setup(){
  for (int i = 0; i<sizeof(led)/sizeof(led[0]); i++){
    pinMode(led[i], OUTPUT);
  }
}

void loop(){
  delay(500);
  for(int j = 0; j<sizeof(led)/sizeof(led[0]); j++){
    digitalWrite(led[j], LOW);
  }
  digitalWrite(led[step], HIGH);
  if(step == 8) {
    step = 0;
  } else {
    step += 1;
  }
}
