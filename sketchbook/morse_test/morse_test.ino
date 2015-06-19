void blinkalot(int led){
  for (int i=0; i<9; i++){
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
  delay(950);
}

void blinkone(int led){
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(1000);
}

void morseBlink(const char * sig, int pin, int unit){
  char dot = '.';
  char dash = '-';
  for (int i=0; i<strlen(sig); i++){
    if (sig[i]==dot){
      digitalWrite(pin, HIGH);
      delay(unit);
      digitalWrite(pin, LOW);
      delay(unit);
    }
    if (sig[i]==dash){
      digitalWrite(pin, HIGH);
      delay(unit*3);
      digitalWrite(pin, LOW);
      delay(unit);
    }
  }
}

void morse(const char * a[], int pin, int unit){
  blinkalot(pin);
  
  const char * abc[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
  const char * morsetable[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

  const char * input = a[0];
  for (int i=0; i<strlen(input); i++){
    //if the character is a space, wait, then go to the next character
    if(input[i]==' '){
      delay(unit*7);
      continue;
    }
    for (int j=0; j<sizeof(abc)/sizeof(abc[0]); j++){
      if (input[i]==abc[j][0]){
        morseBlink(morsetable[j], pin, unit);
      }
    }
    delay(unit*3);
  }
  
}
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

//unit will be the length of a dot. all lengths (dashes, pauses) are calculated from this.
int unit = 200;

//input is the string of characters that will be translated to morse code
const char * input[] = {"cq cq cq de frs ar"};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  morse(input, led, unit);
}
