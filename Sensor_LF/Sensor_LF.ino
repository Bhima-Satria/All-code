
int DS1 = 2;
int DS2 = 3;
int DS3 = 4;
int DS4 = 5;
int DS5 = 6;
int DS6 = 7;
int DS7 = 8;
int DS8 = 9;

int kiri1=10;
int kiri2=11;
int kanan1=12;
int kanan2=13;

void setup() {
  
 pinMode(DS1,INPUT);
 pinMode(DS2,INPUT);
 pinMode(DS3,INPUT);
 pinMode(DS4,INPUT);
 pinMode(DS5,INPUT);
 pinMode(DS6,INPUT);
 pinMode(DS7,INPUT);
 pinMode(DS8,INPUT);
 Serial.begin(9600);
  pinMode(kiri1, OUTPUT);
  pinMode(kiri2, OUTPUT);
  pinMode(kanan1, OUTPUT);
  pinMode(kanan2, OUTPUT);
  
}

void loop() {
  int S1 = digitalRead(DS1);
 int S2 = digitalRead(DS2);
 int S3 = digitalRead(DS3);
 int S4 = digitalRead(DS4);
 int S5 = digitalRead(DS5);
 int S6 = digitalRead(DS6);
 int S7 = digitalRead(DS7);
 int S8 = digitalRead(DS8);
 Serial.print(S1);
 Serial.print(S2);
 Serial.print(S3);
 Serial.print(S4);
 Serial.print(S5);
 Serial.print(S6);
 Serial.print(S7);
 Serial.print(S8);
 Serial.print("\n");
}
