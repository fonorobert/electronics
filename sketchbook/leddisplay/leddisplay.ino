int current_num = 0;
//pin order: 9,2,3,4,5,6,7
//dot: 8
int seven_seg_digits[10][7]{
  {1,0,1,1,1,1,1},
  {0,0,0,1,0,0,1},
  {0,1,1,1,1,1,0},
  {0,1,1,1,0,1,1},
  {1,1,0,1,0,0,1},
  {1,1,1,0,0,1,1},
  {1,1,1,0,1,1,1},
  {0,0,1,1,0,0,1},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};
int pin_order[7] = {9,2,3,4,5,6,7};

void writeDigit(int digit){
  for(int segment = 0; segment<7; segment++){
    digitalWrite(pin_order[segment], seven_seg_digits[digit][segment]);
  }
}

void writeDot(int dot){
  digitalWrite(8, dot);
}

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
  Serial.begin(9600);
  delay(50);
}

void loop(){
  int button = digitalRead(12);
  if(button == LOW && current_num<10){
    Serial.println(current_num);
    writeDigit(current_num);
    current_num++;
    delay(200);
  }
  else if(current_num>=10){
    current_num=0; 
  }
}
