#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

int Id;
int Suhu;
int Udara;
int Tanah;

WiFiClient wificlient;
void setup() {

  Serial.begin(115200);
  WiFi.begin("Workshop Elka", "gapakekabel");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient

    for (int x = 1; x < 5; x++) {
      Suhu  = random(25, 29);
      Udara = random(0, 5);
      Tanah = random(6, 10);
      int Prediksi = random (50, 100);
      http.addHeader("Content-Type", "text/plain");  //Specify content-type header

        String postStr = "http://smartmonitor.id/submit.php?Suhu=" + String(Suhu) + "&Kekeruhan=" + String(Udara) + "&Ph=" + String(Tanah);
//      String postStr = "http://192.168.1.6/iot/submit.php?Suhu=" + String(Suhu) + "&Kelembaban=" + String(Udara) + "&KelembabanT=" + String(Tanah) + "&Prediksi=" + String(Prediksi);
      http.begin(wificlient, postStr);      //Specify request destination
      int httpCode = http.POST(postStr);   //Send the request
      String payload = http.getString();                  //Get the response payload


      Serial.println("Data Alat Terkirim");
//        Serial.printf("ID Alat= %d; Suhu= %d; Udara= %d; Tanah= %d; ", Id, Suhu, Udara, Tanah);
//      Serial.printf("Prediksi= %d; Suhu= %d; Udara= %d; Tanah= %d; ", Prediksi, Suhu, Udara, Tanah);
      Serial.println(httpCode);   //Print HTTP return code
      //      Serial.println(payload);
      http.end();
      delay(1800000);
    }

  } else {

    Serial.println("Error in WiFi connection");

  }

}
