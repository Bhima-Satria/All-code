#include <Arduino.h>
#line 1 "e:\\document\\Program Arduino\\jamur-device\\jamur-device.ino"
#include "IoT.h"
#include "fuzzy.h"
#include "sensor.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SEALEVELPRESSURE_HPA (1013.25)

#define RelayFan 12
#define RelayMist 13

float in_suhu = 0;
float in_humi = 0;
float in_tanah = 0;
float prediksi =0;

float light = 0;

int timeon = 0;

int lastWater = 0; //buat kapan terakhir nyiram
int timeSend = 0;  //nyatat waktu ngirim

String user = "Bhima"

const unsigned char logo_humi[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00,
    0x00, 0xff, 0xf0, 0x00, 0x01, 0xc0, 0x38, 0x00, 0x03, 0x80, 0x1c, 0x00, 0x06, 0x0f, 0xc6, 0x00,
    0x0e, 0xc1, 0xe7, 0x00, 0x0c, 0xe0, 0x73, 0x00, 0x09, 0xf0, 0x39, 0x80, 0x19, 0xb8, 0x19, 0x80,
    0x19, 0x9e, 0x19, 0x80, 0x19, 0x0f, 0x09, 0x80, 0x18, 0x0f, 0x00, 0x00, 0x18, 0x06, 0x00, 0x00,
    0x18, 0x00, 0x03, 0x00, 0x08, 0x00, 0x07, 0x80, 0x0c, 0x00, 0x07, 0xc0, 0x0e, 0x00, 0x0f, 0xc0,
    0x06, 0x00, 0x0f, 0xe0, 0x03, 0x80, 0x1f, 0xe0, 0x01, 0xc0, 0x1f, 0xf0, 0x00, 0xff, 0x9f, 0xf0,
    0x00, 0x3f, 0x9f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x07, 0x80};

const unsigned char logo_temp[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0xfc, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x0c, 0x30, 0x00,
    0x00, 0x0d, 0xbc, 0x00, 0x00, 0x0d, 0xbc, 0x00, 0x00, 0x0d, 0xb0, 0x00, 0x00, 0x0d, 0xb0, 0x00,
    0x00, 0x0d, 0xbc, 0x00, 0x00, 0x0d, 0xbc, 0x00, 0x00, 0x0d, 0xb0, 0x00, 0x00, 0x0d, 0xb0, 0x00,
    0x00, 0x1d, 0xb8, 0x00, 0x00, 0x31, 0x8c, 0x00, 0x00, 0x33, 0xcc, 0x00, 0x00, 0x67, 0xe6, 0x00,
    0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x67, 0xe6, 0x00, 0x00, 0x73, 0xce, 0x00,
    0x00, 0x30, 0x0c, 0x00, 0x00, 0x1c, 0x38, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x07, 0xe0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const unsigned char check[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x3f, 0xf8, 0x01, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0x87, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xef, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xfe, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0x80, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0xff, 0xff, 0x00, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfe, 0x01, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x03, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xf3, 0xff, 0xf8, 0x0f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xc1, 0xff, 0xf0, 0x0f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xc0, 0xff, 0xe0, 0x1f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0x80, 0xff, 0xc0, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xc0, 0x3f, 0x80, 0x7f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xe0, 0x1f, 0x00, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xf0, 0x0e, 0x01, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xf8, 0x0c, 0x03, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xfc, 0x00, 0x0f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xfe, 0x00, 0x0f, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0x00, 0x1f, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0x80, 0x3f, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xc0, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xe0, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xf1, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x3f, 0xf8, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

void setup()
{
  Serial.begin(115200);
  pinMode(RESETWIFIPIN, INPUT_PULLUP);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  for (int x = 0; x <= 100; x++)
  {
    oled.clearDisplay();
    oled.setTextColor(WHITE);
    oled.setTextSize(2);
    oled.setCursor(50, 25);
    oled.print(x);
    oled.println("%");
    oled.display();
  }

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.setCursor(25, 0);
  oled.println("waiting");
  oled.setCursor(50, 25);
  oled.println("for");
  oled.setCursor(5, 45);
  oled.println("connection");
  oled.display();
  autoconnectStart();
  initializeSensor();

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.drawBitmap(0, 0, check, 128, 64, WHITE);
  oled.display();

  Serial.println("connected...yeey :)");
  delay(1000);

  pinMode(RelayFan, OUTPUT);
  pinMode(RelayMist, OUTPUT);
  digitalWrite(RelayFan, LOW);
  digitalWrite(RelayMist, LOW);
}

void loop()
{
  autoconnectLoop();
  resetWiFi();
  Serial.println("pembacaan data sensor");

  get_setpoint(); //Ambil set point dari website_belum fix harus memperbarui fuzzy

  in_suhu = tempMeter();
  in_humi = humidMeter();
  light = luxMeter();
  setClock();

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.drawBitmap(10, 0, logo_temp, 32, 32, WHITE);
  oled.setCursor(33, 10);
  oled.print(" = ");
  int suhuOled = in_suhu;
  oled.print(suhuOled);
  oled.print((char)247);
  oled.println("C");
  oled.drawBitmap(10, 32, logo_humi, 28, 28, WHITE);
  oled.setCursor(33, 40);
  oled.print(" = ");
  int humiOled = in_humi;
  oled.print(humiOled);
  oled.println("%");
  oled.display();

  fuzzy(in_suhu, in_humi);


  int timecentroid = millis(); //waktu awal mulai

  if (Centroid > 3)
  {
    while ((Centroid * 1000) >= ((millis() - timecentroid)))
    {
      oled.clearDisplay();
      oled.setTextColor(WHITE);
      oled.setTextSize(2);
      oled.drawBitmap(10, 0, logo_temp, 32, 32, WHITE);
      oled.setCursor(33, 10);
      oled.print(" = ");
      int suhuOled = in_suhu;
      oled.print(suhuOled);
      oled.print((char)247);
      oled.println("C");
      oled.drawBitmap(10, 32, logo_humi, 28, 28, WHITE);
      oled.setCursor(33, 40);
      oled.print(" = ");
      int humiOled = in_humi;
      oled.print(humiOled);
      oled.println("%");
      oled.display();
      resetWiFi();
      if (Moist == true)
      {
        controlActuator(RelayFan, RelayMist, true, true);
      }
      else if (Fan == true)
      {
        controlActuator(RelayFan, RelayMist, true, false);
      }
      else
      {
        controlActuator(RelayFan, RelayMist, false, false);
      }
    }
  }

  controlActuator(RelayFan, RelayMist, false, false);

  if (timeSend == 0 || ((millis() - timeSend) / 1000 >= (60 * 5)))
  {
    send_data(in_suhu. in_udara, in_tanah, prediksi, Centroid, Tanam, user)
    timeSend = millis();
  }
}

void controlActuator(int GPIO_Fan, int GPIO_Mist, bool control_fan, bool control_mist)
{
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.drawBitmap(10, 0, logo_temp, 32, 32, WHITE);
  oled.setCursor(33, 10);
  oled.print(" = ");
  int suhuOled = in_suhu;
  oled.print(suhuOled);
  oled.print((char)247);
  oled.println("C");
  oled.drawBitmap(10, 32, logo_humi, 28, 28, WHITE);
  oled.setCursor(33, 40);
  oled.print(" = ");
  int humiOled = in_humi;
  oled.print(humiOled);
  oled.println("%");
  oled.display();
  digitalWrite(GPIO_Mist, control_fan);
  digitalWrite(GPIO_Fan, control_mist);
  if (control_fan && control_mist)
  {
    lastWater = setClock();
  }
}

