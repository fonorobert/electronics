#include "sevensegment.h"

int pin_order[7] = {9,2,3,4,5,6,7};
//A,B,C,D,E,F,G

int ground[2] = {11, 12};

int scale[2] = {0,99};
int timer = 50;
int value = 100;

void setup(){
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop(){
  value-= 1;
  writeNumber(value, pin_order, ground, timer);
}
