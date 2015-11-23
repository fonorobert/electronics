const int butPin = 2;
const int redPin = 4;
const int yelPin = 5;
int state = 0;

void red(){
  digitalWrite(redPin, HIGH);
  digitalWrite(yelPin, LOW);
  delay(500);
}

void yellow(){
  digitalWrite(redPin, LOW);
  digitalWrite(yelPin, HIGH);
  delay(500);
}

void setup(){
  pinMode(butPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(yelPin, OUTPUT);

  //Initial light is red
  digitalWrite(redPin, HIGH);
}

void loop(){
  int button = digitalRead(butPin);


  if(button == LOW){
    switch (state){
      case 0:
        yellow();
        state = 1;
        break;
      case 1:
        red();
        state = 0;
        break;
    }
  }

}
