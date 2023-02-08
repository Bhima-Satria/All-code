#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 'logo-um-terbaru-2015-biru', 128x64px
const unsigned char logoUM [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x76, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x5f, 0xf7, 0xa0, 0x00, 0x03, 0x0c, 0x00, 0x00, 0xc0, 0x7c, 0x00, 0x07, 0xc0, 0x00,
  0x00, 0x01, 0xfd, 0xef, 0xf8, 0x00, 0x03, 0x1e, 0x00, 0x01, 0xe3, 0xff, 0x80, 0x3f, 0xf8, 0x00,
  0x00, 0x07, 0xfe, 0xee, 0x7e, 0x00, 0x03, 0x1e, 0x00, 0x01, 0xef, 0xff, 0xc0, 0xff, 0xfc, 0x00,
  0x00, 0x07, 0xff, 0x6e, 0xfe, 0x00, 0x03, 0x1e, 0x00, 0x01, 0xff, 0xff, 0xe1, 0xff, 0xfe, 0x00,
  0x00, 0x3f, 0xff, 0xfe, 0xdb, 0xc0, 0x03, 0x1e, 0x00, 0x01, 0xff, 0x83, 0xf3, 0xf8, 0x3f, 0x00,
  0x00, 0x7f, 0xfc, 0x03, 0xb3, 0xe0, 0x03, 0x1e, 0x00, 0x01, 0xfe, 0x00, 0xff, 0xe0, 0x0f, 0x80,
  0x00, 0xdf, 0xe0, 0x00, 0x77, 0xb0, 0x03, 0x1e, 0x00, 0x01, 0xfc, 0x00, 0x7f, 0xc0, 0x07, 0xc0,
  0x01, 0xc7, 0x80, 0x00, 0x1b, 0x58, 0x03, 0x1e, 0x00, 0x01, 0xf8, 0x00, 0x3f, 0x80, 0x03, 0xc0,
  0x01, 0xfe, 0x00, 0x00, 0x06, 0x38, 0x03, 0x1e, 0x00, 0x01, 0xf0, 0x00, 0x3f, 0x00, 0x03, 0xe0,
  0x03, 0xf4, 0x01, 0x08, 0x03, 0x78, 0x03, 0x1e, 0x00, 0x01, 0xf0, 0x00, 0x1f, 0x00, 0x01, 0xe0,
  0x06, 0x18, 0x06, 0x66, 0x01, 0xf6, 0x03, 0x1e, 0x00, 0x01, 0xe0, 0x00, 0x0e, 0x00, 0x01, 0xe0,
  0x07, 0xf0, 0x0e, 0x67, 0x00, 0xee, 0x03, 0x1e, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x07, 0xe0, 0x1c, 0xf7, 0x80, 0x5f, 0x03, 0x1e, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x0f, 0xc0, 0x5d, 0xfb, 0xa0, 0x3f, 0x03, 0x1e, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x19, 0xc0, 0xdd, 0xff, 0xb0, 0x3f, 0x83, 0x0f, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x16, 0x81, 0xde, 0xf7, 0xb8, 0x1f, 0x83, 0x0f, 0x00, 0x01, 0xe0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x3f, 0x81, 0xdf, 0x6f, 0xb8, 0x1f, 0xc3, 0x0f, 0x00, 0x03, 0xc0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x3f, 0x03, 0xef, 0xff, 0x78, 0x1f, 0xc3, 0x07, 0x80, 0x07, 0xc0, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x31, 0x03, 0xf9, 0xf1, 0xfc, 0x0f, 0x83, 0x07, 0xc0, 0x0f, 0x80, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x3f, 0x07, 0xfc, 0xf3, 0xfa, 0x0f, 0xc3, 0x03, 0xf0, 0x1f, 0x80, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x3f, 0x05, 0xfb, 0x0d, 0xfa, 0x0f, 0xc3, 0x01, 0xff, 0xff, 0x00, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x71, 0x0c, 0xec, 0xf2, 0x72, 0x0b, 0xc3, 0x00, 0xff, 0xfe, 0x00, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x65, 0x0e, 0x18, 0x09, 0x07, 0x0e, 0x63, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x1e, 0x00, 0x01, 0xe0,
  0x7e, 0x0f, 0xf2, 0x65, 0xff, 0x09, 0xe3, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x0e, 0x00, 0x00, 0xe0,
  0x7d, 0x0f, 0xf6, 0xf6, 0xff, 0x0e, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x61, 0x0f, 0xe6, 0x66, 0x7f, 0x08, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3f, 0x07, 0xe6, 0x66, 0x7e, 0x0f, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x2f, 0x07, 0xc4, 0x02, 0x3e, 0x0b, 0xc3, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3f, 0x03, 0x7c, 0x03, 0xd8, 0x0d, 0x83, 0x0f, 0xd0, 0x00, 0x60, 0x00, 0x00, 0x06, 0x00, 0x00,
  0x3f, 0x00, 0x3c, 0x01, 0xc0, 0x1e, 0xc3, 0x03, 0x14, 0x10, 0x60, 0x41, 0x14, 0x20, 0x80, 0x00,
  0x3a, 0x80, 0x10, 0x00, 0x00, 0x1f, 0xc3, 0x03, 0x1a, 0x68, 0x61, 0xb6, 0xdf, 0xb6, 0xdb, 0x60,
  0x13, 0x80, 0x00, 0x02, 0x00, 0x1f, 0x83, 0x03, 0x13, 0x4c, 0x61, 0x10, 0xd1, 0x96, 0x9a, 0x20,
  0x1f, 0xc0, 0x0c, 0xe6, 0x00, 0x27, 0x83, 0x03, 0x13, 0x40, 0x61, 0x06, 0xd1, 0x96, 0x9a, 0x20,
  0x0f, 0xc0, 0x0c, 0xef, 0x00, 0x79, 0x03, 0x03, 0x13, 0x4c, 0x61, 0x94, 0xd1, 0x96, 0x9b, 0x60,
  0x05, 0x60, 0x0c, 0xff, 0x00, 0x7f, 0x03, 0x01, 0x12, 0x38, 0x7c, 0xe7, 0x51, 0x96, 0x89, 0xa0,
  0x06, 0xf0, 0x0c, 0xff, 0x00, 0xde, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x60,
  0x06, 0xe8, 0x0d, 0x9d, 0x81, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0,
  0x01, 0xdc, 0x0f, 0x99, 0x83, 0x88, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xbe, 0x03, 0x18, 0x05, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xf3, 0x80, 0x00, 0x1e, 0xf8, 0x03, 0x00, 0x00, 0x08, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0xfa, 0xe0, 0x00, 0x71, 0xf0, 0x03, 0x00, 0x00, 0x08, 0xc0, 0x40, 0x00, 0x00, 0x48, 0x00,
  0x00, 0x79, 0xdc, 0x03, 0xbb, 0x60, 0x03, 0x00, 0x00, 0x08, 0xc2, 0x09, 0x19, 0x4c, 0x58, 0x20,
  0x00, 0x3b, 0xef, 0xfe, 0xdf, 0xc0, 0x03, 0x00, 0x00, 0x08, 0xdb, 0x69, 0x6d, 0xb2, 0x49, 0x20,
  0x00, 0x07, 0x6f, 0xff, 0x6f, 0x00, 0x03, 0x00, 0x00, 0x08, 0xd9, 0x69, 0x45, 0x9c, 0x49, 0x20,
  0x00, 0x07, 0xef, 0xff, 0xfa, 0x00, 0x03, 0x00, 0x00, 0x08, 0xd9, 0x66, 0x41, 0x06, 0x49, 0xc0,
  0x00, 0x01, 0xff, 0xff, 0xe8, 0x00, 0x03, 0x00, 0x00, 0x0c, 0xd9, 0x66, 0x65, 0x12, 0x48, 0xc0,
  0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x03, 0x00, 0x00, 0x07, 0x11, 0x06, 0x39, 0x0c, 0x4c, 0xc0,
  0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SensorPin A0          //pH meter Analog output to Arduino Analog Input 0
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10], temp;

