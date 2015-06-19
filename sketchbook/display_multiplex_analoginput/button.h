#include "Arduino.h"

int button(int display_metric, int pin, int pin_order[7], int ground[2]){
  int button_state = digitalRead(pin);
  if(button_state == LOW){
    writeNumber(100, pin_order, ground, 50);
    switch(display_metric){
      case 0:
        return 1;
        break;
      case 1:
        return 0;
        break;
    }
  }
  else {
    return display_metric;
  }
}
