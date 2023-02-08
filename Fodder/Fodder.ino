#include <WiFi.h>
#include <HTTPClient.h>


const char *ssid = "your ssid";
const char *password = "your password";

// make timer from millis()
unsigned long timer = 0;
unsigned long interval = 28800000; // 8 hours in milliseconds

// Acatuator
#define Pump_1 2
#define Pump_2 4

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected..!");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());

    pinMode(Pump_1, OUTPUT);
    pinMode(Pump_2, OUTPUT);
}

void loop()
{
    if (millis() - timer > interval) // code means if the time is greater than 8 hours then run the code
    {
        timer = millis();
        digitalWrite(Pump_1, HIGH);
        digitalWrite(Pump_2, HIGH);
        delay(10000);
        digitalWrite(Pump_1, LOW);
        digitalWrite(Pump_2, LOW);
/*
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;
            http.begin("http://www.satu.com/"); // Specify destination for HTTP request
            int httpCode = http.GET();          // Send the actual GET request
            String payload = http.getString();  // Get the response payload
            Serial.println(httpCode);           // Print HTTP return code
            Serial.println(payload);            // Print request response payload
            http.end();                         // Close connection
        }
    }
*/
}

}