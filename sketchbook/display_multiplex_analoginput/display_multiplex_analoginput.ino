#include "sevensegment.h"
#include "analogmeter.h"
#include "button.h"

int pin_order[7] = {9,2,3,4,5,6,7};
//A,B,C,D,E,F,G

int pot_pin = A0;
int light_pin = A1;
int ground[2] = {11, 12};
int button_pin = 0;

int scale[2] = {0,99};
int timer = 10;
int display_metric = 0;
int value;

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
  pinMode(button_pin, INPUT_PULLUP);
}

void loop(){
  display_metric = button(display_metric, button_pin, pin_order, ground);
  switch (display_metric){
    case 0:
      value = analogmeter(pot_pin, scale);
      break;
    case 1:
      value = analogmeter(light_pin, scale);
      break;
  }
  writeNumber(value, pin_order, ground, timer);
}
