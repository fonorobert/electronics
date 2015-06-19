#include "sevensegment.h"
#include "potmeter.h"

int pin_order[7] = {9,2,3,4,5,6,7};
int pot_pin = A0;
int scale[2] = {0,9};

void setup(){
  pinMode(12, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(12, LOW);
  int pot_value = potmeter(pot_pin, scale);
  writeDigit(pot_value, pin_order);
}
