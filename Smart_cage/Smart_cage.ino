#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <TelnetStream.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
#include "DecisionTree.h"

#ifndef STASSID
#define STASSID "Workshop Elka"
#define STAPSK  "gapakekabel"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

Eloquent::ML::Port::DecisionTree clf;

RF24 radio(D4, D8); // CE, CSN
#define DHTPIN D1
#define DHTTYPE DHT11
#define SensorPin A0
#define ONE_WIRE_BUS 6 //Pin Sensor Suhu DS18B20


float suhu;
float humi;
float Amonia;
String data1;
String node = "N1";

DHT dht(DHTPIN, DHTTYPE);

const byte address[6] = "00001";
int count = 0;

const unsigned long eventInterval = 10000;
unsigned long previousTime = 0;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  dht.begin();

  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }


  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("Node 1");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
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
  
  TelnetStream.begin();
}
void loop() {
  ArduinoOTA.handle();

  suhu = dht.readTemperature() - 3;
  humi = dht.readHumidity() - 20;
  Amonia = analogRead(A0);

  float data[3] = {suhu, humi, Amonia};
  int prio = clf.predict(data);

  TelnetStream.print("Suhu : ");
  TelnetStream.println(suhu);

  TelnetStream.print("Humi : ");
  TelnetStream.println(humi);

  TelnetStream.print("Amon : ");
  TelnetStream.println(Amonia);

  TelnetStream.print("Prio : ");
  TelnetStream.println(prio);
  delay(1000);

  unsigned long currentTime = millis();

  if (currentTime - previousTime >= eventInterval) {
    TelnetStream.println("Kirim data berdasarkan waktu");
    previousTime = currentTime;
    count++;

    data1 = "Data ke-" + String(count) + "S" + String(suhu) + "T" +
            String(Amonia) + "U" + String(humi) + "," + node;

    char data_send [data1.length() + 1];
    data1.toCharArray(data_send, data1.length() + 1);

    char text[data1.length() + 1];
    strcpy(text, data_send);

    radio.write(&text, sizeof(text));

    Serial.println(text);
  }

  if (prio == 1) {
    TelnetStream.println("Kirim data berdasarkan prioritas");
    count++;

    data1 = "Data ke-" + String(count) + "S" + String(suhu) + "T" +
            String(Amonia) + "U" + String(humi) + "," + node;

    char data_send [data1.length() + 1];
    data1.toCharArray(data_send, data1.length() + 1);

    char text[data1.length() + 1];
    strcpy(text, data_send);

    radio.write(&text, sizeof(text));

    Serial.println(text);
    delay(1000);
  }

}
