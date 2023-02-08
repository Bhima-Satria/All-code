#include<AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(4);
int DS1 = 2;
int DS2 = 3;
int DS3 = 4;
int DS4 = 5;
int DS5 = 6;
int DS6 = 7;
int DS7 = 8;
int DS8 = 9;

void setup()
{
 Serial.begin(9600);
 motor1.setSpeed(200);
 motor2.setSpeed(200);
 pinMode(DS1,INPUT);
 pinMode(DS2,INPUT);
 pinMode(DS3,INPUT);
 pinMode(DS4,INPUT);
 pinMode(DS5,INPUT);
 pinMode(DS6,INPUT);
 pinMode(DS7,INPUT);
 pinMode(DS8,INPUT);
 motor1.run(RELEASE);
 motor2.run(RELEASE);
}
void loop()
{
 uint8_t mx = 255;
 uint8_t tmax = 191;
 uint8_t hmax = 127;
 uint8_t omax = 64;
 uint8_t lw = 0;
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

 if( S1 == 1 && S2 == 1 && S3 == 1 && S4 == 0 && S5 == 0 && S6 == 1 && S7 == 1 && S8 == 1 ) //Centre
   {
     motor1.run(FORWARD);
     motor1.setSpeed(mx);
     motor2.run(FORWARD);
     motor2.setSpeed(mx);
   }
 else if( S1 == 1 && S2 == 1 && S3 == 0 && S4 == 0 && S5 == 1 && S6 == 1 && S7 == 1 && S8 == 1 ) //75 Left
   {
     motor1.run(FORWARD);
     motor1.setSpeed(tmax);
     motor2.run(FORWARD);
     motor2.setSpeed(mx);
   }
 else if( S1 == 1 && S2 == 0 && S3 == 0 && S4 == 1 && S5 == 1 && S6 == 1 && S7 == 1 && S8 == 1 ) //50 Left
   {
     motor1.run(FORWARD);
     motor1.setSpeed(hmax);
     motor2.run(FORWARD);
     motor2.setSpeed(mx);
   }
 else if( S1 == 0 && S2 == 0 && S3 == 1 && S4 == 1 && S5 == 1 && S6 == 1 && S7 == 1 && S8 == 1 ) //25 Left
   {
     motor1.run(FORWARD);
     motor1.setSpeed(omax);
     motor2.run(FORWARD);
     motor2.setSpeed(mx);
   }
 else if( S1 == 0 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1 && S6 == 1 && S7 == 1 && S8 == 1 ) //0 Left
   {
     motor1.run(FORWARD);
     motor1.setSpeed(lw);
     motor2.run(FORWARD);
     motor2.setSpeed(mx);
   }
 else if( S1 == 0 && S2 == 0 && S3 == 0 && S4 == 0 && S5 == 0 && S6 == 1 && S7 == 1 && S8 == 1) //Left L
   {
     motor1.run(FORWARD);
     motor1.setSpeed(lw);
     motor2.run(FORWARD);
     motor2.setSpeed(mx);
   }
 else if( S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 0 && S6 == 0 && S7 == 1 && S8 == 1 ) //75 Right
   {
     motor1.run(FORWARD);
     motor1.setSpeed(mx);
     motor2.run(FORWARD);
     motor2.setSpeed(tmax);
   }
 else if( S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1 && S6 == 0 && S7 == 0 && S8 == 1 ) //50 Right
   {
     motor1.run(FORWARD);
     motor1.setSpeed(mx);
     motor2.run(FORWARD);
     motor2.setSpeed(hmax);
   }
 else if( S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1 && S6 == 1 && S7 == 0 && S8 == 0 ) //25 Right
   {
     motor1.run(FORWARD);
     motor1.setSpeed(mx);
     motor2.run(FORWARD);
     motor2.setSpeed(omax);
   } 
 else if( S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1 && S6 == 1 && S7 == 1 && S8 == 0 ) //0 Right
   {
     motor1.run(FORWARD);
     motor1.setSpeed(mx);
     motor2.run(FORWARD);
     motor2.setSpeed(lw);
   }
 else if( S1 == 0 && S2 == 0 && S3 == 0 && S4 == 0 && S5 == 0 && S6 == 1 && S7 == 1 && S8 == 1) //Right L
   {
     motor1.run(FORWARD);
     motor1.setSpeed(mx);
     motor2.run(FORWARD);
     motor2.setSpeed(lw);
   }
 else if( S1 == 1 && S2 == 1 && S3 == 1 && S4 == 1 && S5 == 1 && S6 == 1 && S7 == 1 && S8 == 1 ) //All White
   {
     motor1.run(FORWARD);
     motor1.setSpeed(tmax);
     motor2.run(FORWARD);
     motor2.setSpeed(tmax);
   }
 else if( S1 == 0 && S2 == 0 && S3 == 0 && S4 == 0 && S5 == 0 && S6 == 0 && S7 == 0 && S8 == 0 ) //All Black
   {
     motor1.run(FORWARD);
     motor1.setSpeed(tmax);
     motor2.run(FORWARD);
     motor2.setSpeed(tmax);
   }
 else
   {
     motor1.run(FORWARD);
     motor1.setSpeed(tmax);
     motor2.run(FORWARD);
     motor2.setSpeed(tmax);
   }
}
