#include "VirtualWire.h"

int tx_pin = 2;
String input = "";
bool stringComplete = false;

void setup(){
  input.reserve(200);
  vw_set_tx_pin(tx_pin);
  vw_setup(2000);
  Serial.begin(9600);
  Serial.println("Transmitter module");
}

void loop(){

    if(stringComplete){
      char msg[input.length()];
      input.toCharArray(msg, input.length());
      Serial.print(sizeof(msg));
      vw_send((uint8_t *)msg, sizeof(msg));
      vw_wait_tx();
      Serial.print("Sent: ");
      Serial.print(msg);
      Serial.println();
      input = "";
      stringComplete = false;
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    input += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '/n') {
      stringComplete = true;
    }
  }
}
