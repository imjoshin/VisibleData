const int ledPin =  13; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
}

char in;
int i;
void loop() {
  if(Serial.available() > 0) {
    Serial.println("in if");
    in = Serial.read();
    Serial.print("read: ");
    Serial.println(in);
    digitalWrite(ledPin, HIGH);
    delay(2000);
    for(i = 0; i < 8; i++) {
      if((int)in < 0) {
        Serial.println("one");
        digitalWrite(ledPin, HIGH);
      } else {
        Serial.println("zero");
        digitalWrite(ledPin, LOW);
      }
      delay(500);
      in = in << 1;
    }
    digitalWrite(ledPin, LOW);
    delay(2000);
  }  
}
