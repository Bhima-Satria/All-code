#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <RBDdimmer.h>
#include <DHT.h>

#define DHTPIN D3
#define DHTPIN2 D4
#define DHTTYPE DHT22

#define Relay1 D7
#define Relay2 D8
#define Serial  Serial

DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

float suhu;
float suhu2;
float hum;
float hum2;
const char* ssid = "Workshop Elka";//
const char* password = "gapakekabel";
//WiFiClient client;
char server[] = "192.168.43.63";


WiFiClient client;

#define zerocross D2 // for boards with CHANGEBLE input pins

dimmerLamp dimmer_1(D5, zerocross);
dimmerLamp dimmer_2(D6, zerocross);


void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
  dimmer_1.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE)
  dimmer_2.begin(NORMAL_MODE, ON);
  Serial.println("Incubator Program is starting...");
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  dht.begin();
  dht2.begin();
}

void loop()
{
  suhu = dht.readTemperature();
  suhu2 = dht2.readTemperature();
  hum = dht.readHumidity() + 4;
  hum2 = dht2.readHumidity() + 4;

  kirim(suhu, suhu2, hum, hum2);

  Serial.print("Suhu Room 1 : ");
  Serial.println(suhu);
  Serial.print("Kelembapan Room 1 : ");
  Serial.println(hum);
  Serial.println("----------------------------------");
  Serial.print("Suhu Room 2 : ");
  Serial.println(suhu2);
  Serial.print("Kelembapan Room 2 : ");
  Serial.println(hum2);
  Serial.println("----------------------------------");
  Serial.println("----------------------------------");


  /*(2 suhu 2 kelembapan, range sensor diganti 33-35)
    suhu = dht.readTemperature() + 2;
    suhu2 = dht2.readTemperature() + 2;*/

  if (suhu < 33)
  {
    digitalWrite(Relay1, LOW);
    dimmer_1.setPower(99);
  }
  else if (suhu <= 34)
  {
    digitalWrite(Relay1, LOW);
    dimmer_1.setPower(70);
  }
  else if (suhu >= 35)
  {
    digitalWrite(Relay1, HIGH);
    dimmer_1.setPower(20);
  }
  else if (suhu2 < 33)
  {
    digitalWrite(Relay2, LOW);
    dimmer_2.setPower(99);
  }
  else if (suhu2 <= 34)
  {
    digitalWrite(Relay2, LOW);
    dimmer_2.setPower(70);
  }
  else if (suhu2 >= 35)
  {
    digitalWrite(Relay2, HIGH);
    dimmer_2.setPower(20);
  }
  else
  {
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, LOW);
    dimmer_1.setPower(40);
    dimmer_2.setPower(40);
  }

  delay(1000);
}


void kirim(float temp, float temp2, float hum, float hum2) {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient

    http.addHeader("Content-Type", "text/plain");  //Specify content-type header


    String postStr = "http://192.168.1.91/inkubatorbayi/input.php?kelembapan=" + String(hum) + "&suhu=" + String(temp);
    String postStr2 = "http://192.168.1.91/inkubatorbayi/input2.php?kelembapan=" + String(hum2) + "&suhu=" + String(temp2);
    http.begin(postStr);      //Specify request destination
    int httpCode = http.POST(postStr);   //Send the request
    String payload = http.getString();                  //Get the response payload


    Serial.println("Data 1 Terkirim");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);

    http.begin(postStr2);      //Specify request destination
    int httpCode2 = http.POST(postStr2);   //Send the request
    String payload2 = http.getString();                  //Get the response payload


    Serial.println("Data 2 Terkirim");
    Serial.println(httpCode2);   //Print HTTP return code
    Serial.println(payload2);
    http.end();
    delay(1000);

  } else {

    Serial.println("Error in WiFi connection");

  }

}
