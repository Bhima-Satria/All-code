#include <Servo.h>

Servo myservo;

int i=0;
void setup() {
  myservo.attach(9);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, INPUT);

}

void loop() {

int IR = digitalRead(12);

 if(IR == HIGH){
  for(i=0; i<=9; i+=1){
  digitalWrite(i, HIGH);
  delay(15);
  digitalWrite(i, LOW);
  delay(15);
  }
  for(i=9; i>=0; i-=1){
  digitalWrite(i, HIGH);
  delay(15);
  digitalWrite(i, LOW);
  delay(15);  
  } 
  myservo.write(180);
  delay(15);
 }
 else {
 
 digitalWrite(8, HIGH);
 digitalWrite(6, HIGH);
 digitalWrite(4, HIGH);
 digitalWrite(2, HIGH);
  myservo.write(0);
  delay(15);
 }
}
