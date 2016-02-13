#include <string.h>
const int readPin = A0;
const int baud = 6;
const int limit = 130;

//#define debug

void setup() {
  pinMode(readPin, INPUT);
  Serial.begin(9600);
}

char in;
int i, start, next;
int bits[12];
int check[4];
void loop() {
  in = 0;
  
  //wait for start bit
  while(analogRead(readPin) < limit) {}
  start = millis();
  next = start + (1.5 * baud);
  while(millis() < next) {}
  
  
  for(i = 0; i < 12; i++) {
    bits[i] = 0;
    if(analogRead(readPin) > limit) {
      bits[i] = 1;
      #ifdef debug
      Serial.print("1");
    } else {
      Serial.print("0");
      #endif
    }
    next = start + (baud * 1.5) + (baud * (i + 1));
    while(millis() < next) {};
  }
  
  //check for error
  check[0] = (bits[0] + bits[2] + bits[4] + bits[6] + bits[8] + bits[10]) % 2;
  check[1] = (bits[1] + bits[2] + bits[5] + bits[6] + bits[9] + bits[10]) % 2;
  check[2] = (bits[3] + bits[4] + bits[5] + bits[6] + bits[11]) % 2;
  check[3] = (bits[7] + bits[8] + bits[9] + bits[10] + bits[11]) % 2;
    
  i = ((check[0]) + (check[1] * 2) + (check[2] *4) + (check[3] * 8)) - 1;
  if(i != -1) {
    #ifdef debug
    Serial.print("flipping : ");
    Serial.print(i);
    #endif
    bits[i] = bits[i] == 1 ? 0 : 1;
  }
    
  //move bits from arrya to char
  #ifdef debug
  Serial.print("  in: ");
  #endif
  for(i = 0; i < 12; i++) {
    if(i == 0 || i == 1 || i == 3 || i == 7)
      continue;
    in = in << 1;
    if(bits[i] == 1) {
      in++;
      #ifdef debug
      Serial.print("1");
    } else {
      Serial.print("0");
      #endif
    }
  }

  #ifdef debug
  Serial.print("\ngot: ");
  #endif
  Serial.print(in);
  #ifdef debug
  Serial.println("");
  #endif
}
