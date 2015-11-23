#include "VirtualWire.h"

int tx_pin = 2;
static uint8_t vw_tx_pin = 2;
int butPin = 4;
int ledPin = 13;

void setup(){
  pinMode(butPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  vw_set_tx_pin(vw_tx_pin);
  vw_setup(1000);
}

void loop(){
    int button = digitalRead(butPin);

    if(button == LOW){
      char msg[] = "128";
      vw_send((uint8_t *)msg, sizeof(msg)/sizeof(msg[0]));
      vw_wait_tx();

      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(10);
    }

    /*vw_send((uint8_t *)"H30", 3);
    vw_wait_tx();
    delay(2000);*/
}
