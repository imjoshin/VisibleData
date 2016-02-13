const int ledPin =  13; 
const int baud = 10;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
}

char in;
int i;
void loop() {
  if(Serial.available() > 0) {
    in = Serial.read();
    Serial.print(in);
    digitalWrite(ledPin, HIGH);
    delay(baud);
    for(i = 0; i < 8; i++) {
      if((int)in < 0) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
      delay(baud);
      in = in << 1;
    }
    digitalWrite(ledPin, LOW);
    delay(baud);
  }
}
