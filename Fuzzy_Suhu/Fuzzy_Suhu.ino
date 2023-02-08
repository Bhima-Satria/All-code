#include "DHT.h"


#define DHTTYPE DHT11
#define DHTPIN D2       //Pin Sensor DHT11
#define Led D8


DHT dht(DHTPIN, DHTTYPE);


float error;
float Derror;
float M_dingin, M_normal, M_panas;
float D_dingin, D_normal, D_panas;
float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float S, N, F;
float HS, HN, HF;
float MoM;
float error_1;
float Sp;

int Butt_30 = D3;
int Butt_35 = D4;
int Butt_40 = D5;
int Butt_45 = D6;
int Butt_Start = D7;

int Butt_State30 = 0;
int Butt_State35 = 0;
int Butt_State40 = 0;
int Butt_State45 = 0;
int Butt_StateStart = 0;

boolean dingin = false;
boolean normal = false;
boolean panas = false;
boolean Ddingin = false;
boolean Dnormal = false;
boolean Dpanas= false;


void setup() {
  
   pinMode(Butt_30, INPUT_PULLUP);
   pinMode(Butt_35, INPUT_PULLUP);
   pinMode(Butt_40, INPUT_PULLUP);
   pinMode(Butt_45, INPUT_PULLUP);
   pinMode(Butt_Start, INPUT_PULLUP);
   pinMode(Led, OUTPUT);
   Serial.begin(9600);

   dht.begin();
}

void loop() {
  
  Butt_State30 = digitalRead (Butt_30);
  Butt_State35 = digitalRead (Butt_35);
  Butt_State40 = digitalRead (Butt_40);
  Butt_State45 = digitalRead (Butt_45);
  Butt_StateStart = digitalRead (Butt_Start);
  
if (Butt_State30 == LOW){
  Sp = 30;
  if (Butt_StateStart == LOW){
    bacasuhu();
    fuzzyfikasi();
    defuzzyfikasi();
  }
  else {
    Serial.println ("Tekan Start");
    delay (1000);
  }
}

else if (Butt_State35 == LOW){
  Sp = 35;
  if (Butt_StateStart == LOW){
    bacasuhu();
    fuzzyfikasi();
    defuzzyfikasi();
  }
  else {
    Serial.println ("Tekan Start");
    delay (1000);
  }
}

else if (Butt_State40 == LOW){
  Sp = 40;
  if (Butt_StateStart == LOW){
    bacasuhu();
    fuzzyfikasi();
    defuzzyfikasi();
  }
  else {
    Serial.println ("Tekan Start");
    delay (1000);
  }
}

else if (Butt_State45 == LOW){
  Sp = 45;
  if (Butt_StateStart == LOW){
    bacasuhu ();
    fuzzyfikasi();
    defuzzyfikasi();
  }
  else {
    Serial.println ("Tekan Start");
    delay (1000);
  }
}

else {
  Serial.println ("Pilih Suhu");
  delay(1000);
  }
}

void bacasuhu(){
      
   delay(1000);
   float C = dht.readTemperature();
   error_1 = error;
   error = C-Sp ;
   Derror = error - error_1;
   
   Serial.println("====Baca Data====");
   Serial.print("Suhu : ");
   Serial.print(C);
   Serial.println("*C");
   delay(1000);
   Serial.print("error :");
   Serial.println(error);
   Serial.print("Derror : ");
   Serial.println(Derror);
}

