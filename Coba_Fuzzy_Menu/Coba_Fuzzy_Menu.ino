#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define DHTPIN D1     //Pin Sensor DHT22
#define DHTTYPE DHT22
#define LED D8
#define Motor D7

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);


String jam_a, nol_a;
String jam_b, nol_b;
String jam_c, nol_c;
String tanggal;

float error, C ;
float Derror, H ;
float M_dingin, M_normal, M_panas;
float D_dingin, D_normal, D_panas;
float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float S, N, F;
float HS, HN, HF;
float MoM;
float error_1;
int Sp;
int SpH;
int SpH1;
int SpH2;

int Butt_Up = D5;
int Butt_Down = D6;
int Butt_Next = D4;



int Up   = 0;
int Down = 0;
int Ok   = 0;


boolean dingin = false;
boolean normal = false;
boolean panas = false;
boolean Ddingin = false;
boolean Dnormal = false;
boolean Dpanas = false;
byte Simbol_derajat = B11011111;

void setup() {
  Serial.begin(9600);
  Wire.begin(D3, D2);
  dht.begin();
  lcd.begin();
  lcd.print("Connecting....");

  WiFiManager wifiManager;
  WiFi.mode(WIFI_STA);
  wifiManager.resetSettings();
  wifiManager.autoConnect("Orbital Shaker", "12345678");
  Serial.println("connected...yeey :)");
  delay(1000);

  pinMode(Butt_Up, INPUT_PULLUP);
  pinMode(Butt_Down, INPUT_PULLUP);
  pinMode(Butt_Next, INPUT_PULLUP);

  pinMode(LED, OUTPUT);
  pinMode(Motor, OUTPUT);

  lcd.clear();
  lcd.print("Orbital Shaker");
  lcd.setCursor(0, 1);
  lcd.print("Berbasis Fuzzy");
  delay (2000);
  lcd.clear();

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  Menu();
}


void Menu () {
  Up = digitalRead (Butt_Up);
  Down = digitalRead (Butt_Down);
  Ok = digitalRead (Butt_Next);

menu:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Pengaturan");
    lcd.setCursor(0, 1);
    lcd.print("1.Set");
    lcd.setCursor(9, 1);
    lcd.print("2.Start");
    delay(200);
    digitalWrite(Motor, LOW);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    if (Up == LOW) {
      delay(100);
      goto menu1;
    }
    if (Ok == LOW) {
      delay (100);
      goto Run;
    }

  }

menu1:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Atur Suhu");
    lcd.setCursor(0, 1);
    lcd.print("1.Ok 2.Next");
    delay(200);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    if (Up   == LOW) {
      delay (100);
      goto menu3;
    }
    if (Down == LOW) {
      delay (100);
      goto menu;
    }
    if (Ok   == LOW) {
      delay (100);
      goto menu2;
    }
  }


menu2:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Suhu :");
    lcd.setCursor(10, 0);
    lcd.print(Sp);
    lcd.setCursor(0, 1);
    lcd.print("1.Ok");
    delay(200);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    Sp = constrain(Sp, 0, 60);

    if (Ok    == LOW) {
      delay (100);
      goto menu1;
    }
    if (Up    == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(Sp++);
    }
    if (Down  == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(Sp--);
    }
  }

menu3:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Atur Waktu");
    lcd.setCursor(0, 1);
    lcd.print("1.Ok 2.Back");
    delay(200);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    //if (Up   == LOW) { delay (100); goto menu1; }
    if (Down == LOW) {
      delay (100);
      goto menu1;
    }
    if (Ok   == LOW) {
      delay (100);
      goto menu4;
    }
  }

menu4:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Jam : ");
    lcd.setCursor(10, 0);
    lcd.print(SpH);
    lcd.setCursor(0, 1);
    lcd.print("1.Ok");
    delay(200);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    SpH = constrain(SpH, 0, 23);

    if (Ok    == LOW) {
      delay (100);
      goto menu5;
    }
    if (Up    == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(SpH++);
    }
    if (Down  == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(SpH--);
    }

  }

