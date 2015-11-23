#include "VirtualWire.h"

int rx_pin = 12;

int heat[3] = {2,3,4};
int wind[3] = {5,6,7};
int humi[3] = {8,9,10};




void setup(){
  for (int i = 2; i<11; i++){
    pinMode(i, OUTPUT);
  }
  vw_set_rx_pin(rx_pin);
  vw_setup(2000);
  vw_rx_start();
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
