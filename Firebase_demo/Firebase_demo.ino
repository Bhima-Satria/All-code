#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

//1. Change the following info
#define FIREBASE_HOST "smartfarming-1997.firebaseio.com"
#define FIREBASE_AUTH "sMS2rhUKdfho0qGNdyR3DDULuKLBzaq4WgASZhtN"
#define WIFI_SSID "password"
#define WIFI_PASSWORD "012345678"

//2. Define FirebaseESP8266 data object for data sending and receiving
FirebaseData firebaseData;


void setup()
{

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
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


  //3. Set your Firebase info

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

}

void loop()
{
  int x = rand()%99;
  Serial.print ("Kirim Data : ");
  Serial.print (x);
  Serial.print("\t \t");
  Firebase.setInt(firebaseData,"/DHT",x);
  Serial.print("Ambil Data : ");
  Firebase.get(firebaseData, "/Data");
  Serial.println(firebaseData.stringData());
  delay(100);
  if( firebaseData.stringData() == "Aktif"){
    digitalWrite(LED_BUILTIN, LOW);
  } else if (firebaseData.stringData() == "Blink"){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
  }
  else digitalWrite(LED_BUILTIN, HIGH);
}
