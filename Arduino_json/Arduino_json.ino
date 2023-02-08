#include <ArduinoJson.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include "FirebaseJson.h"



#define FIREBASE_HOST "monitoringsoilmoisture.firebaseio.com"
#define FIREBASE_AUTH "g6GIB3flY82CSpOoBceM1bdrCPpxufTxy9UZiydL"
#define WIFI_SSID "Workshop_Batujajar"
#define WIFI_PASSWORD "Workshop2020"
#define PIN_POMPA D7
#define PIN_SENSOR A0

float error ;
float Derror ;
float M_negatif, M_zero, M_positif;
float D_negatif, D_zero, D_positif;
float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float S, N, F;
float HS, HN, HF;
float MoM;
float error_1;
float C;
int Sp;

boolean negatif = false;
boolean zero = false;
boolean positif = false;
boolean Dnegatif = false;
boolean Dzero = false;
boolean Dpositif = false;

//gawe NTP waktu
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;

NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//gawe misah data json
const size_t capacity = 4 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + 260;
DynamicJsonDocument doc(capacity);

FirebaseJson json;

String namaNode = "Node4";
String pathNode = "/DaftarPerangkat/" + namaNode;
String namaPerangkat = "WaterPump";
String daftarPerangkat = "/DaftarPerangkat/";
String pathPerangkat = "/DaftarPerangkat/" + namaPerangkat;

int SensorValue;

FirebaseData firebaseData;
void printJsonObjectContent(FirebaseData &data);

