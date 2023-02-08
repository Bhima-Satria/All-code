#include "fuzzy.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//const long interval = 10000; //5000
//unsigned long previousMillis = 0;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RF24 radio(4, 5); // CE, CSN

const byte address[6] = "00001";
String cmd, data_count, data_from, str_S, str_T, str_U;
float Suhu, K_udara, K_tanah;

float Data_node1_S = 0;
float Data_node1_U = 0;
float Data_node1_T = 0;
float Data_node2_S = 0;
float Data_node2_U = 0;
float Data_node2_T = 0;
float Data_node3_S = 0;
float Data_node3_U = 0;
float Data_node3_T = 0;

String ID_Tanaman;
String Tanaman;
String Suhu_web;
String Kelembapan_U;
String Kelembapan_T;
String Harga_K;
String Aktif;
String Tanam;

float website_suhu  = 0;
float website_udara = 0;
float website_tanah = 0;
float website_harga = 0;

float input_suhu  = 0;
float input_udara = 0;
float input_tanah = 0;

float wsn_suhu  = 0;
float wsn_udara = 0;
float wsn_tanah = 0;

float error_suhu = 0;
float error_tanah = 0;
float error_udara = 0;

int x = 0;

void setup () {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(F("Waiting WiFi.."));
  display.display();

  Serial.println("Waiting for SmartConfig..");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
    x++;
    display.setCursor(x, 10);
    display.print(F("."));
    display.display();
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("WiFi Conected.."));
  display.display();
  delay(2000);
  Serial.println("SmartConfig done.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");
  StaticJsonDocument<2048> doc;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40, 0);
  display.println(F("Stand By"));
  display.setCursor(0, 20);
  display.print(F("Tanaman  : "));
  display.println(Tanam);
  display.print(F("Harga psr: "));
  display.print(website_harga);
  display.println(" K");
  display.print(F("Monetize : "));
  display.print(prediksi);
  display.println(" K");
  display.display();