const int Butt_Up = D5;
const int Butt_Down = D7;
const int Butt_Next = D6;
const int Butt_Back = D4;

#define Pump2 D3


int Up   = 0;
int Down = 0;
int Ok   = 0;
int Back = 0;

//Fuzzy Design
float error, Derror;
float E_Z, E_NS, E_N, E_PS, E_P;
float D_Z, D_NS, D_N, D_PS, D_P;
float r1, r2, r3, r4, r5, r6, r7, r8, r9, r10,
      r11, r12, r13, r14, r15, r16, r17, r18, r19, r20,
      r21, r22, r23, r24, r25;
float Vg, Vb, Gd, Nm, Bd;
float HVg, HVb, HGd, HNm, HBd;
float hsl1, hsl2;
float CoA;
float error_1;
float Sp = 7.50;
float phValue;

boolean Z   = false;
boolean N_S = false;
boolean N = false;
boolean P_S = false;
boolean P   = false;

boolean DZ   = false;
boolean DN_S = false;
boolean DN = false;
boolean DP_S = false;
boolean DP = false;

int timer = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Butt_Up, INPUT_PULLUP);
  pinMode(Butt_Down, INPUT_PULLUP);
  pinMode(Butt_Next, INPUT_PULLUP);
  pinMode(Butt_Back, INPUT_PULLUP);
  pinMode(SensorPin, INPUT);
  //  pinMode(Pump1, OUTPUT);
  pinMode(Pump2, OUTPUT);
  //  digitalWrite(Pump1, HIGH);
  digitalWrite(Pump2, HIGH);

  delay(1000);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay(); //for Clearing the display
  display.drawBitmap(0, 0, logoUM, 128, 64, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();

  Serial.println("Ready");
  //  Serial.print("IP address: ");
  //  Serial.println(WiFi.localIP());
  delay(2000);
}

