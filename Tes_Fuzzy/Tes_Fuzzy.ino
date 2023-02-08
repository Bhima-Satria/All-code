#include <OneWire.h>
#include <DallasTemperature.h>
// #include "DHT.h"


#define ONE_WIRE_BUS A0 //Pin Sensor Suhu DS18B20
#define DHTPIN 2       //Pin Sensor DHT11
#define DHTTYPE DHT11
#define LED     0
#define LED_Proses 3
#define Fan 4
#define Mist 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// DHT dht(DHTPIN, DHTTYPE);


float suhu=0;
float kelembaban=0;
float miu_dingin, miu_sejuk, miu_normalc, miu_hangat, miu_panas;
float miu_Tkering, miu_kering, miu_normalm, miu_lembab, miu_basah;
float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float rule10, rule11, rule12, rule13, rule14, rule15, rule16, rule17, rule18;
float rule19, rule20, rule21, rule22, rule23, rule24, rule25;
float SC, C, N, L, SL;
float H_SC, H_C, H_N, H_L, H_SL;
float MoM;

boolean dingin = false;
boolean sejuk = false;
boolean normalc = false;
boolean hangat = false;
boolean panas = false;
boolean Tkering = false;
boolean kering = false;
boolean normalm = false;
boolean lembab = false;
boolean basah = false ;

void setup() {
//============//Koneksi Network//=====================
  Serial.begin(115200);                                  //Serial connection
  delay(1000);
  
   sensors.begin();
   Serial.println("Sensor Tes.....\t");
   Serial.println("   ");
//   dht.begin();
   pinMode(LED_Proses,OUTPUT);
   pinMode(LED, OUTPUT);
   pinMode(Fan,OUTPUT);
}