menu5:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Menit : ");
    lcd.setCursor(11, 0);
    lcd.print(SpH1);
    lcd.setCursor(0, 1);
    lcd.print("1.Ok");
    delay(200);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    SpH1 = constrain(SpH1, 0, 59);

    if (Ok    == LOW) {
      delay (100);
      goto menu6;
    }
    if (Up    == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(SpH1++);
    }
    if (Down  == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(SpH1--);
    }

  }

menu6:
  while (1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Tanggal : ");
    lcd.setCursor(13, 0);
    lcd.print(SpH2);
    lcd.setCursor(0, 1);
    lcd.print("1.Ok");
    delay(200);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    SpH2 = constrain(SpH2, 0, 35);

    if (Ok    == LOW) {
      delay (100);
      goto menu3;
    }
    if (Up    == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(SpH2++);
    }
    if (Down  == LOW) {
      lcd.setCursor(10, 0);
      lcd.print(SpH2--);
    }

  }

Run:
  while (1) {
    lcd.clear();
    lcd.print ("Running : ");
    lcd.setCursor(9, 0);
    lcd.print(Sp);
    lcd.write(Simbol_derajat);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print ("2.Back");
    digitalWrite (Motor, HIGH);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);

    if (Down == LOW) {
      delay(100);
      goto menu;
    }
    bacasuhu();
    fuzzyfikasi();
    if (Down == LOW) {
      delay(100);
      goto menu;
    }
    defuzzyfikasi();

    if (Down == LOW) {
      delay(100);
      goto menu;
    }
    if (String(SpH) == jam_a && String (SpH1) == jam_b && String(SpH2) == tanggal ) {
      delay (100);
      goto menu;
    }
  }
}