void loop() {
//  menu();
    sensor();
    fuzzyfikasi();
    defuzzyfikasi();
    dsply();
    delay(3000);
}


void menu() {
  Up = digitalRead (Butt_Up);
  Down = digitalRead (Butt_Down);
  Ok = digitalRead (Butt_Next);
  Back = digitalRead(Butt_Back);

  unsigned long currentMillis = millis();


menu:
  while (1) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(BLACK, WHITE);
    display.print(F("Pengaturan"));
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.print(F("1. Tes Ph Air"));
    display.setCursor(0, 20);
    display.print(F("2. Kuras Air"));
    display.setCursor(0, 30);
    display.print(F("3. Atur Set-Point"));
    display.display();
    //    digitalWrite(Pump1, HIGH);
    digitalWrite(Pump2, HIGH);

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Down == LOW) {
      delay(200);
      goto menu1;
    }
  }

menu1:
  while (1) {
    timer=0;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.print(F("Pengaturan"));
    display.setCursor(0, 10);
    display.print(F(">1. Tes Ph Air"));
    display.setCursor(0, 20);
    display.print(F("2. Kuras Air"));
    display.setCursor(0, 30);
    display.print(F("3. Atur Set-Point"));
    display.display();

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Down == LOW) {
      delay(100);
      goto menu2;
    } else if (Up == LOW) {
      delay(200);
      goto menu;
    } else if (Ok == LOW) {
      delay(200);
      goto baca;
    }

  }

menu2:
  while (1) {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.print(F("Pengaturan"));
    display.setCursor(0, 10);
    display.print(F("1. Tes Ph Air"));
    display.setCursor(0, 20);
    display.print(F(">2. Kuras Air"));
    display.setCursor(0, 30);
    display.print(F("3. Atur Set-Point"));
    display.display();

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Down == LOW) {
      delay(100);
      goto menu3;
    } else if (Up == LOW) {
      delay(200);
      goto menu1;
    } else if (Ok == LOW) {
      delay(200);
      goto kuras;
    }
  }

menu3:
  while (1) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.print(F("Pengaturan"));
    display.setCursor(0, 10);
    display.print(F("1. Tes Ph Air"));
    display.setCursor(0, 20);
    display.print(F("2. Kuras Air"));
    display.setCursor(0, 30);
    display.print(F(">3. Atur Set-Point"));
    display.display();

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Up == LOW) {
      delay(200);
      goto menu2;
    } else if (Ok == LOW) {
      delay(200);
      goto setpoint;
    }
  }

