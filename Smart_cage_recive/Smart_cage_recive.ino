#include <ArduinoJson.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(D4, D8);

const byte address[6] = "00001";
unsigned long previousMillis = 0;
String cmd, data_count, data_from, str_S, str_T, str_U;
float Suhu, K_udara, K_amon;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Pengirim, Data Ke-, Suhu, Kelembapan, Amonia");
}

void loop() {
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");

  if (radio.available()) {
    char text[64] = "";
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
    K_amon    = str_T.toFloat();

    Serial.print("DATA, TIME,");
    Serial.print(data_from);
    Serial.print(",");
    Serial.print(data_count);
    Serial.print(",");
    Serial.print(Suhu);
    Serial.print(",");
    Serial.print(K_udara);
    Serial.print(",");
    Serial.print(K_amon);
    Serial.println(",");
    cmd = "";

  }
}
