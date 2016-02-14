const int ledPin =  13; 
const int baud = 6;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
  digitalWrite(ledPin, HIGH);
}

char in;
int i;
unsigned long next;
unsigned long start;
int bits[12];

void loop() {
}
