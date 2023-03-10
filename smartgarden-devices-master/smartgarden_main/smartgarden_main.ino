#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "fuzzy.h"
#include "IoT.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SEALEVELPRESSURE_HPA (1013.25)

#define RelayA D7
#define RelayB D8

Adafruit_BME280 bme;
float in_suhu = 0;
float in_humi = 0;
int timeon = 0;

const unsigned char logo[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x80, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xc0, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x01, 0xe1, 0xc0, 0x00, 0x00, 0x00, 0x07, 0x18, 0x00,
    0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xc3, 0x80, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00,
    0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xc3, 0x30, 0x00, 0x00, 0x08, 0xfe, 0x00, 0x00,
    0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x86, 0x39, 0x80, 0x38, 0x0d, 0xce, 0x00, 0x00,
    0x00, 0x03, 0xc3, 0xf0, 0x60, 0x00, 0x00, 0x07, 0x00, 0x39, 0xcc, 0x3c, 0x1d, 0x9c, 0x00, 0x00,
    0x00, 0x03, 0xf7, 0xf1, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x71, 0xce, 0x7e, 0x1d, 0x9c, 0x00, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0x38, 0x73, 0x8e, 0xf3, 0x3c, 0x98, 0x00, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xe4, 0x63, 0x9c, 0xe7, 0x38, 0x38, 0x00, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0x86, 0xe3, 0x9c, 0xe7, 0x38, 0x38, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x0e, 0xe3, 0x1d, 0xc7, 0x78, 0x30, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x0c, 0xe3, 0x99, 0xc7, 0x70, 0x30, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x1c, 0xe3, 0x19, 0xc7, 0x70, 0x30, 0x00, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7c, 0x01, 0x18, 0xc3, 0x20, 0x30, 0x00, 0x00,
    0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x7c, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xf8, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x18, 0x0e, 0x00, 0x80, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0xc0, 0xc3, 0x01, 0x98, 0x8e, 0x71, 0xcc, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xc7, 0xe7, 0x81, 0xf9, 0xfc, 0xf9, 0xce, 0x00,
    0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0x87, 0xef, 0x83, 0xb3, 0xfc, 0xe9, 0xce, 0x00,
    0x00, 0x01, 0xf7, 0xfb, 0xe0, 0x00, 0x00, 0x03, 0x81, 0xcf, 0x63, 0x93, 0xb9, 0xcb, 0x9e, 0x00,
    0x00, 0x03, 0xc3, 0xf0, 0xe0, 0x00, 0x00, 0x07, 0x03, 0x9e, 0xf7, 0x97, 0x39, 0xd3, 0x9c, 0x00,
    0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x03, 0x9c, 0xf7, 0x07, 0x39, 0x83, 0x1c, 0x00,
    0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x07, 0x1c, 0xe7, 0x07, 0x73, 0x87, 0x3c, 0x00,
    0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x38, 0xef, 0x06, 0x73, 0x87, 0x38, 0x00,
    0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x18, 0xee, 0x06, 0x33, 0x87, 0x38, 0x00,
    0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x01, 0x3e, 0x18, 0x66, 0x02, 0x21, 0x83, 0x18, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xf6, 0x00, 0x00, 0x00, 0x10, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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
  delay(1000);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.drawBitmap(0, 0, logo, 128, 64, WHITE);
  oled.display();
  delay(2000);

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

  WiFi.mode(WIFI_STA);
  WiFiManager wifiManager;
  // wifiManager.resetSettings();
  //  String APnameString = "SmartGarden-"+ String(ESP.getChipId(),HEX);
  //  char* APname;
  //  APnameString.toCharArray(APname,50);
  wifiManager.autoConnect("SmartGarden", "82668266");

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.drawBitmap(0, 0, check, 128, 64, WHITE);
  oled.display();

  Serial.println("connected...yeey :)");
  delay(1000);

  pinMode(RelayA, OUTPUT);
  pinMode(RelayB, OUTPUT);
  digitalWrite(RelayA, LOW);
  digitalWrite(RelayB, LOW);
  bme.begin(0x76);
}

void loop()
{
  Serial.println("pembacaan data sensor");
  in_suhu = bme.readTemperature();
  in_humi = bme.readHumidity();

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

  while ((Centroid * 1000) >= ((millis() - timecentroid)))
  { ///sambil nunggu centroid, update LCD
    digitalWrite(RelayA, HIGH);
    digitalWrite(RelayB, HIGH);
    in_suhu = bme.readTemperature();
    in_humi = bme.readHumidity();
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
  }

  digitalWrite(RelayA, LOW);
  digitalWrite(RelayB, LOW);
  timeon = millis();
  if (timeon == 0 || ((millis() - timeon) / 1000) >= (60 * 5))
  {
    timeon = millis();
    sendData(in_humi, in_suhu);
  }
}
