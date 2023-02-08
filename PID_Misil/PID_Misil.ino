/*
      ARDUINO HOCAM GIMBAL YAPIMI

*/
#include <Servo.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h> // MPU6050 using I2C protocol ,thats why we need to use these libraries.

String inString = "";
String degrex = "90";
String degrey = "90";
String degrez = "90";

MPU6050 ACC_GYR; // Creating MPU6050 object and giving a name.
MPU6050 ACC_GYR2(0x69); // Creating MPU6050 object and giving a name.

int error1, error2, lasterror1, lasterror2, outx, outz;
float kp=0.3, kd=0.3;

Servo servo1;
Servo servo2; // Servo objects.

Servo servo3;
Servo servo4; // Servo objects.

//Create 16 bit variables. the reason is data which is coming from sensor has 16bit information.
int16_t accx, accy, accz;
int16_t gyrx, gyry, gyrz;

int16_t accx2, accy2, accz2;
int16_t gyrx2, gyry2, gyrz2;

int deger, deger2, eskideger, eskideger2, x, y; // create variable. Here x and y are used for my personal stabilization. You don't have to use them.

int deger_2, deger2_2;

int degre3=90;
int degre4=90;

void setup()
{
//  pinMode(6, OUTPUT);
//  analogWrite(6, 180);
  Serial.begin(9600);
  Serial.println("ARDUINO HOCAM GIMBALL YAPIMI");
  Serial.println("www.youtube.com/ArduinoHocam ");
  
  ACC_GYR.initialize();
  ACC_GYR2.initialize();// Sensor initialize
  
  Serial.println(ACC_GYR.testConnection() ? "BAĞLANDI" : "BAĞLANAMADI!!!"); //connection test
  Serial.println(ACC_GYR2.testConnection() ? "BAĞLANDI" : "BAĞLANAMADI!!!"); //connection test

  
  
  servo1.attach(11);
  servo2.attach(10); //servo pins
  servo1.write(90);
  servo2.write(90); // 90 DERECE KONUMUNA GETIR.

  servo3.attach(3);
  servo4.attach(9); //servo pins
  servo3.write(90);
  servo4.write(90); // 90 DERECE KONUMUNA GETIR.
  delay(50);
  
}

void loop()
{
//mengambil nilai dari sensor Mpu6050
  ACC_GYR.getMotion6(&accx, &accy, &accz, &gyrx, &gyry, &gyrz); // dalatarı çekiyoruz sensörde
  ACC_GYR2.getMotion6(&accx2, &accy2, &accz2, &gyrx2, &gyry2, &gyrz2);
  
  deger = map(accx, -16000, 17000, 0, 180);  // change x axis boundries
//  deger = accx;
  deger2 = map(accy, -16000, 17000, 0, 180); //change yaxis boundries
//  deger2 = accy;

//  deger_2 = map(accx2, -17000, 17000, 0, 180);  // change x axis boundries
//  deger2_2 = map(accy2, -17000, 17000, 0, 180); //change yaxis boundries



//Membaca input dari serial
  while (Serial.available() > 0)
  {
    inString = Serial.readString();
    Serial.println(inString);

    int posisix = inString.indexOf('x');
    degrex = inString.substring(0, posisix);

    int posisiy = inString.indexOf('y');
    degrey = inString.substring(posisix + 1, posisiy);

    int posisiz = inString.indexOf('z');
    degrez = inString.substring(posisiy + 1, posisiz);
  }

//  Serial.print("Kordinat x : ");
//  Serial.println(degrex);
//  Serial.print("Kordinat y : ");
//  Serial.println(degrey);
//  Serial.print("Kordinat z : ");
//  Serial.println(degrez);

  
  degre3 = degrex.toInt();
  degre4 = degrez.toInt();
  
  error1 = degre3-deger;
  error2 = degre4-deger2;

  outx = ((error1*kp)+deger)+((error1-lasterror1)*kd);
  outz = ((error2*kp)+degre4)+((error2-lasterror2)*kd);
  
  servo3.write(degre3);
  servo4.write(degre4);


//fungsi menggerakkan servo
  if (outz != eskideger)
  {                  //if old value is not equal to new value ; which means we have movement on the sensor...
    y = outz;  //Here, this is personal. In order to stabilization. I just made some math...
    servo2.write(y); //
    eskideger = outz;
    Serial.print("z aksis:");
    Serial.print(outz);
  }
  if (outx != eskideger2)
  {
    x = 180 - outx;
    servo1.write(x);
    eskideger2 = outx;
    Serial.print(" // x aksis:");
    Serial.println(outx);
  }
  Serial.println(" ");
//  Serial.print("y aksis 2: ");
//  Serial.print(deger_2);
//  Serial.print(" // x aksis 2 : ");
//  Serial.println(deger2_2);
  
delay(250);
//  delay(1000);
}
