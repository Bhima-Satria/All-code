#include <Servo.h>

Servo servo1, servo2, servo3;

#define pin_servo1 6
#define pin_servo2 7
#define pin_servo3 8

String inputString = "";
int xx;
int yy;
int zz;

void setup(){
  Serial.begin(9600);
  servo1.attach(pin_servo1, 612, 2480);
  servo2.attach(pin_servo2, 1000, 2680);
  servo3.attach(pin_servo3, 600, 2000);
}

void inverse_kinematik(long x, long y, long z){

const long L1 = 12; //cm, Sesuaikan dg panjang L1 trainer
const long L2 = 9; //cm, Sesuaikan dg panjang L2 trainer

float sdt_1, sdt_2, sdt_3, sdt_2a, sdt_2b;
long AC, AD, a, b, c, ab, bc;

//Panjang Sisi Miring AC
AD = sqrt(sq(x) + sq(y)); //satuan panjang
AC = sqrt(sq(AD)+sq(z)); //satuan panjang

//Sudut 1
sdt_1 = atan2(y,x)*RAD_TO_DEG; //iku wes dadi sudut titik tumpu e

// Sudut 2
a = (z/AD);//
b = sq(L1)+sq(AC)-sq(L2);
c =  2*L1*AC;
sdt_2a= atan((float)a)*RAD_TO_DEG;
sdt_2b= acos((float)b/(float)c)*RAD_TO_DEG;
sdt_2 = sdt_2a+sdt_2b;

//Sudut 3
ab = sq(L1)+sq(L2)-sq(AC);
bc = 2*L1*L2;
sdt_3 = acos((float)ab/(float)bc)*RAD_TO_DEG;

Serial.print("q1 = "); Serial.println((int)sdt_1);
Serial.print("q2 = "); Serial.println((int)sdt_2);
Serial.print("q3 = "); Serial.println((int)sdt_3);// iki mbuh bener ta gak

servo1.write((int) sdt_1);
servo2.write((int) sdt_2);
servo3.write((int) sdt_3);

}

void loop() {
  if (Serial.available() >= 0 )
  {
    String str=Serial.readStringUntil('x');
    unsigned int a = Serial.parseInt();
    String str1=Serial.readStringUntil('y');
    unsigned int b = Serial.parseInt();
    String str2=Serial.readStringUntil('z');
    unsigned int c = Serial.parseInt();
    unsigned int xx = a;
    unsigned int yy = b;
    unsigned int z = c;
    
    inverse_kinematik(xx , yy, zz);
    }
    }