void loop() {
digitalWrite(LED, LOW);
digitalWrite(LED_Proses,HIGH);
//==============//Proses Input//=======================
   delay(2000);
   sensors.requestTemperatures();
//   suhu=sensors.getTempCByIndex(0);
//   float h = dht.readHumidity();
   kelembaban = 78;
   suhu       = 37;

   
   Serial.println("====Baca Data====");
   Serial.print("Suhu : ");
   Serial.print(suhu);
   Serial.println("*C");
   Serial.print("Humidity : ");
   Serial.print(kelembaban);
   Serial.println("%");
   delay(1000);
   Serial.println("====Fuzzifikasi====");
   Serial.println("   ");

//=====================//suhu//=========================
//***Label Dingin***
if (suhu == 7.5){
  miu_dingin= 1 ;
  dingin=true;
}
else if (suhu >0 && suhu <=7.5){
  miu_dingin=(suhu-0)/(7.5-0);
  dingin=true;
}
else if (suhu >=7.5 && suhu <15){
  miu_dingin=(15-suhu)/(15-7.5);
  dingin=true;
} 
//***Label Sejuk***
if (suhu == 15){
  miu_sejuk= 1 ;
  sejuk=true;
}
else if (suhu >10 && suhu <=15){
  miu_sejuk=(suhu-10)/(15-10);
  sejuk=true;
}
else if (suhu >=15 && suhu <20){
  miu_sejuk=(20-suhu)/(20-15);
  sejuk=true;
}

//***Label Normal***
if (suhu == 22.5){
  miu_normalc=1;
  normalc=true;
} 
else if (suhu >15 && suhu <=22.5){
  miu_normalc=(suhu-15)/(22.5-15);
  normalc=true; 
}
else if (suhu >=22.5 && suhu <30){
  miu_normalc=(30-suhu)/(30-22.5);
  normalc=true;
}

//***Label Hangat***
if (suhu == 30){
  miu_hangat=1;
  hangat=true;
}
else if (suhu >25 && suhu <=30){
  miu_hangat=(suhu-25)/(30-25);
  hangat=true;
}
else if (suhu >=30 && suhu <35){
  miu_hangat=(35-suhu)/(35-30);
  hangat=true;
}

///***Label Panas***
if (suhu == 37.5){
  miu_panas= 1;
  panas=true;
}
else if (suhu >30 && suhu <=37.5){
  miu_panas=(suhu-30)/(37.5-30);
  panas=true;
} 
else if (suhu >=37.5 && suhu <45){
  miu_panas=(45-suhu)/(45-37.5);
  panas=true;
}
    
//=================//Kelembaban//=================
//***label Tkering***
if (kelembaban == 15 ){
  miu_Tkering=1;
  Tkering=true;
}
else if(kelembaban >0 && kelembaban <=15){
  miu_Tkering=(kelembaban-0)/(15-0);
  Tkering=true;
}
else if (kelembaban >=15 && kelembaban <30){
  miu_Tkering=(30-kelembaban)/(30-15);
  Tkering=true; 
}

//***Label Kering***
if (kelembaban == 30){
  miu_kering = 1;
  kering=true;
}
else if(kelembaban >15 && kelembaban <=30){
  miu_kering=(kelembaban-15)/(30-20);
  kering=true;
}
else if (kelembaban >=30 && kelembaban <45){
  miu_kering=(45-kelembaban)/(45-30);
  kering=true;
}

//***Label Normal***
if (kelembaban == 50 ){
  miu_normalm=1;
  normalm=true;
}
else if (kelembaban >30 && kelembaban <=50){
  miu_normalm =(kelembaban-30)/(50-30);
  normalm=true;
}
else if (kelembaban >=50 && kelembaban <70){
  miu_normalm = (70-kelembaban)/(70-50);
  normalm=true;
}

//***Label lembab***
if (kelembaban == 70){
  miu_lembab=1;
  lembab=true;
}
else if (kelembaban >55 && kelembaban <=70){
  miu_lembab=(kelembaban-55)/(70-55);
  lembab=true; 
}
else if (kelembaban >=70 && kelembaban <85){
  miu_lembab=(85-kelembaban)/(85-70);
  lembab=true;
}

//***Label Sangat Lembab***
if (kelembaban == 85){
  miu_basah=1;
  basah=true;
}
else if (kelembaban >70 && kelembaban <=85){
  miu_basah =(kelembaban-70)/(85-70);
  basah=true;
}
else if (kelembaban >=85 && kelembaban <100){
  miu_basah = (100-kelembaban)/(100-85);
  basah=true;
}

//===============Tampilan miu=================
delay(100);
Serial.println("======SUHU======");
Serial.print("miu_dingin : ");
Serial.println(miu_dingin);
Serial.print("miu_sejuk : ");
Serial.println(miu_sejuk);
Serial.print("miu_normal : ");
Serial.println(miu_normalc);
Serial.print("miu_hangat : ");
Serial.println(miu_hangat);
Serial.print("miu_panas : ");
Serial.println(miu_panas);
Serial.println("   ");
delay(100);
Serial.println("===KELEMBABAN===");
Serial.print("miu_Tkering : ");
Serial.println(miu_Tkering);
Serial.print("miu_kering : ");
Serial.println(miu_kering);
Serial.print("miu_normal : ");
Serial.println(miu_normalm);
Serial.print("miu_lembab : ");
Serial.println(miu_lembab);
Serial.print("miu_Slembab : ");
Serial.println(miu_basah);
Serial.println("   ");
delay(200);

//===========Tabel Rule=============
Serial.println("===Inference Rule & Implikasi Min===");
if (dingin==true && Tkering==true){
  rule1=min(miu_dingin, miu_Tkering);
  Serial.print("rule1 : ");
  Serial.println(rule1);
  delay(500);
}
if (dingin==true && kering==true){
  rule2=min(miu_dingin, miu_kering);
  Serial.print("rule2 : ");
  Serial.println(rule2);
  delay(500);
}
if (dingin==true && normalm==true){
  rule3=min(miu_dingin, miu_normalm);
  Serial.print("rule3 : ");
  Serial.println(rule3);
  delay(500);
}
if (dingin==true && lembab==true){
  rule4=min(miu_dingin, miu_lembab);
  Serial.print("rule4 : ");
  Serial.println(rule4);
  delay(500);
}
if (dingin==true && basah==true){
  rule5=min(miu_dingin, miu_basah);
  Serial.print("rule5 : ");
  Serial.println(rule5);
  delay(500);
}
if (sejuk==true && Tkering==true){
  rule6=min(miu_sejuk, miu_Tkering);
  Serial.print("rule6 : ");
  Serial.println(rule6);
  delay(500);
}
if (sejuk==true && kering==true){
  rule7=min(miu_sejuk, miu_kering);
  Serial.print("rule7 : ");
  Serial.println(rule7);
  delay(500);
}
if (sejuk==true && normalm==true){
  rule8=min(miu_sejuk, miu_normalm);
  Serial.print("rule8 : ");
  Serial.println(rule8);
}
if (sejuk==true && lembab==true){
  rule9=min(miu_sejuk, miu_lembab);
  Serial.print("rule9 : ");
  Serial.print(rule9);
  delay(500);
}
if (sejuk==true && basah==true){
  rule10=min(miu_sejuk, miu_basah);
  Serial.print("rule10 : ");
  Serial.println(rule10);
  delay(500);
}
if (normalc==true && Tkering==true){
  rule11=min(miu_normalc, miu_Tkering);
  Serial.print("rule11 : ");
  Serial.println(rule11);
  delay(500);
}
if (normalc==true && kering==true){
  rule12=min(miu_normalc, miu_kering);
  Serial.print("rule12 : ");
  Serial.println(rule12);
  delay(500);
}
if (normalc==true && normalm==true){
  rule13=min(miu_normalc, miu_normalm);
  Serial.print("rule13 : ");
  Serial.println(rule13);
  delay(500);
}
if (normalc==true && lembab==true){
  rule14=min(miu_normalc, miu_lembab);
  Serial.print("rule14 :");
  Serial.println(rule14);
  delay(500);
}
if (normalc==true && basah==true){
  rule15=min(miu_normalc, miu_basah);
  Serial.print("rule15 :");
  Serial.println(rule15);
  delay(500);
}
if (hangat==true && Tkering==true){
  rule16=min(miu_hangat, miu_Tkering);
  Serial.print("rule16 :");
  Serial.println(rule16);
  delay(500);
}
if (hangat==true && kering==true){
  rule17=min(miu_hangat, miu_kering);
  Serial.print("rule17 :");
  Serial.println(rule17);
  delay(500);
}
if (hangat==true && normalm==true){
  rule18=min(miu_hangat, miu_normalm);
  Serial.print("rule18 :");
  Serial.println(rule18);
  delay(500);
}
if (hangat==true && lembab==true){
  rule19=min(miu_hangat, miu_lembab);
  Serial.print("rule19 :");
  Serial.println(rule19);
  delay(500);
}
if (hangat==true && basah==true){
  rule20=min(miu_hangat, miu_basah);
  Serial.print("rule20 :");
  Serial.println(rule20);
  delay(500);
}
if (panas==true && Tkering==true){
  rule21=min(miu_panas, miu_Tkering);
  Serial.print("rule21 :");
  Serial.println(rule21);
  delay(500);
}
if (panas==true && kering==true){
  rule22=min(miu_panas, miu_kering);
  Serial.print("rule22 :");
  Serial.println(rule22);
  delay(500);
}
if (panas==true && normalm==true){
  rule23=min(miu_panas, miu_normalm);
  Serial.print("rule23 :");
  Serial.println(rule23);
  delay(500);
}
if (panas==true && lembab==true){
  rule24=min(miu_panas, miu_lembab);
  Serial.print("rule24 :");
  Serial.println(rule24);
  delay(500);
}
if (panas==true && basah==true){
  rule25=min(miu_panas, miu_basah);
  Serial.print("rule25 :");
  Serial.println(rule25);
  delay(500);
}

Serial.println("   ");
Serial.println("===Fungsi Implikasi Max===");
SC=max(max(max(rule5, rule10), max(rule15, rule20)), rule25);
C =max(max(max(rule3, rule4), max(rule9, rule14)), rule19);
N =max(max(rule8,rule13),rule24);
L =max(max(max(rule2,rule7),max(rule12,rule17)),(max(rule18,rule23)));
SL=max(max(max(rule1,rule6),max(rule11,rule16)),(max(rule21,rule22)));
delay(1000);

Serial.print("Sangat Cepat: ");
Serial.println(SC);
Serial.print("Cepat       : ");
Serial.println(C);
Serial.print("Normal      : ");
Serial.println(N);
Serial.print("Lama        : ");
Serial.println(L);
Serial.print("Sangat Lama : ");
Serial.println(SL);
Serial.println("   ");
delay(3000);

//===========Defuzzifikasi===========
Serial.println("=====Hasil Defuzzifikasi=====");
Serial.print("Defuzzifikasi : ");
MoM = max(max(max(SC,C),max(N,L)),SL);
if (MoM==SC){
  MoM=0;
  H_SC=60;
  Serial.print("Sangat Cepat : ");
  Serial.println(MoM);
  digitalWrite(Fan,HIGH);
  delay(H_SC*1000);
}
else if (MoM==C){
  MoM=180;
  H_C=180;
  Serial.print("Cepat : ");
  Serial.println(H_C);
  digitalWrite(Mist,HIGH);
  delay(H_C*1000);
}
else if(MoM==N){
  MoM=300;
  H_N=300;
  Serial.print("Normal : ");
  Serial.println(H_N);
  digitalWrite(Mist,HIGH);
  delay(H_N*1000);
}
else if(MoM==L){
  MoM=420;
  H_L=420;
  Serial.print("Lama : ");
  Serial.println(H_L);
  digitalWrite(Mist,HIGH);
  delay(H_L*1000);
}
else if(MoM==SL){
  MoM=600;
  H_SL=600;
  Serial.print("Sangat Lama : ");
  Serial.println(H_SL);
  digitalWrite(Mist,HIGH);
  delay(H_SL*1000);
}

digitalWrite(Mist,LOW);

//======Selesai======
Serial.println("Proses Selesai......");
Serial.println("   ");
delay(2000);
 
}


