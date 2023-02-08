#include <PString.h>
#include <OneWire.h>

char buffer[30];
OneWire ds(18);
int relay1=2;
int relay2=3;
int relay3=4;
int relay4=5;
int sr1=14;
int sr2=15;
int pir=16;
boolean s1,s2,s3,ls3=false;

void setup() {
  delay(3000);
  pinMode(sr1,INPUT_PULLUP);
  pinMode(sr2,INPUT_PULLUP);
  pinMode(pir,INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  Serial.begin(9600);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
}

void loop() {
  PString str(buffer, sizeof(buffer));
  str.begin();
  float temperature = getTemp();
  str.print("#");
  str.print(temperature,1);
  str.print("+");
  
  baca();
  str.print(s1);
  str.print("+");
  str.print(s2);
  str.print("+");
  str.print(s3);
  str.print("+");
  Serial.println(str);
 
if(Serial.available()>0){
  char in=Serial.read();
  if(in=='a'){
    digitalWrite(relay1,LOW);
  }
  if(in=='b'){
    digitalWrite(relay1,HIGH);
  }
  if(in=='c'){
    digitalWrite(relay2,LOW);
  }
  if(in=='d'){
    digitalWrite(relay2,HIGH);
  }
   if(in=='e'){
    digitalWrite(relay3,LOW);
  }
  if(in=='f'){
    digitalWrite(relay3,HIGH);
  }
   if(in=='g'){
    digitalWrite(relay4,LOW);
  }
  if(in=='h'){
    digitalWrite(relay4,HIGH);
  }
}
delay(100);
}

void baca(){
  s1=digitalRead(sr1);
  s2=digitalRead(sr2);
  s3=digitalRead(pir);
}

float getTemp(){
 
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
   
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); 
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); 

  
  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); 
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}