void fuzzyfikasi (){
  //=====================//error//=========================
//***Label dingin***
if (error <= -0.75){
  M_dingin = 1 ;
  dingin = true;
}
/*else if (error >=-1.5 && error <-0.75){
  M_dingin=(error - (-1.5))/( (-0.75) - (-1.5));
  dingin=true;
}*/
else if (error >-0.75 && error <=0){
  M_dingin=(0-(error))/(0-(-0.75));
  dingin=true;
} 
/*else if (error <= -1.5){
  M_dingin = 1;
  dingin = true;
}*/

//***Label Normal***
if (error == 0){
  M_normal = 1 ;
  normal = true;
}
else if (error >=-0.75 && error <0){
  M_normal=(error - (-0.75))/(0 - (-0.75));
  normal=true;
}
else if (error >0 && error <=0.75){
  M_normal=(0.75-(error))/(0.75-0);
  normal=true;
} 

//***Label Panas***
if (error >= 0.75){
  M_panas = 1 ;
  panas = true;
}
else if (error >=0 && error <0.75){
  M_panas=(error - 0)/(0.75-0);
  panas=true;
}
/*else if (error >0.75 && error <=1.5){
  M_panas=(1.5 -(error))/(1.5 - 0.75);
  panas=true;
} */
/*else if (error >= 1.5){
  M_panas = 1;
  panas = true;
}*/

//=====================//Derror//=========================
//***Label dingin***
if (Derror <= -0.75){
  D_dingin = 1 ;
  Ddingin = true;
}
/*else if (Derror >=-1.5 && Derror <-0.75){
  D_dingin=(Derror - (-1.5))/( (-0.75) - (-1.5));
  Ddingin=true;
}*/
else if (Derror >-0.75 && Derror <=0){
  D_dingin=(0-(Derror))/(0-(-0.75));
  Ddingin=true;
} 
/*else if (Derror <= -1.5){
  D_dingin = 1;
  Ddingin = true;
}*/


//***Label Normal***
if (Derror == 0){
  D_normal = 1 ;
  Dnormal = true;
}
else if (Derror >= -0.75 && Derror <0){
  D_normal=(Derror - (-0.75))/(0 - (-0.75));
  Dnormal=true;
}
else if (Derror >0 && Derror <=0.75){
  D_normal=(0.75-(Derror))/(0.75-0);
  Dnormal=true;
} 

//***Label Panas***
if (Derror >= 0.75){
  D_panas = 1 ;
  Dpanas = true;
}
else if (Derror >=0 && Derror <0.75){
 D_panas=(Derror - 0)/(0.75-0);
  Dpanas=true;
}
/*else if (Derror >0.75 && Derror <=1.5){
  D_panas=(1.5 -(Derror))/(1.5 - 0.75);
  Dpanas=true;
} */
/*else if (Derror >= 1.5){
  D_panas = 1;
  Dpanas = true;
}*/

delay(100);
Serial.println("======Error======");
Serial.print("M_dingin : ");
Serial.println(M_dingin);
Serial.print("M_normal : ");
Serial.println(M_normal);
Serial.print("M_panas : ");
Serial.println(M_panas);
delay(100);

Serial.println("===Derror===");
Serial.print("D_dingin : ");
Serial.println(D_dingin);
Serial.print("D_normal : ");
Serial.println(D_normal);
Serial.print("D_panas : ");
Serial.println(D_panas);
delay(100);
}

void defuzzyfikasi(){
//===========Tabel Rule=============
Serial.println("===Inference Rule & Implikasi Min===");
if (dingin==true && Ddingin==true){
  rule1=min(M_dingin, D_dingin);
  Serial.print("rule1 : ");
  Serial.println(rule1);
  delay(100);
}
if (dingin==true && Dnormal==true){
  rule2=min(M_dingin, D_normal);
  Serial.print("rule2 : ");
  Serial.println(rule2);
  delay(100);
}
if (dingin==true && Dpanas==true){
  rule3=min(M_dingin, D_panas);
  Serial.print("rule3 : ");
  Serial.println(rule3);
  delay(100);
}
if (normal==true && Ddingin==true){
  rule4=min(M_normal, D_dingin);
  Serial.print("rule4 : ");
  Serial.println(rule4);
  delay(100);
}
if (normal==true && Dnormal==true){
  rule5=min(M_normal, D_normal);
  Serial.print("rule5 : ");
  Serial.println(rule5);
  delay(100);
}
if (normal==true && Dpanas==true){
  rule6=min(M_normal, D_panas);
  Serial.print("rule6 : ");
  Serial.println(rule6);
  delay(100);
}
if (panas==true && Ddingin==true){
  rule7=min(M_panas, D_dingin);
  Serial.print("rule7 : ");
  Serial.println(rule7);
  delay(100);
}
if (panas==true && Dnormal==true){
  rule8=min(M_panas, D_normal);
  Serial.print("rule8 : ");
  Serial.println(rule8);
  delay(100);
}
if (panas==true && Dpanas==true){
  rule9=min(M_panas, D_panas);
  Serial.print("rule9 : ");
  Serial.println(rule9);
  delay(100);
}


Serial.println("   ");
Serial.println("===Fungsi Implikasi Max===");
S= max(rule1, rule2);
N= max(max(rule3, rule4), rule7);
F= max(max(rule5, rule6), max(rule8, rule9));

Serial.print("Fast  : ");
Serial.println(F);
Serial.print("Normal: ");
Serial.println(N);
Serial.print("Slow  : ");
Serial.println(S);
delay(100);

Serial.println("=====Hasil Defuzzifikasi=====");
Serial.print("Defuzzifikasi : ");
MoM = max(max(S, N), F);

if (MoM==S){
  MoM=15;
  HS=15;
  digitalWrite(Led, HIGH);
  Serial.println(HS);
  
}
if (MoM==N){
  MoM=7.5;
  HN=15;
  digitalWrite(Led, HIGH);
  Serial.println(HN);
 
}
if (MoM==F){
  MoM=0;
  HF=0;
  digitalWrite(Led, LOW);
  Serial.println(HF);
}

//======Selesai======
Serial.println("Proses Selesai......");
Serial.println("   ");
delay(5000);
digitalWrite(Led, LOW);
}
