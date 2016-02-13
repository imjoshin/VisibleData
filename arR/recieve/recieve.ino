const int readPin = A0;
const int baud = 10;
const int limit = 130;

//#define debug

void setup() {
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

char in;
int i;
void loop() {
  in = 0;
  while(analogRead(readPin) < limit) {}
  //Serial.println(analogRead(readPin));
  delay(baud + (.5 * baud));
  for(i = 0; i < 8; i++) {
    in = in << 1;
    if(analogRead(readPin) > limit) {
      in++;
      #ifdef debug
      Serial.print("1");
    } else {
      Serial.print("0");
      #endif
    }
    delay(baud);
  }
  #ifdef debug
  Serial.print("\ngot: ");
  #endif
  Serial.print(in);
  #ifdef debug
  Serial.println("");
  #endif
}
