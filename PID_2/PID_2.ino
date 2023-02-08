#include <NewPing.h>

//Scan Kanan
#define TRIGGER_PIN1    A4   
#define ECHO_PIN1       A5     
//Scan Depan
#define TRIGGER_PIN2    A0    
#define ECHO_PIN2       A1   
//Kipas
#define Fan 8

#define MAX_DISTANCE    100   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int dir1  = 4;                // inisiai pin direct (arah putaran) untuk motor kiri
int pwm1  = 5;                // inisiai pin pwm (kecepatan putar) untuk motor kiri
int pwm2  = 6;                // inisiai pin direct (arah putaran) untuk motor kanan
int dir2  = 7;                // inisiai pin pwm (kecepatan putar) untuk motor kanan

int pwm;

int Upper =100;               // Pwm maksimal yang diizinkan
int Lower =45;                // Pwm minimal yang diizinkan
int Sen_Flame = 0;


NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

void setup() 
{
  Serial.begin(115200);       // Open serial monitor at 115200 baud to see ping results.
  pinMode(dir1, OUTPUT);      // Set pin untuk motor sebagai OUTPUT
  pinMode(pwm1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm2, OUTPUT);
}

void loop() 
{
  //Kodingan di bawah ini untuk mengambil nilai yang terbaca oleh sensor ultrasonic (dalam satuan CM)
  delay(50);
  unsigned int us = sonar1.ping();     // Send ping, get ping time in microseconds (uS).
  int kanan = us / US_ROUNDTRIP_CM;
  unsigned int us2 = sonar2.ping();    // Send ping, get ping time in microseconds (uS).
  int depan = us2 / US_ROUNDTRIP_CM;

  if (kanan>20) {kanan=20;}            // Pembacaan maksimal sensor kanan adalah 20, di atas 20 tetap terbaca 20.
  else {kanan=kanan;}
  //---akhir kodingan membaca nilai sensor

  // Kodingan di bawah ini adalah untuk melakukan aksi ketika kondisi Robot menabrak dinding di depan
  if (depan<=20)                        // ketika sensor depan mendeteksi dinding kurang dari 3 cm robot harus belok kiri
  {

  analogWrite(pwm1, 100);
  analogWrite(pwm2, 0);
  }
  //---akhir kodingan kondisi menabrak dinding depan


  // Kodingan di bawah ini adalah kondisi kebalikan dari kondisi di atas yaitu ketika sensor depan tidak menabrak dinding
  // Kodingan menggunakkan pendekatan metode PID (Kontrol Proporsional).
  else
  {
  int sp = 5;                          // sp = set point, posisi robot harus senantiasa di jarak 7 cm
  int error = sp - kanan;              // mendefinisikan nilai error, selisih antara setpoint dan pembacaan sensor kanan
    
  
  
  int pid = 5*error;                   // Pembobotan nilai PID, Angka 9 adalah konstanta proporsional (Kp)
    
  pwm=sp*5-pid;                       // Pembobotan OUTPUT/pwm hasil perhitungan PID, saya masih belum yakin ini sesuai dengan teori PID
  if(pwm>Upper){pwm=Upper;}            // Angka 10 adalah konstanta yang membuat pwm berada dikisaran angka ratusan/motor bisa berputar
  if(pwm<Lower){pwm=Lower;}
  int ki=pwm;
  
  pwm=sp*5+pid;
  if(pwm>Upper){pwm=Upper;}
  if(pwm<Lower){pwm=Lower;}
  int ka=pwm;
      
  analogWrite(pwm1, 100 - ka);
  analogWrite(pwm2, 100 - ki);
  }
}
/*
void Api ()
{
 if (Sen_Flame = 1){
 digitalWrite(Fan, HIGH);
  digitalWrite(pwm1, LOW);
    digitalWrite(dir1, LOW); 
     digitalWrite(pwm2, LOW);
      digitalWrite(dir2, LOW);
 }
 else {
  digitalWrite(Fan, LOW);
 }
 */


