const int ledPin =  13; 
const int baud = 4;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
}

char in;
int i;
unsigned long next;
unsigned long start;
int bits[12];

void loop() {
  if(Serial.available() > 0) {
    //read char to send
    in = Serial.read();
    Serial.print(in);
    
    
    //create hamming code
    bits[11] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[10] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[9] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[8] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[6] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[5] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[4] = in < 0 ? 1 : 0;
    in = in << 1;
    bits[2] = in < 0 ? 1 : 0;
    in = in << 1;
    
    
    Serial.print(bits[2]);
    Serial.print(bits[4]);
    Serial.print(bits[5]);
    Serial.print(bits[6]);
    Serial.print(bits[8]);
    Serial.print(bits[9]);
    Serial.print(bits[10]);
    Serial.println(bits[11]);
    
    bits[0] = (bits[2] + bits[4] + bits[6] + bits[8] + bits[10]) % 2;
    bits[1] = (bits[2] + bits[5] + bits[6] + bits[9] + bits[10]) % 2;
    bits[3] = (bits[3] + bits[4] + bits[5] + bits[6] + bits[11]) % 2;
    bits[7] = (bits[7] + bits[8] + bits[9] + bits[10] + bits[11]) % 2;
    
    Serial.print(bits[0]);
    Serial.print(bits[1]);
    Serial.print(bits[2]);
    Serial.print(bits[3]);
    Serial.print(bits[4]);
    Serial.print(bits[5]);
    Serial.print(bits[6]);
    Serial.print(bits[7]);
    Serial.print(bits[8]);
    Serial.print(bits[9]);
    Serial.print(bits[10]);
    Serial.println(bits[11]);
    //start bit
    start = millis();
    digitalWrite(ledPin, HIGH);
    next = start + baud;
    while(millis() < next) {}
    
    //send 8 bits of the char
    for(i = 0; i < 12; i++) {
      if(bits[i]) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
      
      //stay on the same bit 
      next = start + baud + (baud * (i + 1));
      while(millis() < next) {};
      
      //get the next bit ready
      in = in << 1;
    }
    
    //TODO: write parody bits
    
    
    //stop bit
    digitalWrite(ledPin, LOW);
    delay(baud * 2);
  }
}
