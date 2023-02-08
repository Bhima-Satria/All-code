#include <ESP8266WiFi.h> //librray ESP8266
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "DHT.h"

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);


#define ON HIGH //Deklarasi variable ON sebagai kondisi HIGH
#define OFF LOW //Deklarasi Variable OFF sebagai kondisi LOW
#define LED2 D1 //Deklarasi PIN D1 untuk LED2
#define LED1 D0 //Deklarasi PIN D0 untuk LED1
 
const char* ssid = "OPPO A5"; // nama wifi kamu
const char* password = "987654321"; // password wifi kamu
 
int value1 = OFF, value2 = OFF; //membuat variable untuk control LED
 
WiFiServer server(80); //menentukan port HTTP yang digunakan untuk server
 
void setup() {
  Serial.begin(115200);  //membuka komunikasi serial
  delay(10);
  pinMode(LED1, OUTPUT); //inisialisasi pin LED 1 sebagai OUTPUT
  pinMode(LED2, OUTPUT); //inisialisasi pin LED 2 sebagai OUTPUT

  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");

  dht.begin();


  digitalWrite(LED1, OFF);
  digitalWrite(LED2, OFF);
 
//   // Program untuk koneksi ke Wifi
//  Serial.println();
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
// 
//  WiFi.begin(ssid, password);
// 
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
 
  // Program untuk memulai server
  server.begin();
  Serial.println("Server started");
 
  // Menampilkan alamat IP Server pada serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // fungsi untuk mengecek kondisi client sudah terkoneksi atau beleum
  delay(2000);
  
  float Kelembapan = rand()%80;
  float Suhu  = rand() %30;

  Serial.print("Kelembapan :");
  Serial.println(Kelembapan);
  Serial.print("Suhu :");
  Serial.println(Suhu);
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Kondisi menunggu client mengirim data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // membaca baris pertama pada request client
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 

//Logika jika ada request masuk dari client
  if(request.indexOf("/led=ON") != -1 ){
    digitalWrite(LED1, ON);   
    value1 = ON;
  }
  if(request.indexOf("/led=OFF") != -1 ){
    digitalWrite(LED1, OFF);
    value1 = OFF;   
  }

    if(request.indexOf("/led2=ON") != -1 ){
    digitalWrite(LED2, ON);   
    value2 = ON;
  }
  if(request.indexOf("/led2=OFF") != -1 ){
    digitalWrite(LED2, OFF);
    value2 = OFF;   
  }
  
// Script HTML untuk kontrol LED yang ditampilkan pada server
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset='utf-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<meta http-equiv='x-ua-compatible' content='ie=edge'>");
  client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css' integrity='sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ' crossorigin='anonymous'>");  
  client.println("</head>");
  client.println("<center>");
  client.println("<body>"); 
  client.println("<br><br>");
  client.println("<div class='col-md-6'>");
  client.println("<div class = 'container-fluid'>");
  client.println("<div class ='row'>"); 
  client.println("<div class ='col-md-6'>");

  client.println("<div class='card mb-3'>");
  client.println("<div class = 'card-header'>");
  client.println("<p>Kontrol Lampu Via Website dan Pembacaan Sensor<p>");
  client.println("</div>");
  client.println("<div class = 'card-body'>");
  client.println("<p> Menyalakan dan mematikan LED <p>");
  client.println("<a href=\"/led=ON\"\" type = 'button' class='btn btn-danger btn-block'>ON</a>");
  client.println("<a href=\"/led=OFF\"\" type = 'button' class='btn btn-primary btn-block'>OFF</a>");
  client.println("<p> Menyalakan dan mematikan LED2 <p>"); 
  client.println("<a href=\"/led2=ON\"\" type = 'button' class='btn btn-danger btn-block'>ON</a>");
  client.println("<a href=\"/led2=OFF\"\" type = 'button' class='btn btn-primary btn-block'>OFF</a>");
  client.println("<p> Pembacaan Sensor <p>");
  client.println("<p>Pembacaan Sensor Kelembapan :<p>");
  client.println(Kelembapan);
  client.println("<p>Pembacaan Sensor Suhu :<p>");
  client.println(Suhu);
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</center>");
  client.println("</html>"); //Akhir script HTML
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
