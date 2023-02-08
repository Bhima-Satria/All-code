#include<Wire.h>
#include<Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

int a;
int b;
int c;
int d;
int e;

void setup(){
myservo1.attach(2); //rotator
myservo2.attach(3); //panjang
myservo3.attach(4); //mundur
myservo4.attach(5); //japit

 myservo1.write(90);
 myservo2.write(90);
 myservo3.write(90);
 myservo4.write(150);
 delay(3000);
}


void loop(){
  
kanan();
maju();
kiri();
mundur();
turun();
naik();
lepas();
japit();
 
}

void kanan(){
  for(a=0;a<=150;a++){
  myservo1.write(a);
  delay(50);
  }
  return;
}

void kiri(){
  for(a=150;a>=0;a--){
  myservo1.write(a);
  delay(50);
  }
  return;
}

void maju(){
  for(b=150;b>=50;b++){
  myservo3.write(b);
  delay(50);
  }
  return;
}

void mundur(){
  for(b=50;b<=150;b--){
  myservo3.write(b);
  delay(50);
  }
  return;
}

void turun(){
  for(c=50;c<=150;c--){
  myservo2.write(c);
  delay(50);
  }
  return;
}

void naik(){
  for(c=150;c>=50;c++){
  myservo2.write(c);
  delay(50);
  }
  return;
}


void japit(){
  for(e=100;e>=40;e--){
  myservo4.write(e);
  delay(50);
  }
  return;
}


void lepas(){
  for(e=40;e<=100;e++){
  myservo4.write(e);
  delay(50);
  }
  return;
}
