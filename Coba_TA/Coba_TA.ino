#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

// Sensor 1
int sensorPin1 = 5;
int ledPin1 = 13;

// Sensor 2
int sensorPin2 = 4;
int ledPin2 = 12;

// Sensor 3
int sensorPin3 = 0;
int ledPin3 = 14;

void setup() {

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("Vinolia I No.10A", "1sampai2puluh");   //WiFi connection

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection");

  }

}

void loop() {

 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;    //Declare object of class HTTPClient
   int P = 3;
   int V = 6;
   int M = 9;
  
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   String postStr ="http://smartgardend3.000webhostapp.com/submit.php?Suhu="+String(P)+"&Kelembaban="+String(V)+"&FLC="+String(M);
                             /*postStr += P;
                             postStr +="&Kelembaban=";
                             postStr += V;
                             postStr +="&FLC=";
                             postStr += M;*/
   http.begin(postStr);      //Specify request destination
   int httpCode = http.POST(postStr);   //Send the request
   String payload = http.getString();                  //Get the response payload

   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload

   http.end();  //Close connection

 }else{

    Serial.println("Error in WiFi connection");   

 }

  delay(30000);  //Send a request every 30 seconds

}