setpoint:
  while (1) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.print(F("Atur Set-Point"));
    display.setCursor(0, 10);
    display.print("Nilai Ph : ");
    display.setCursor(60, 10);
    display.print(Sp);
    display.display();

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Up == LOW) {
      delay(200);
      Sp += 0.1;
    } else if (Down == LOW) {
      delay(200);
      Sp -= 0.1;
    } else if (Ok == LOW) {
      delay(200);
      goto baca;
    } else if (Back == LOW) {
      delay(200);
      goto menu;
    }

  }


baca:
  while (1) {

    sensor();
    fuzzyfikasi();
    defuzzyfikasi();
    dsply();

    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Back == LOW) {
      delay(100);
      goto menu;
    }
    else if (Ok == LOW) {
      delay(100);
      goto kuras;
    }
  }

kuras:
  while (1) {
    kuras();
    Up = digitalRead (Butt_Up);
    Down = digitalRead (Butt_Down);
    Ok = digitalRead (Butt_Next);
    Back = digitalRead(Butt_Back);

    if (Back == LOW) {
      delay(100);
      goto menu;
    }
  }
}

void kuras() {

  //  digitalWrite(Pump1, LOW);
  digitalWrite(Pump2, LOW);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.print(F("Pengurasan Air"));
  display.setCursor(0, 10);
  display.print(F("Timer : "));
  display.setCursor(60, 10);
  display.print(timer++);
  display.display();
  delay(1000);
}

void sensor() {
  for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i] = analogRead(SensorPin);
    delay(10);
  }
  for (int i = 0; i < 9; i++) //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  double dummy = 6.5;
  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];
  phValue = (float)avgValue * 5.0 / 1024 / 6;
  phValue = 3.5 * phValue;
//  error_1 = error;
//  error   = phValue - Sp;
//  Derror  = error - error_1;
    error  = 0.74;
    Derror = 0.07;
  Serial.println("==Error==");
  Serial.println(error);
  Serial.println(Derror);

}