void bacasuhu() {

  delay(1000);
  C = dht.readTemperature();
  H = dht.readHumidity();
  error_1 = error;
  error = C - Sp ;
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

void fuzzyfikasi () {
  //=====================//error//=========================
  //***Label dingin***
  if (error <= -0.75) {
    M_dingin = 1 ;
    dingin = true;
  }
  /*else if (error >=-1.5 && error <-0.75){
    M_dingin=(error - (-1.5))/( (-0.75) - (-1.5));
    dingin=true;
    }*/
  else if (error > -0.75 && error <= 0) {
    M_dingin = (0 - (error)) / (0 - (-0.75));
    dingin = true;
  }
  /*else if (error <= -1.5){
    M_dingin = 1;
    dingin = true;
    }*/
  else {
    M_dingin = 0;
  }

  //***Label Normal***
  if (error == 0) {
    M_normal = 1 ;
    normal = true;
  }
  else if (error >= -0.75 && error < 0) {
    M_normal = (error - (-0.75)) / (0 - (-0.75));
    normal = true;
  }
  else if (error > 0 && error <= 0.75) {
    M_normal = (0.75 - (error)) / (0.75 - 0);
    normal = true;
  }
  else {
    M_normal = 0;
  }

  //***Label Panas***
  if (error >= 0.75) {
    M_panas = 1 ;
    panas = true;
  }
  else if (error >= 0 && error < 0.75) {
    M_panas = (error - 0) / (0.75 - 0);
    panas = true;
  }
  else {
    M_panas = 0;
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
  if (Derror <= -0.75) {
    D_dingin = 1 ;
    Ddingin = true;
  }
  /*else if (Derror >=-1.5 && Derror <-0.75){
    D_dingin=(Derror - (-1.5))/( (-0.75) - (-1.5));
    Ddingin=true;
    }*/
  else if (Derror > -0.75 && Derror <= 0) {
    D_dingin = (0 - (Derror)) / (0 - (-0.75));
    Ddingin = true;
  }
  /*else if (Derror <= -1.5){
    D_dingin = 1;
    Ddingin = true;
    }*/
  else {
    D_dingin = 0;
  }


  //***Label Normal***
  if (Derror == 0) {
    D_normal = 1 ;
    Dnormal = true;
  }
  else if (Derror >= -0.75 && Derror < 0) {
    D_normal = (Derror - (-0.75)) / (0 - (-0.75));
    Dnormal = true;
  }
  else if (Derror > 0 && Derror <= 0.75) {
    D_normal = (0.75 - (Derror)) / (0.75 - 0);
    Dnormal = true;
  }
  else {
    D_normal = 0;
  }

  //***Label Panas***
  if (Derror >= 0.75) {
    D_panas = 1 ;
    Dpanas = true;
  }
  else if (Derror >= 0 && Derror < 0.75) {
    D_panas = (Derror - 0) / (0.75 - 0);
    Dpanas = true;
  }
  else {
    D_panas = 0;
  }
  /*else if (Derror >0.75 && Derror <=1.5){
    D_panas=(1.5 -(Derror))/(1.5 - 0.75);
    Dpanas=true;
    } */
  /*else if (Derror >= 1.5){
    D_panas = 1;
    Dpanas = true;
    }*/


  delay(1000);
  Serial.println("======Error======");
  Serial.print("M_dingin : ");
  Serial.println(M_dingin);
  Serial.print("M_normal : ");
  Serial.println(M_normal);
  Serial.print("M_panas : ");
  Serial.println(M_panas);
  delay(1000);

  Serial.println("===Derror===");
  Serial.print("D_dingin : ");
  Serial.println(D_dingin);
  Serial.print("D_normal : ");
  Serial.println(D_normal);
  Serial.print("D_panas : ");
  Serial.println(D_panas);
  delay(1000);
}

void defuzzyfikasi() {
  //===========Tabel Rule=============
  Serial.println("===Inference Rule & Implikasi Min===");
  if (dingin == true && Ddingin == true) {
    rule1 = min(M_dingin, D_dingin);
    Serial.print("rule1 : ");
    Serial.println(rule1);
    delay(100);
  }
  if (dingin == true && Dnormal == true) {
    rule2 = min(M_dingin, D_normal);
    Serial.print("rule2 : ");
    Serial.println(rule2);
    delay(100);
  }
  if (dingin == true && Dpanas == true) {
    rule3 = min(M_dingin, D_panas);
    Serial.print("rule3 : ");
    Serial.println(rule3);
    delay(100);
  }
  if (normal == true && Ddingin == true) {
    rule4 = min(M_normal, D_dingin);
    Serial.print("rule4 : ");
    Serial.println(rule4);
    delay(100);
  }
  if (normal == true && Dnormal == true) {
    rule5 = min(M_normal, D_normal);
    Serial.print("rule5 : ");
    Serial.println(rule5);
    delay(100);
  }
  if (normal == true && Dpanas == true) {
    rule6 = min(M_normal, D_panas);
    Serial.print("rule6 : ");
    Serial.println(rule6);
    delay(100);
  }
  if (panas == true && Ddingin == true) {
    rule7 = min(M_panas, D_dingin);
    Serial.print("rule7 : ");
    Serial.println(rule7);
    delay(100);
  }
  if (panas == true && Dnormal == true) {
    rule8 = min(M_panas, D_normal);
    Serial.print("rule8 : ");
    Serial.println(rule8);
    delay(100);
  }
  if (panas == true && Dpanas == true) {
    rule9 = min(M_panas, D_panas);
    Serial.print("rule9 : ");
    Serial.println(rule9);
    delay(100);
  }


  Serial.println("   ");
  Serial.println("===Fungsi Implikasi Max===");
  S = max(rule1, rule2);
  N = max(max(rule3, rule4), rule7);
  F = max(max(rule5, rule6), max(rule8, rule9));

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

  if (MoM == S) {
    MoM = 7.5;
    HS = 7.5;
    digitalWrite(LED, HIGH);
    Serial.println(HS);
    delay(15 * 1000);
  }
  if (MoM == N) {
    MoM = 3.5;
    HN = 3.5;
    digitalWrite(LED, HIGH);
    Serial.println(HN);
    delay(7.5 * 1000);
  }
  if (MoM == F) {
    MoM = 0;
    HF = 0;
    digitalWrite(LED, LOW);
    Serial.println(HF);
  }

  //======Selesai======
  Serial.println("Proses Selesai......");
  Serial.println("   ");
  digitalWrite(LED, LOW);
  lcd.clear();

  //========================Koneksi dan Kirim Data ke Server================================
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;                      //Declare object of class HTTPClient

    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
    String postStr = "http://orbitalshaker.000webhostapp.com/submit.php?Suhu=" + String(C) + "&Kelembaban=" + String(H) + "&FLC=" + String(MoM);
    String postStr1 = "http://api.geonames.org/timezoneJSON?lat=-7&lng=112&username=vikingsbhima";

    http.begin(postStr);                 //Specify request destination
    int httpCode = http.POST(postStr);   //Send the request
    String payload = http.getString();   //Get the response payload

    http.begin(postStr1);                 //Specify request destination
    int httpCode1 = http.POST(postStr1);   //Send the request
    String payload1 = http.getString();   //Get the response payload

    jam_a = payload1.substring(202, 204);

    if (jam_a == "00") {
      jam_a = "0";
    }
    else if (jam_a == "01") {
      jam_a = "1";
    }
    else if (jam_a == "02") {
      jam_a = "2";
    }
    else if (jam_a == "03") {
      jam_a = "3";
    }
    else if (jam_a == "04") {
      jam_a = "4";
    }
    else if (jam_a == "05") {
      jam_a = "5";
    }
    else if (jam_a == "06") {
      jam_a = "6";
    }
    else if (jam_a == "07") {
      jam_a = "7";
    }
    else if (jam_a == "08") {
      jam_a = "8";
    }
    else if (jam_a == "09") {
      jam_a = "9";
    }
    else jam_a = jam_a;

    jam_b = payload1.substring(205, 207);

    if (jam_b == "00") {
      jam_b = "0";
    }
    else if (jam_b == "01") {
      jam_b = "1";
    }
    else if (jam_b == "02") {
      jam_b = "2";
    }
    else if (jam_b == "03") {
      jam_b = "3";
    }
    else if (jam_b == "04") {
      jam_b = "4";
    }
    else if (jam_b == "05") {
      jam_b = "5";
    }
    else if (jam_b == "06") {
      jam_b = "6";
    }
    else if (jam_b == "07") {
      jam_b = "7";
    }
    else if (jam_b == "08") {
      jam_b = "8";
    }
    else if (jam_b == "09") {
      jam_b = "9";
    }
    else jam_b = jam_b;

    jam_c = payload1.substring(191, 199);
    tanggal = payload1.substring(199, 201);
    if (tanggal == "00") {
      tanggal = "0";
    }
    else if (tanggal == "01") {
      tanggal = "1";
    }
    else if (tanggal == "02") {
      tanggal = "2";
    }
    else if (tanggal == "03") {
      tanggal = "3";
    }
    else if (tanggal == "04") {
      tanggal = "4";
    }
    else if (tanggal == "05") {
      tanggal = "5";
    }
    else if (tanggal == "06") {
      tanggal = "6";
    }
    else if (tanggal == "07") {
      tanggal = "7";
    }
    else if (tanggal == "08") {
      tanggal = "8";
    }
    else if (tanggal == "09") {
      tanggal = "9";
    }
    else tanggal = tanggal;


    lcd.setCursor(0, 0);
    lcd.print("Sekarang Pukul :");
    lcd.setCursor(0, 1);
    lcd.print(jam_a);
    lcd.print(":");

    lcd.print(jam_b);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Timer Off :");
    lcd.setCursor(0, 1);
    lcd.print("tgl:");
    lcd.print(jam_c);
    lcd.print(SpH2);
    delay(3000);
    lcd.clear();
    lcd.print("Timer Off :");
    lcd.setCursor(0, 1);
    lcd.print("Jam:");
    lcd.print(SpH);
    lcd.print(":");
    lcd.print(SpH1);
    delay(3000);
    lcd.clear();

    Serial.println("====Kirim Data====");
    Serial.println(httpCode);            //Print HTTP return code
    Serial.println(payload);             //Print request response payload
    http.end();  //Close connection

  }
  else {
    Serial.println("Error in WiFi connection");
  }
  delay(1000);
}
