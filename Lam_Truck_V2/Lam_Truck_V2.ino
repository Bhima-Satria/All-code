//register A
int LatchA= 2;  
int ClkA  = 3; 
int SerA  = 4;  

byte ledA = 0; 

//register B
int LatchB= 5;  
int ClkB  = 6; 
int SerB  = 7;  

byte ledB = 0;   

int Rem    = 8;
int Hazard = 9;
int Kanan  = 10;
int Kiri   = 11;
int Kota   = 12;
int Mundur = 13;

void setup() 
{
  pinMode(LatchA, OUTPUT);
  pinMode(ClkA, OUTPUT);  
  pinMode(SerA, OUTPUT);

  pinMode(LatchB, OUTPUT);
  pinMode(ClkB, OUTPUT);  
  pinMode(SerB, OUTPUT);

  pinMode(Rem, INPUT);

  Serial.begin(9600);
}

void loop() 
{
  ledA = 0; 
  updateShiftRegister();
  delay(500);
if (digitalRead(Rem) == HIGH) {
/*  for (int i = 8; i >= 0; i--) 
  {
    bitSet(ledA, i);
    Serial.print(i);
    updateShiftRegister();
    delay(100);
  } */

  bitSet(ledA, 0);
  updateShiftRegister();
  delay(100);  
  bitSet(ledA, 1);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 2);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 3);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 4);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 5);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 6);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 7);
  updateShiftRegister();
  delay(100);

  
} else {

  bitSet(ledA, 1);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 3);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 5);
  updateShiftRegister();
  delay(100);
  bitSet(ledA, 7);
  updateShiftRegister();
  delay(100);
}

}

void updateShiftRegister()
{
   digitalWrite(LatchA, LOW);
   shiftOut(SerA, ClkA, LSBFIRST, ledA);
   digitalWrite(LatchA, HIGH);
   
}