void fuzzyfikasi() {

  //====Error=====
  //***Label Negative***
  if (error == -1) {
    E_N = 1;
    N   = true;
  }

  else if ( error < -1 && error > -1.5) {
    E_N = (error - (-1.5)) / (-1 - (-1.5));
    N   = true;
  }

  else if ( error > -1 && error < -0.5) {
    E_N = ( -0.5 - (error)) / (-0.5 - -1);
    N   = true;
  }


  //***Label Negative Small***
  if (error == -0.5) {
    E_NS  = 1;
    N_S   = true;
  }

  else if (error < -0.5 && error > -1) {
    E_NS  = (error - (-1)) / (-0.5 - (-1));
    N_S   = true;
  }

  else if (error > -0.5 && error < 0) {
    E_NS  = (0 - (error)) / (0 - (-0.5));
    N_S   = true;
  }


  //***Label Zero***
  if (error == 0) {
    E_Z   = 1;
    Z     = true;
  }

  else if (error < 0 && error > -0.5) {
    E_Z   = (error - (-0.5)) / (0 - (-0.5));
    Z     = true;
  }

  else if (error > 0 && error < 0.5) {
    E_Z   = (0.5 - error) / (0.5 - 0);
    Z     = true;
  }

  //***Label Positif Small***
  if (error == 0.5) {
    E_PS  = 1;
    P_S   = true;
  }

  else if (error > 0 && error < 0.5) {
    E_PS  = (error - 0) / (0.5 - 0);
    P_S   = true;
  }

  else if (error > 0.5 && error < 1) {
    E_PS  = (1 - error) / (1 - 0.5);
    P_S   = true;
  }

  //***Label Positif***
  if (error == 1) {
    E_P   = 1;
    P     = true;
  }

  else if (error > 0.5 && error < 1) {
    E_P   = (error - 0.5) / (1 - 0.5);
    P     = true;
  }

  else if (error > 1 && error < 1.5) {
    E_P   = (1.5 - error) / (1.5 - 1);
    P     = true;
  }


  //====Delta Error=====
  //***Label Negative***
  if (Derror == -1) {
    D_N = 1;
    DN   = true;
  }

  else if ( Derror < -1 && Derror > -1.5) {
    D_N = (Derror - (-1.5)) / (-1 - (-1.5));
    DN   = true;
  }

  else if ( Derror > -1 && Derror < -0.5) {
    D_N = ( -0.5 - (Derror)) / (-0.5 - -1);
    DN   = true;
  }


  //***Label Negative Small***
  if (Derror == -0.5) {
    D_NS  = 1;
    DN_S   = true;
  }

  else if (Derror < -0.5 && Derror > -1) {
    D_NS  = (Derror - (-1)) / (-0.5 - (-1));
    DN_S   = true;
  }

  else if (Derror > -0.5 && Derror < 0) {
    D_NS  = (0 - (Derror)) / (0 - (-0.5));
    DN_S   = true;
  }


  //***Label Zero***
  if (Derror == 0) {
    D_Z   = 1;
    DZ     = true;
  }

  else if (Derror < 0 && Derror > -0.5) {
    D_Z   = (Derror - (-0.5)) / (0 - (-0.5));
    DZ     = true;
  }

  else if (Derror > 0 && Derror < 0.5) {
    D_Z   = (0.5 - Derror) / (0.5 - 0);
    DZ     = true;
  }

  //***Label Positif Small***
  if (Derror == 0.5) {
    D_PS  = 1;
    DP_S   = true;
  }

  else if (Derror > 0 && Derror < 0.5) {
    D_PS  = (Derror - 0) / (0.5 - 0);
    DP_S   = true;
  }

  else if (Derror > 0.5 && Derror < 1) {
    D_PS  = (1 - Derror) / (1 - 0.5);
    DP_S   = true;
  }

  //***Label Positif***
  if (Derror == 1) {
    D_P   = 1;
    DP     = true;
  }

  else if (Derror > 0.5 && Derror < 1) {
    D_P   = (Derror - 0.5) / (1 - 0.5);
    DP     = true;
  }

  else if (Derror > 1 && Derror < 1.5) {
    D_P   = (1.5 - Derror) / (1.5 - 1);
    DP     = true;
  }

  //Inference Rule
  Serial.println("==Rule== \n");
  if (N == true && DN == true) {
    r1 = min(E_N, D_N);
    Serial.print("R1 : ");
    Serial.println(r1);
  }

  if (N == true && DN_S == true) {
    r2  = min(E_N, D_NS);
    Serial.print("R2 : ");
    Serial.println(r2);
  }

  if (N == true && DZ == true) {
    r3  = min(E_N, D_Z);
    Serial.print("R3 : ");
    Serial.println(r3);
  }

  if (N == true && DP_S == true) {
    r4  = min(E_N, D_PS);
    Serial.print("R4 : ");
    Serial.println(r4);
  }

  if (N == true && DP == true) {
    r5  = min(E_N, D_P);
    Serial.print("R5 : ");
    Serial.println(r5);
  }

  if (N_S == true && DN == true) {
    r6  = min(E_NS, D_N);
    Serial.print("R6 : ");
    Serial.println(r5);
  }

  if (N_S == true && DN_S == true) {
    r7  = min(E_NS, D_NS);
    Serial.print("R7 : ");
    Serial.println(r7);
  }

  if (N_S == true && DZ == true) {
    r8  = min(E_NS, D_Z);
    Serial.print("R8 : ");
    Serial.println(r8);
  }

  if (N_S == true && DP_S == true) {
    r9  = min(E_NS, D_PS);
    Serial.print("R9 : ");
    Serial.println(r9);
  }

  if (N_S == true && DP == true) {
    r10 = min(E_NS, D_P);
    Serial.print("R10 : ");
    Serial.println(r10);
  }

  if (Z == true && DN == true) {
    r11 = min(E_Z, D_N);
    Serial.print("R11 : ");
    Serial.println(r11);
  }

  if (Z == true && DN_S == true) {
    r12 = min(E_Z, D_NS);
    Serial.print("R12 : ");
    Serial.println(r12);
  }

  if (Z == true && DZ == true) {
    r13 = min(E_Z, D_Z);
    Serial.print("R13 : ");
    Serial.println(r13);
  }

  if (Z == true && DP_S == true) {
    r14 = min(E_Z, D_PS);
    Serial.print("R14 : ");
    Serial.println(r14);
  }

  if (Z == true && DP == true) {
    r15 = min(E_Z, D_P);
    Serial.print("R15 : ");
    Serial.println(r15);
  }

  if (P_S == true && DN == true) {
    r16 = min(E_PS, D_N);
    Serial.print("R16 : ");
    Serial.println(r16);
  }

  if (P_S == true && DN_S == true) {
    r17 = min(E_PS, D_NS);
    Serial.print("R17 : ");
    Serial.println(r17);
  }

  if (P_S == true && DZ == true) {
    r18 = min(E_PS, D_Z);
    Serial.print("R18 : ");
    Serial.println(r18);
  }

  if (P_S == true && DP_S == true) {
    r19 = min(E_PS, D_PS);
    Serial.print("R19 : ");
    Serial.println(r19);
  }

  if (P_S == true && DP == true) {
    r20 = min(E_PS, D_P);
    Serial.print("R20 : ");
    Serial.println(r20);
  }

  if (P == true && DN == true) {
    r21 = min(E_P, D_N);
    Serial.print("R21 : ");
    Serial.println(r21);
  }

  if (P == true && DN_S == true) {
    r22 = min(E_P, D_NS);
    Serial.print("R22 : ");
    Serial.println(r22);
  }

  if (P == true && DZ == true) {
    r23 = min(E_P, D_Z);
    Serial.print("R23 : ");
    Serial.println(r23);
  }

  if (P == true && DP_S == true) {
    r24 = min(E_P, D_PS);
    Serial.print("R24 : ");
    Serial.println(r24);
  }

  if (P == true && DP == true) {
    r25 = min(E_PS, D_P);
    Serial.print("R20 : ");
    Serial.println(r20);
  }

  Serial.println("==Implikasi Max==");
  Vg = r13;
  Vb = max(max(max(max(r1, r2), max(r4, r5)), max(max(r6, r10), max(r16, r20))), max(max(r21, r22), max(r24, r25)));
  Gd  = r14;
  Nm  = max(max(r8, r12), r18);
  Bd  = max(max(max(r3, r7), max(r9, r11)), max(max(r15, r17), max(r19, r23)));
  Serial.println(Vg);
  Serial.println(Vb);
  Serial.println(Gd);
  Serial.println(Nm);
  Serial.println(Bd);
}

