#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
 
// Gunakan serial sebagai monitor
#define USE_SERIAL Serial

const char* ssid = "Workshop Elka";
const char* password = "gapakekabel";
 
// Buat object Wifi
ESP8266WiFiMulti WiFiMulti;
 
// Buat object http
HTTPClient http;
 
// Deklarasikan variable untuk suhu
float vref = 3.3;
float resolusi = vref*100/1023;
float suhu;
String payload;
 
// Ini adalah alamat script (URL) yang kita pasang di web server
// Silahkan sesuaikan alamat IP dengan ip komputer anda atau alamat domain (bila di web hosting)
// '?suhu=' adalah adalah nama parameter yang akan dikirimkan ke script PHP 
 
String url = "http://192.168.0.192/arduino_mysql/Konten.php?nilai_sensor=";
 
//===============================
// SETUP
//===============================
 
void setup() {
 
    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(false);
 
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] Tunggu %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
 
  Serial.println();Serial.println(); //pemberian spasi
  Serial.print("Terhubung dengan Wifi.... ");
 // Koneksi dengan Wifi
  Serial.println(ssid);
 
  //prosedur pengkoneksian wifi
  WiFi.begin(ssid, password);
 
 //pengecekan status wifi
  while (WiFi.status() != WL_CONNECTED) //pengecekan kondisi koneksi wifi
  {delay(600);Serial.print(".");}
  Serial.println("");
  Serial.println("Sudah terkoneksi dengan wifi");
 
  //menuliskan alamat ip
  Serial.print("Alamat ip yang digunakan untuk pengaksesan: ");
  Serial.print("http://");Serial.print (WiFi.localIP());Serial.println("/"); 
 
}
 
//===============================
// LOOP
//===============================
 
void loop() {
    
    // Baca suhu dari pin analog
    //suhu = analogRead(A0);
    suhu = random(10,20); //suhu*resolusi;
    //----------------------
 
    // Cek apakah statusnya sudah terhubung
    if((WiFiMulti.run() == WL_CONNECTED)) {
 
        // Tambahkan nilai suhu pada URL yang sudah kita buat
        USE_SERIAL.print("[HTTP] Memulai...\n");
        http.begin( url + (String) suhu ); 
        
        // Mulai koneksi dengan metode GET
        USE_SERIAL.print("[HTTP] Melakukan GET ke server...\n");
        int httpCode = http.GET();
 
        // Periksa httpCode, akan bernilai negatif kalau error
        if(httpCode > 0) {
            
            // Tampilkan response http
            USE_SERIAL.printf("[HTTP] kode response GET: %d\n", httpCode);
 
            // Bila koneksi berhasil, baca data response dari server
            if(httpCode == HTTP_CODE_OK) {
                payload = http.getString();
                USE_SERIAL.println(payload);
            }
 
        } else {
 
            USE_SERIAL.printf("[HTTP] GET gagal, error: %s\n", http.errorToString(httpCode).c_str());
        }
 
        http.end();
    }
 
    delay(1000);
}
