const int butPin = 8;
const int redPin = 3;
const int yelPin = 4;
const int grePin = 5;
const int conPin = 13;
int state = 0;

void blinkLight(int pinNum, int timeDelay, int repeats){
  for(int i = 0; i<repeats; i++){
    digitalWrite(pinNum, HIGH);
    delay(timeDelay);
    digitalWrite(pinNum, LOW);
    delay(timeDelay);
  }
}

void red(){
  digitalWrite(redPin, HIGH);
  digitalWrite(yelPin, LOW);
  digitalWrite(grePin, LOW);
}

void red_yellow(){
  digitalWrite(redPin, HIGH);
  digitalWrite(yelPin, HIGH);
  digitalWrite(grePin, LOW);
}

void green(){
  digitalWrite(redPin, LOW);
  digitalWrite(yelPin, LOW);
  digitalWrite(grePin, HIGH);
}

void yellow(){
  blinkLight(grePin, 400, 3);
  digitalWrite(redPin, LOW);
  digitalWrite(yelPin, HIGH);
  digitalWrite(grePin, LOW);
}

void setup(){
  pinMode(butPin, INPUT_PULLUP);
  pinMode(conPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yelPin, OUTPUT);
  pinMode(grePin, OUTPUT);
  
  //Initial light is red
  digitalWrite(redPin, HIGH);
}

void loop(){
  int button = digitalRead(butPin);

  
  if(button == LOW){
    digitalWrite(conPin, HIGH);
    delay(500);
    digitalWrite(conPin, LOW);
    switch (state){
      case 0:
        red_yellow();
        state = 1;
        break;
      case 1:
        green();
        state = 2;
        break;
      case 2:
        yellow();
        state = 3;
        break;
      case 3:
        red();
        state = 0;
        break;
    }
  }
}
