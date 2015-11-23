#include "VirtualWire.h"
#include "rfarraytoint.h"

int pinTemp[3] = {4, 5, 6};
int pinHum[3] = {7, 8, 9};
int pinWind = 10;

static uint8_t vw_rx_pin = 2;

volatile int ctrlValue = 0;
char * ctrlReading;

volatile int temp = 0;
volatile int hum = 0;


void setup(){
  Serial.begin(9600);
  Serial.println("Weather display with LEDs");

  for(int t=0; t<sizeof(pinTemp); t++){
    pinMode(pinTemp[t], OUTPUT);
  }

  for(int h=0; h<sizeof(pinHum); h++){
    pinMode(pinHum[h], OUTPUT);
  }

  pinMode(pinWind, OUTPUT);

  digitalWrite(pinWind, HIGH);

  vw_set_rx_pin(vw_rx_pin);
  vw_setup(1000);
  vw_rx_start();

  attachInterrupt(0, updateValues, RISING);
}

void loop(){
  switch(temp){
    case 0:
      digitalWrite(pinTemp[0], HIGH);
      digitalWrite(pinTemp[1], LOW);
      digitalWrite(pinTemp[2], LOW);
      break;
    case 1:
      digitalWrite(pinTemp[0], HIGH);
      digitalWrite(pinTemp[1], HIGH);
      digitalWrite(pinTemp[2], LOW);
      break;
    case 2:
      digitalWrite(pinTemp[0], HIGH);
      digitalWrite(pinTemp[1], HIGH);
      digitalWrite(pinTemp[2], HIGH);
      break;
  }

  switch(hum){
    case 0:
      digitalWrite(pinHum[0], HIGH);
      digitalWrite(pinHum[1], LOW);
      digitalWrite(pinHum[2], LOW);
      break;
    case 1:
      digitalWrite(pinHum[0], LOW);
      digitalWrite(pinHum[1], HIGH);
      digitalWrite(pinHum[2], LOW);
      break;
    case 2:
      digitalWrite(pinHum[0], LOW);
      digitalWrite(pinHum[1], LOW);
      digitalWrite(pinHum[2], HIGH);
      break;
  }

}

void updateValues(){
  uint8_t msg[VW_MAX_MESSAGE_LEN];
  uint8_t msglength = VW_MAX_MESSAGE_LEN;

  if(vw_get_message(msg, &msglength)){

    int value = rfArrToInt(msg, msglength);

    if (value < 200) {
      value -= 100;
      if(value < 20) {
        temp = 0;
      } else if (value < 26) {
        temp = 1;
      } else if (value >= 26) {
        temp = 2;
      }
    } else if(value < 300 && value >= 200) {
        value -= 200;
        if (value < 22){
          hum = 0;
        } else if (value < 30) {
          hum = 1;
        } else if (value >= 31) {
          hum = 2;
        }
    }
  }
}