//String hasiljson(FirebaseData &data){
//  FirebaseJsonData &json = data.jsonObject();
//  String jsonStr;
//  json.toString(jsonStr);
//  return jsonStr;
//}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  pinMode(PIN_POMPA, OUTPUT);
  /*
    This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
    Firewall that allows only GET and POST requests.

    Firebase.enableClassicRequest(firebaseData, true);
  */
  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();

  //pengiriman data sensor
  //Serial.println("Proses membaca sensor mulai");
  SensorValue = 0;
  for (int balen = 0; balen < 100; balen++) {
    SensorValue = (analogRead(PIN_SENSOR) + SensorValue) / 2;
  }

  //Serial.println("Proses membaca sensor selesai");
  json.add("SoilMoisture", String(SensorValue));
  json.add("JamKirim", String(timeClient.getFormattedTime()));
  String jsonStr;
  json.toString(jsonStr, true);
  Serial.println(jsonStr);
  if (Firebase.updateNode(firebaseData, pathNode, json))
  {
    Serial.println("PASSED");
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  json.clear();

  //NGAMBIL DATA SENSOR
  if (Firebase.getJSON(firebaseData, daftarPerangkat)) {
    Serial.println("PASSED");
    //      Serial.println(hasiljson(firebaseData));
    //    Serial.println(firebaseData.jsonData());
    deserializeJson(doc, firebaseData.jsonData());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }


  const char* Node1_JamKirim = doc["Node1"]["JamKirim"]; // "17:22:13"
  int Node1_SoilMoisture = doc["Node1"]["SoilMoisture"]; // "1024"

  const char* Node2_JamKirim = doc["Node2"]["JamKirim"]; // "17:22:21"
  int Node2_SoilMoisture = doc["Node2"]["SoilMoisture"]; // "2"

  const char* Node3_JamKirim = doc["Node3"]["JamKirim"]; // "17:22:21"
  int Node3_SoilMoisture = doc["Node3"]["SoilMoisture"]; // "1024"

  const char* Node4_JamKirim = doc["Node4"]["JamKirim"]; // "19:53:31"
  int Node4_SoilMoisture = doc["Node4"]["SoilMoisture"]; // 676

  Sp = doc["WaterPump"]["SetPoint"]; // 676

  int averagesoil = (Node1_SoilMoisture + Node2_SoilMoisture + Node3_SoilMoisture + Node4_SoilMoisture) / 4; //rata-rata soil moisture
  Serial.print("Nilai Rata-rata soil moisture ");
  Serial.println(averagesoil);

  JsonObject WaterPump = doc["WaterPump"];
  const char* WaterPump_JamKirim = WaterPump["JamKirim"]; // "09.00"
  int WaterPump_KecepatanPompa = WaterPump["KecepatanPompa"]; // 50
  bool WaterPump_Otomatis = WaterPump["Otomatis"]; //
  bool WaterPump_PompaAktif = WaterPump["PompaAktif"]; //

  bool WaterPump_debug = WaterPump["debug"]; // false
  int WaterPump_debugtime = WaterPump["debugtime"]; // 5


  //jika mode pengujian pompa menyala
  //  if (WaterPump_debug == true) {
  //    int waktuawal = millis(); //9500
  //    while ((millis() - waktuawal) < (WaterPump_debugtime * 1000)) { //ktika, 00.06-00.05< 10
  //      Serial.print("pengujian pompa menyala dengan kecepatan ");
  //      Serial.println(WaterPump_KecepatanPompa);
  //      analogWrite(PIN_POMPA, WaterPump_KecepatanPompa);
  //      delay(1000);
  //    }
  //    Serial.println("pengujian pompa mati");
  //    analogWrite(PIN_POMPA, 0);
  //  }

  //mode normal
  //  else if (WaterPump_debug == false) {
  //    if (WaterPump_Otomatis == false) {
  //      Serial.println("pompa mode manual");
  //      if (WaterPump_PompaAktif == true) {
  //        Serial.print("pompa menyala dengan kecepatan ");
  //        Serial.println(WaterPump_KecepatanPompa);
  //        analogWrite(PIN_POMPA, WaterPump_KecepatanPompa);
  //      }
  //      else {
  //        Serial.println("pompa mati");
  //        analogWrite(PIN_POMPA, 0);
  //      }
  //    }
  //    else {
  // FUZZY LOGIC
  error_1 = error;
  error = averagesoil - Sp ;
  Derror = error - error_1;

  Serial.println("====Baca Data====");
  Serial.print("Kelembaban : ");
  Serial.print(C);
  Serial.println("*C");
  delay(1000);
  Serial.print("error :");
  Serial.println(error);
  Serial.print("Derror : ");
  Serial.println(Derror);

  //=====================//error//=========================
  //*Label Negatif*
  if (error <= -0.5) {
    M_negatif = 1 ;
    negatif = true;
  }
  /*else if (error >=-1.5 && error <-0.75){
    M_dingin=(error - (-1.5))/( (-0.75) - (-1.5));
    dingin=true;
    }*/
  else if (error > -0.5 && error <= 0) {
    M_negatif = (0 - (error)) / (0 - (-0.5));
    negatif = true;
  }
  /*else if (error <= -1.5){
    M_dingin = 1;
    dingin = true;
    }*/
  else {
    M_negatif = 0;
  }

  //*Label Zero*
  if (error == 0) {
    M_zero = 1 ;
    zero = true;
  }
  else if (error >= -0.5 && error < 0) {
    M_zero = (error - (-0.5)) / (0 - (-0.5));
    zero = true;
  }
  else if (error > 0 && error <= 0.5) {
    M_zero = (0.5 - (error)) / (0.5 - 0);
    zero = true;
  }
  else {
    M_zero = 0;
  }

  //*Label Positif*
  if (error >= 0.5) {
    M_positif = 1 ;
    positif = true;
  }
  else if (error >= 0 && error < 0.5) {
    M_positif = (error - 0) / (0.5 - 0);
    positif = true;
  }
  else {
    M_positif = 0;
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
  //*Label Negatif*
  if (Derror <= -0.5) {
    D_negatif = 1 ;
    Dnegatif = true;
  }
  /*else if (Derror >=-1.5 && Derror <-0.75){
    D_dingin=(Derror - (-1.5))/( (-0.75) - (-1.5));
    Ddingin=true;
    }*/
  else if (Derror > -0.5 && Derror <= 0) {
    D_negatif = (0 - (Derror)) / (0 - (-0.5));
    Dnegatif = true;
  }
  /*else if (Derror <= -1.5){
    D_dingin = 1;
    Ddingin = true;
    }*/
  else {
    D_negatif = 0;
  }

  //*Label Zero*
  if (Derror == 0) {
    D_zero = 1 ;
    Dzero = true;
  }
  else if (Derror >= -0.5 && Derror < 0) {
    D_zero = (Derror - (-0.5)) / (0 - (-0.5));
    Dzero = true;
  }
  else if (Derror > 0 && Derror <= 0.5) {
    D_zero = (0.5 - (Derror)) / (0.5 - 0);
    Dzero = true;
  }
  else {
    D_zero = 0;
  }

  //*Label Positif*
  if (Derror >= 0.5) {
    D_positif = 1 ;
    Dpositif = true;
  }
  else if (Derror >= 0 && Derror < 0.5) {
    D_positif = (Derror - 0) / (0.5 - 0);
    Dpositif = true;
  }
  else {
    D_positif = 0;
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
  Serial.print("M_negatif : ");
  Serial.println(M_negatif);
  Serial.print("M_zero : ");
  Serial.println(M_zero);
  Serial.print("M_positif : ");
  Serial.println(M_positif);
  delay(1000);

  Serial.println("===Derror===");
  Serial.print("D_negatif : ");
  Serial.println(D_negatif);
  Serial.print("D_zero : ");
  Serial.println(D_zero);
  Serial.print("D_positif : ");
  Serial.println(D_positif);
  delay(1000);


  Serial.println("pompa mode otomatis");
  //    }

  Serial.println("fungsi selesai");
  //  }
  defuzzyfikasi();
}

void defuzzyfikasi() {
  //===========Tabel Rule=============
  Serial.println("===Inference Rule & Implikasi Min===");
  if (negatif == true && Dnegatif == true) {
    rule1 = min(M_negatif, D_negatif);
    Serial.print("rule1 : ");
    Serial.println(rule1);
    delay(100);
  }
  if (negatif == true && Dzero == true) {
    rule2 = min(M_negatif, D_zero);
    Serial.print("rule2 : ");
    Serial.println(rule2);
    delay(100);
  }
  if (negatif == true && Dpositif == true) {
    rule3 = min(M_negatif, D_positif);
    Serial.print("rule3 : ");
    Serial.println(rule3);
    delay(100);
  }
  if (zero == true && Dnegatif == true) {
    rule4 = min(M_zero, D_negatif);
    Serial.print("rule4 : ");
    Serial.println(rule4);
    delay(100);
  }
  if (zero == true && Dzero == true) {
    rule5 = min(M_zero, D_zero);
    Serial.print("rule5 : ");
    Serial.println(rule5);
    delay(100);
  }
  if (zero == true && Dpositif == true) {
    rule6 = min(M_zero, D_positif);
    Serial.print("rule6 : ");
    Serial.println(rule6);
    delay(100);
  }
  if (positif == true && Dnegatif == true) {
    rule7 = min(M_positif, D_negatif);
    Serial.print("rule7 : ");
    Serial.println(rule7);
    delay(100);
  }
  if (positif == true && Dzero == true) {
    rule8 = min(M_positif, D_zero);
    Serial.print("rule8 : ");
    Serial.println(rule8);
    delay(100);
  }
  if (positif == true && Dpositif == true) {
    rule9 = min(M_positif, D_positif);
    Serial.print("rule9 : ");
    Serial.println(rule9);
    delay(100);
  }

  Serial.println("   ");
  Serial.println("===Fungsi Implikasi Max===");
  S = rule1;
  N = max(max(rule2, rule3), max(rule4, rule7));
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
  Serial.print(MoM);

  if (MoM == S) {
    MoM = 5;
    HS = 5;
    digitalWrite(PIN_POMPA, HIGH);
    Serial.println(HS);
    delay(5 * 1000);
  }
  if (MoM == N) {
    MoM = 3;
    HN = 3;
    digitalWrite(PIN_POMPA, HIGH);
    Serial.println(HN);
    delay(3 * 1000);
  }
  if (MoM == F) {
    MoM = 0;
    HF = 0;
    digitalWrite(PIN_POMPA, LOW);
    Serial.println(HF);
  }

  //======Selesai======
  Serial.println("Proses Selesai......");
  Serial.println("   ");
}