tunggu_node:
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    cmd += text;
    int prefix_1 = cmd.indexOf("S");
    int prefix_2 = cmd.indexOf("T");
    int prefix_3 = cmd.indexOf("U");
    int prefix_4 = cmd.lastIndexOf(",");

    data_count = cmd.substring(0, prefix_1);
    str_S      = cmd.substring(prefix_1 + 1, prefix_2);
    str_T      = cmd.substring(prefix_2 + 1, prefix_3);
    str_U      = cmd.substring(prefix_3 + 1, prefix_4);
    data_from  = cmd.substring(prefix_4 + 1);

    Suhu       = str_S.toFloat();
    K_udara    = str_U.toFloat();
    K_tanah    = str_T.toFloat();

    Serial.print("Form : ");
    Serial.println(data_from);
    Serial.print("Data : ");
    Serial.println(data_count);
    Serial.print("Temp : ");
    Serial.println(Suhu);
    Serial.print("Soil : ");
    Serial.println(K_tanah);
    Serial.print("Humi : ");
    Serial.println(K_udara);

    if (data_from == "Node1") {
      Data_node1_S = Suhu;
      Data_node1_U = K_udara;
      Data_node1_T = K_tanah;
      display.clearDisplay();
      display.setCursor(40, 0);
      display.println(F("Node 1"));
      display.setCursor(0, 20);
      display.print(F("Suhu    : "));
      display.println(Data_node1_S);
      display.print(F("K_Udara : "));
      display.println(Data_node1_U);
      display.print(F("K_Tanah : "));
      display.println(Data_node1_T);
      display.display();
      delay(2000);
    }
    else if (data_from == "Node2") {
      Data_node2_S = Suhu;
      Data_node2_U = K_udara;
      Data_node2_T = K_tanah;
      display.clearDisplay();
      display.setCursor(40, 0);
      display.println(F("Node 2"));
      display.setCursor(0, 20);
      display.print(F("Suhu    : "));
      display.println(Data_node2_S);
      display.print(F("K_Udara : "));
      display.println(Data_node2_U);
      display.print(F("K_Tanah : "));
      display.println(Data_node2_T);
      display.display();
      delay(2000);
    }
    else if (data_from == "Node3") {
      Data_node3_S = Suhu;
      Data_node3_U = K_udara;
      Data_node3_T = K_tanah;
      display.clearDisplay();
      display.setCursor(40, 0);
      display.println(F("Node 3"));
      display.setCursor(0, 20);
      display.print(F("Suhu    : "));
      display.println(Data_node3_S);
      display.print(F("K_Udara : "));
      display.println(Data_node3_U);
      display.print(F("K_Tanah : "));
      display.println(Data_node3_T);
      display.display();
      delay(2000);
    }

    String postsyr = "http://smartfarming.iotum.id/submitwsn.php?Id=" + data_from +
                     "&Suhu_wsn=" + str_S +
                     "&Udara_wsn=" + str_U +
                     "&Tanah_wsn=" + str_T +
                     "&User=Bhima";

    Serial.println("===Kirim Data===");
    http.begin(postsyr);                 //Specify request destination
    int httpCode = http.POST(postsyr);   //Send the request
    String payload = http.getString();
    Serial.println("===Selesai===");

    cmd = "";
    if (Data_node1_S < 1 || Data_node2_S < 1 || Data_node3_S < 1 ) {
      Serial.println("Tunggu Node Lain");
      delay(1000);
      goto tunggu_node;
    } else
      for (int x = 1; x <= 3; x++) {
        http.begin("http://smartfarming.iotum.id/proses.php?Data=" + String(x));
        int httpCode = http.GET();
        if (WiFi.status() == WL_CONNECTED) {
          if (httpCode > 0) {
            DeserializationError error = deserializeJson(doc, http.getStream());
            if (error) {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.f_str());
              return;
            }

            const char* ID = doc["ID"];
            const char* Data = doc["Data"]; // "Terong"
            const char* Udara = doc["Suhu"]; // "25"
            const char* K_Udara = doc["K_Udara"]; // "68"
            const char* K_Tanah = doc["K_Tanah"]; // "70"
            const char* Harga = doc["Harga"]; // "15"
            const char* Setatus = doc["Setatus"]; // "0"

            ID_Tanaman   = ID;
            Tanaman      = Data;
            Suhu_web     = Udara;
            Kelembapan_U = K_Udara;
            Kelembapan_T = K_Tanah;
            Harga_K      = Harga;
            Aktif        = Setatus;

            if (ID_Tanaman == "1" && Aktif == "1") {
              website_suhu  = Suhu_web.toFloat();
              website_udara = Kelembapan_U.toFloat();
              website_tanah = Kelembapan_T.toFloat();
              website_harga = Harga_K.toFloat();
              Tanam         = Tanaman;
              Serial.println("=== Data WEB ===");
              Serial.print("Menaman: ");
              Serial.println(Tanaman);
              Serial.print("Suhu: ");
              Serial.println(website_suhu);
              Serial.print("Udara: ");
              Serial.println(website_udara);
              Serial.print("Tanah: ");
              Serial.println(website_tanah);
              Serial.print("Harga: ");
              Serial.println(website_harga);
              digitalWrite(LED_BUILTIN, LOW);


            } else if (ID_Tanaman == "2" && Aktif == "1") {
              website_suhu  = Suhu_web.toFloat();
              website_udara = Kelembapan_U.toFloat();
              website_tanah = Kelembapan_T.toFloat();
              website_harga = Harga_K.toFloat();
              Tanam         = Tanaman;
              Serial.println("=== Data WEB ===");
              Serial.print("Menaman: ");
              Serial.println(Tanaman);
              Serial.print("Suhu: ");
              Serial.println(website_suhu);
              Serial.print("Udara: ");
              Serial.println(website_udara);
              Serial.print("Tanah: ");
              Serial.println(website_tanah);
              Serial.print("Harga: ");
              Serial.println(website_harga);
              digitalWrite(LED_BUILTIN, LOW);


            } else if (ID_Tanaman == "3" && Aktif == "1") {
              website_suhu  = Suhu_web.toFloat();
              website_udara = Kelembapan_U.toFloat();
              website_tanah = Kelembapan_T.toFloat();
              website_harga = Harga_K.toFloat();
              Tanam         = Tanaman;
              Serial.println("=== Data WEB ===");
              Serial.print("Menaman: ");
              Serial.println(Tanaman);
              Serial.print("Suhu: ");
              Serial.println(website_suhu);
              Serial.print("Udara: ");
              Serial.println(website_udara);
              Serial.print("Tanah: ");
              Serial.println(website_tanah);
              Serial.print("Harga: ");
              Serial.println(website_harga);
              digitalWrite(LED_BUILTIN, LOW);
            }
          }
        }
      }

    // fuzzy sistem
    wsn_suhu  = ((Data_node1_S + Data_node2_S + Data_node3_S) / 3);
    wsn_udara = ((Data_node1_U + Data_node2_U + Data_node3_U) / 3);
    wsn_tanah = ((Data_node1_T + Data_node2_T + Data_node3_T) / 3);

    error_suhu = wsn_suhu - website_suhu;
    error_udara = wsn_udara - website_udara;
    error_tanah = wsn_tanah - website_tanah;

    Serial.println("=== Data WSN ===");
    Serial.print("WSN_Suhu : ");
    Serial.println(wsn_suhu);
    Serial.print("WSN_Udara : ");
    Serial.println(wsn_udara);
    Serial.print("WSN_Tanah : ");
    Serial.println(wsn_tanah);

    fuzzy(error_suhu, error_udara, error_tanah, website_harga);
    //kirim data ke server
    String postsyr_fuzzy = "http://smartfarming.iotum.id/submit.php?Suhu=" + String(wsn_suhu) +
                           "&Kelembaban=" + String(wsn_udara) +
                           "&KelembabanT=" + String(wsn_tanah) +
                           "&Prediksi=" + String(prediksi) +
                           "&Fuzzy=" + String(Z) +
                           "&Tanaman=" + Tanam +
                           "&User=Bhima";

    http.begin(postsyr_fuzzy);                 //Specify request destination
    int httpCode1 = http.POST(postsyr_fuzzy);   //Send the request
    String payload1 = http.getString();
    digitalWrite(LED_BUILTIN, HIGH);
    http.end();
    delay(2000);
    Data_node1_S = 0;
    Data_node1_U = 0;
    Data_node1_T = 0;
    Data_node2_S = 0;
    Data_node2_U = 0;
    Data_node2_T = 0;
    Data_node3_S = 0;
    Data_node3_U = 0;
    Data_node3_T = 0;
    delay(5000);
  }
  
  delay(2000);
  display.clearDisplay();
  display.setCursor(40, 0);
  display.println(F("Rata-rata"));
  display.setCursor(0, 20);
  display.print(F("Suhu    : "));
  display.print(wsn_suhu);
  display.println(" C");
  display.print(F("K_Udara : "));
  display.print(wsn_udara);
  display.println(F(" %"));
  display.print(F("K_Tanah : "));
  display.print(wsn_tanah);
  display.println(F(" %"));
  display.print(F("Fuzzy   : "));
  display.print(Z);
  display.println(F(" %"));
  display.print(F("Monetize: "));
  display.print(prediksi);
  display.println(" K");
  display.display();
  delay(2000);
}
