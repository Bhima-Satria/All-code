int SerA = 2;
int SerB = 3;
int SerC = 4;

int ClkA = 5;
int ClkB = 6;
int ClkC = 7;

int Rem     = 8;
int Hazard  = 9;
int Kiri    = 10;
int Kanan   = 11;
int Kota    = 12;
int Mndr    = 13;

void setup() {
  
  pinMode (SerA, OUTPUT);
  pinMode (SerB, OUTPUT);
  pinMode (SerC, OUTPUT);

  pinMode (ClkA, OUTPUT);
  pinMode (ClkB, OUTPUT);
  pinMode (ClkC, OUTPUT);

  pinMode (Rem,   INPUT_PULLUP);
  pinMode (Hazard,INPUT);
  pinMode (Kiri,  INPUT);
  pinMode (Kanan, INPUT);
  pinMode (Kota,  INPUT);
  pinMode (Mndr,  INPUT);

}

void loop() {
 if (digitalRead(Kota) == HIGH) {
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
 }

 else if (digitalRead(Rem) == HIGH) {
//Masukan (Data)
  digitalWrite (SerA, HIGH);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (SerA, LOW);
  delay(100);
  
//Luaran
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(100);
 }

 else if (digitalRead(Hazard) == HIGH){
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);  
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, HIGH);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(250);
    digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  delay(250);
 } else 
    digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
  digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
   digitalWrite (SerA, LOW);
  digitalWrite (ClkA, HIGH);
  digitalWrite (ClkA, LOW);
 
}
