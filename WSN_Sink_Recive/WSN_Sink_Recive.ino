#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(4, 5); // CE, CSN

const byte address[6] = "00001";
unsigned long previousMillis = 0;
String cmd, data_count, data_from, str_S, str_T, str_U;
float Suhu, K_udara, K_tanah;

float Data_node1[2];
float Data_node2[2];
float Data_node3[2];

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("SmartConfig done.");

  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected.");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.begin(9600);
}

void loop() {
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");

  unsigned long currentMillis = millis();
  unsigned long interval;
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

    interval = currentMillis - previousMillis;

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

    String postsyr = "http://192.168.1.81/iot/submitwsn.php?Id=" + data_from +
                     "&Suhu_wsn=" + str_S +
                     "&Udara_wsn=" + str_U +
                     "&Tanah_wsn=" + str_T +
                     "&User=Bhima";
                     
    Serial.println("===Kirim Data===");
    http.begin(postsyr);                 //Specify request destination
    int httpCode = http.POST(postsyr);   //Send the request
    String payload = http.getString();
    Serial.println("===Selesai===");

    if (data_from == "Node1") {
      Data_node1[0] = Suhu;
      Data_node1[1] = K_udara;
      Data_node1[2] = K_tanah;
    }
    else if (data_from == "Node2") {
      Data_node2[0] = Suhu;
      Data_node2[1] = K_udara;
      Data_node2[2] = K_tanah;
    }
    else if (data_from == "Node3") {
      Data_node3[0] = Suhu;
      Data_node3[1] = K_udara;
      Data_node3[2] = K_tanah;
    } else {
      for (int x = 3; x <= 3; x++) {
        Data_node1[x] = 0;
        Data_node2[x] = 0;
        Data_node3[x] = 0;
      }
    }

    cmd = "";
    previousMillis = currentMillis;
  }
}
