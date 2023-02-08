#include <NewPing.h>

//Scan Depan
#define TRIG_PIN1   A0
#define ECHO_PIN1   A1

//Scan Kiri
#define TRIG_PIN2   A2
#define ECHO_PIN2   A3

//Scan Kanan
#define TRIG_PIN3   A4
#define ECHO_PIN3   A5

#define Jarak_Maks    50

//Kipas
int Fan = 9;

//Sensor Api
int Sen_Flame = 8;

//Direct Motor
int dirL  = 4;
int pwmL  = 5;
int dirR  = 7;
int pwmR  = 6;

int error, lasterror, outkr, outkn, sp=10, kp=7, kd=15, setpwm=200, maks=255;
int kiri, kanan, depan;

//Sensor Ultrasonik
NewPing sonar1  (TRIG_PIN1, ECHO_PIN1, Jarak_Maks);
NewPing sonar2  (TRIG_PIN2, ECHO_PIN2, Jarak_Maks);
NewPing sonar3  (TRIG_PIN3, ECHO_PIN3, Jarak_Maks);



void setup() {
Serial.begin (9600);
  pinMode (dirL, OUTPUT);
  pinMode (pwmL, OUTPUT);
  pinMode (dirR, OUTPUT);
  pinMode (pwmR, OUTPUT);
  pinMode (Sen_Flame, INPUT);
  pinMode (Fan, OUTPUT);
}

void ultras () {
  delay (50);
  unsigned int usd = sonar1.ping();
   depan = usd/US_ROUNDTRIP_CM;
  unsigned int usL = sonar2.ping();
   kiri  = usL/US_ROUNDTRIP_CM;
  unsigned int usR = sonar3.ping();
   kanan = usR/US_ROUNDTRIP_CM;

 if (depan>30) { depan=30;}//pembatas baca ultra jika nilai > 40 maka =40
 else if (depan <= 0 ) { depan=30;}
 else {depan=depan;}
 
 if (kanan>30) {kanan=30;}
 else if (kanan <= 0 ) { kanan=30;}
 else {kanan=kanan;}
 
 if (kiri>30) {kiri=30;}
 else if (kiri <= 0) { kiri=30;}
 else {kiri=kiri;}


}

void errorkiri (){
  error = sp- kiri;
  if ( error < -5 ) { error = -5;}
}

void errorkanan (){
  error = -sp + kanan;
  if ( error > 5 ) { error = 5;}
}

void PID (){
  outkr=((error*kp)+setpwm) + ((error-lasterror)*kd);
  outkn=((-error*kp)+setpwm) - ((error-lasterror)*kd);
  lasterror=error;
  
}

void motor(){
 // motor kiri
 if (outkr > maks){
  outkr = maks;
  digitalWrite(dirL, LOW);
  analogWrite (pwmL, outkr);
 }
 else if (outkr == setpwm){
  outkr=setpwm;
  digitalWrite(dirL, LOW);
  analogWrite (pwmL, outkr);
 }
 else if (outkr >= 0){
  outkr = outkr;
  digitalWrite (dirL, LOW);
  analogWrite (pwmL, outkr);
 }
 else if (outkr < -maks) {
  outkr = maks;
  digitalWrite (dirL, LOW);
  analogWrite (pwmL, outkr); 
 }
 else if (outkr < 0) {
  outkr = (-outkr);
  digitalWrite (dirR, LOW);
  analogWrite (pwmR, outkr);
 }
 
 // motor kanan
 if (outkn > maks) {
  outkn = maks;
  digitalWrite (dirR, LOW);
  analogWrite (pwmR, outkn);
 }
 else if (outkn == setpwm) {
  outkn = setpwm;
  digitalWrite (dirR, LOW);
  analogWrite (pwmR, outkn);
 }
 else if (outkn >= 0) {
  outkn = outkn;
  digitalWrite (dirR, LOW);
  analogWrite (pwmR, outkn);
 }
 else if (outkn < -maks) {
 outkn = maks;
 digitalWrite (dirR, LOW);
 analogWrite (pwmR, outkn);
 }
 else if (outkn < 0) {
 outkn = (-outkn);
 digitalWrite (dirL, LOW);
 analogWrite (pwmL, outkn);
 }
}

void scankiri (){
  ultras();
  errorkiri();
  PID();
  motor();
    if ( depan < 10 ) {
    digitalWrite(dirL, LOW);
    analogWrite (pwmL, 100);
    digitalWrite(dirR, HIGH);
    analogWrite (pwmR, 50);
  }
}

void scankanan (){
  ultras();
  errorkanan();
  PID();
  motor();
    if (depan < 10) {
    digitalWrite(dirL, HIGH);
    analogWrite (pwmL,50);
    digitalWrite(dirR, LOW);
    analogWrite (pwmR, 100);
  }
}

void baca_api (){

}

// program utama dijalankan
void loop() {
  scankiri();
  
 int kondisi_api = digitalRead (Sen_Flame);  
    // Serial.print (kondisi_api); 
    if (kondisi_api < 1 ){
    digitalWrite (dirR, LOW);
    digitalWrite (dirL, LOW);
    analogWrite  (pwmR, 0);
    analogWrite  (pwmL, 0);
    digitalWrite (Fan, HIGH);
    }
    else {digitalWrite (Fan, LOW);}
/* Serial.print ("error : ");
 Serial.println (error);
 Serial.print ("depan : ");
 Serial.println (depan);
 Serial.print ("Kiri : ");
 Serial.println (kiri);
 Serial.print ("Kanan : ");
 Serial.println (kanan);
 delay (500);*/
}


