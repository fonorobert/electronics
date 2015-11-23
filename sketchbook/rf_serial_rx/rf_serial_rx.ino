#include "VirtualWire.h"

int rx_pin = 2;


void setup(){
  vw_set_rx_pin(rx_pin);
  vw_setup(2000);
  vw_rx_start();
  Serial.begin(9600);
  Serial.println("Receiver module");
}

void loop(){

  uint8_t msg[VW_MAX_MESSAGE_LEN];
  uint8_t msglength = VW_MAX_MESSAGE_LEN;

  vw_wait_rx();
  if(vw_get_message(msg, &msglength)){
    Serial.print("Got: ");
    for (int i = 0; i < msglength; i++)
  	{
  	    Serial.print(char(msg[i]));
  	}
	   Serial.println();
  }
}
