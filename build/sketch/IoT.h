#line 1 "e:\\document\\Program Arduino\\jamur-device\\IoT.h"
//autoconnect library
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
//autoconnect config
#include <AutoConnect.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "HTTPUpdateServer.h"
#define HOSTIDENTIFY "esp32"
#define mDNSUpdate(c) \
    do                \
    {                 \
    } while (0)
using WebServerClass = WebServer;
using HTTPUpdateServerClass = HTTPUpdateServer;
static const char *host = HOSTIDENTIFY "-webupdate";
#define HTTP_PORT 80
WebServerClass httpServer(HTTP_PORT);
#define USERNAME "user" //*< Replace the actual username you want */
#define PASSWORD "pass" //*< Replace the actual password you want */
#include <WiFiClientSecure.h>
HTTPUpdateServerClass httpUpdater;
AutoConnectAux update("/update", "Update");
AutoConnect portal(httpServer);
// --------------------------------------------------------------------------------

String ID_Tanaman;
String Tanaman;
String Suhu_web;
String Kelembapan_U;
String Kelembapan_T;
String Harga_K;
String Aktif;
String Tanam;

float setpoint_suhu = 0;
float setpoint_udara = 0;
float setpoint_tanah = 0;
float setpoint_harga = 0;

void autoconnectStart()
{
    httpUpdater.setup(&httpServer, USERNAME, PASSWORD);
    portal.join({update});
    if (portal.begin())
    {
        if (MDNS.begin(host))
        {
            MDNS.addService("http", "tcp", HTTP_PORT);
            Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
        }
        else
            Serial.println("Error setting up MDNS responder");
    }
}
void autoconnectLoop()
{
    mDNSUpdate(MDNS);
    portal.handleClient();
}

const int ChipID = ESP.getEfuseMac();
bool setclockchecked = false;
const String softwareVersion = "0.0.3";
#define RESETWIFIPIN 4

void resetWiFi()
{
    pinMode(RESETWIFIPIN, INPUT_PULLUP);

    switch (digitalRead(RESETWIFIPIN))
    {
    case 0:
        //reset WiFi
        break;
    }
}

int setClock()
{
    // config time (GMT +7,daylight saving, server 1, server2, server 3)
    if (setclockchecked == false)
    { //biar ga tiap dipanggil update ntp
        configTime(7 * 3600, 0, "id.pool.ntp.org", "pool.ntp.org", "time.nist.gov");
    }
    Serial.print("Waiting for NTP time sync: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.println(asctime(&timeinfo));
    time_t timeSinceEpoch = mktime(&timeinfo);
    Serial.println(timeSinceEpoch + (7 * 3600));
    return timeSinceEpoch + (7 * 3600);
}

void get_setpoint()
{
    for (int x = 1; x <= 3; x++)
    {
        http.begin("http://smartfarming.iotum.id/proses.php?Data=" + String(x));
        int httpCode = http.GET();
        if (WiFi.status() == WL_CONNECTED)
        {
            if (httpCode > 0)
            {
                DeserializationError error = deserializeJson(doc, http.getStream());
                if (error)
                {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.f_str());
                    return;
                }

                const char *ID = doc["ID"];
                const char *Data = doc["Data"];       // "Terong"
                const char *Udara = doc["Suhu"];      // "25"
                const char *K_Udara = doc["K_Udara"]; // "68"
                const char *K_Tanah = doc["K_Tanah"]; // "70"
                const char *Harga = doc["Harga"];     // "15"
                const char *Setatus = doc["Setatus"]; // "0"

                ID_Tanaman = ID;
                Tanaman = Data;
                Suhu_web = Udara;
                Kelembapan_U = K_Udara;
                Kelembapan_T = K_Tanah;
                Harga_K = Harga;
                Aktif = Setatus;

                if (Aktif == "1")
                {
                    setpoint_suhu = Suhu_web.toFloat();
                    setpoint_udara = Kelembapan_U.toFloat();
                    setpoint_tanah = Kelembapan_T.toFloat();
                    setpoint_harga = Harga_K.toFloat();
                    Tanam = Tanaman;
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
}

void send_data(float suhu, float udara, float tanah, float prediksi, float Z, String Ditanam, String User)
{
    String postsyr = "http://smartfarming.iotum.id/submit.php?Suhu=" + String(suhu) +
                           "&Kelembaban=" + String(udara) +
                           "&KelembabanT=" + String(tanah) +
                           "&Prediksi=" + String(prediksi) +
                           "&Fuzzy=" + String(Z) +
                           "&Tanaman=" + Ditanam +
                           "&User=" + User;

    http.begin(postsyr);                //Specify request destination
    int httpCode1 = http.POST(postsyr); //Send the request
    String payload1 = http.getString();
    digitalWrite(LED_BUILTIN, HIGH);
    http.end();
}