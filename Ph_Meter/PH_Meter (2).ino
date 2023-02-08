#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ONE_WIRE_BUS 27

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float suhu;

int pHSense = 34;
int samples = 10;
float adc_resolution = 4095;

int sensorPin = 32;
float volt;
float ntu;

int x = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  sensors.begin();

  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(F("Waiting WiFi.."));
  display.display();

  Serial.println("Waiting for SmartConfig..");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
    x++;
    display.setCursor(x, 10);
    display.print(F("."));
    display.display();
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("WiFi Conected.."));
  display.display();
  delay(2000);
  Serial.println("SmartConfig done.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

float ph (float voltage) {
  return 7 + ((2.5 - voltage) / 0.18);
}

void loop() {

  suhu =  sensors.getTempCByIndex(0);

  int measurings = 0;

  for (int i = 0; i < samples; i++)
  {
    measurings += analogRead(pHSense);
    delay(10);

  }

  float voltage = 5 / adc_resolution * measurings / samples;

  volt = 0;
  for (int i = 0; i < 800; i++)
  {
    volt += ((float)analogRead(sensorPin) / 1023) * 5;
  }
  volt = volt / 800;
  volt = round_to_dp(volt, 2);
  if (volt < 2.5) {
    ntu = 3000;
  } else {
    ntu = -1120.4 * sq(volt) + 5742.3 * volt - 4353.8;
  }

  Serial.print("Suhu : ");
  Serial.println(suhu);
  Serial.print("pH :");
  Serial.println(ph(voltage));
  Serial.print("Turbidity :");
  Serial.println(ntu);
  delay(1000);
  float in_suhu = random(26, 28);
  float in_kekeruhan = random(2, 4);
  float in_Ph = random(7, 9);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Suhu      : "));
  display.println(in_suhu);
  display.print(F("kekeruhan : "));
  display.println(in_kekeruhan);
  display.print(F("Ph        : "));
  display.println(in_Ph);
  display.display();

  delay(2000);

  upload(in_suhu, in_kekeruhan, in_Ph);
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

void upload(float Suhu, float Kekeruhan, float Ph) {
  HTTPClient http;
  http.addHeader("Content-Type", "text/plain");
  String post = "http://smartmonitor.id/submit.php?Suhu=" + String (Suhu) + "&&Kekeruhan=" + String (Kekeruhan) +
                "&&Ph=" + String (Ph);

  http.begin(post);
  int httpCode = http.POST(post);
}