void defuzzyfikasi() {
  Serial.println("Defuzzyfikasi");
  HVg = (Vg * (80 + 82.5 + 85 + 87.5 + 90 + 92.5 + 95 + 97.5 + 100));
  HVb = (Vb * (0 + 2.5 + 5 + 7.5 + 10 + 12.5 + 15 + 17.5 + 20 + 22.5 + 25 + 27.5 + 30 + 32.5 + 35 + 37.5 + 40 + 42.5 + 45 + 47.5 + 50 + 52.5 + 55 + 57.5 + 60));
  HGd = (Gd * (70 + 72.5 + 75 + 77.5 + 80 + 82.5 + 85 + 87.5 + 90));
  HNm = (Nm * (60 + 62.5 + 65 + 67.5 + 70 + 72.5 + 75 + 77.5 + 80));
  HBd = (Bd * (50 + 52.5 + 55 + 57.5 + 60 + 62.5 + 65 + 67.5 + 70));
  Serial.println("==Derajat Keanggotaan Output==");
  Serial.println(HVg);
  Serial.println(HVb);
  Serial.println(HGd);
  Serial.println(HNm);
  Serial.println(HBd);
  hsl1 = (HVg + HVb + HGd + HNm + HBd);
  hsl2 = ((Vg * 9) + (Vb * 25) + (Gd * 9) + (Nm * 9) + (Bd * 9));
  CoA = hsl1 / hsl2;
  Serial.println("==Hasil Defuzyfikasi==");
  Serial.println(hsl1);
  Serial.println(hsl2);
  Serial.println(CoA);
}

void dsply() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print(F("Tes Kualitas Air"));
  display.setCursor(0, 10);
  display.print(F("Ph  : "));
  display.setCursor(30, 10);
  display.print(phValue);

  display.setCursor(0, 20);
  display.print(F("Air : "));
  display.setCursor(30, 20);
  display.print(CoA);
  display.setCursor(65, 20);
  display.print(F("%"));

  //Derror
  display.setCursor(0, 30);
  display.print("Er  : ");
  display.setCursor(30, 30);
  display.print(error);
  display.setCursor(0, 40);
  display.print("De  : ");
  display.setCursor(30, 40);
  display.print(Derror);
  display.setCursor(0, 50);
  display.print("Tekan Ok untuk kuras");

  display.display();
}
