#include "VirtualWire.h"
#include "rfarraytoint.h"

int rx_pin = 2;
static uint8_t vw_rx_pin = 2;

int ledOne = 10;
/*int ledTwo = 9;
int ledThr = 10;*/


void setup(){
  vw_set_rx_pin(vw_rx_pin);
  vw_setup(1000);
  vw_rx_start();
  pinMode(ledOne, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, printToSerial, RISING);
  /*pinMode(ledTwo, OUTPUT);
  pinMode(ledThr, OUTPUT);*/
}

void loop(){
  digitalWrite(ledOne, LOW);
  delay(2000);
  digitalWrite(ledOne, HIGH);
  delay(2000);
}

void printToSerial(){
  uint8_t msg[VW_MAX_MESSAGE_LEN];
  uint8_t msglength = VW_MAX_MESSAGE_LEN;

  if(vw_get_message(msg, &msglength)){
    int value = rfArrToInt(msg, msglength);
    Serial.println(value + 1);

    if (value < 200) {
      value -= 100;
      if(value < 17) {
        Serial.println(0);
      } else if (value < 20) {
        Serial.println(1);
      } else if (value < 24) {
        Serial.println(2);
      } else if (value < 29) {
        Serial.println(3);
      } else if (value >= 29) {
        Serial.println(4);
      }
    }
  }
}
