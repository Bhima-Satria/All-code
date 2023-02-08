#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIN_BTN_OKR 3

/*
  ATUR LIMIT SENSOR PADA limit_value DIBAWAH INI MULAI DARI SENSOR PALING KIRI HINGGA PALING KANAN
  CARI NILAI TERTINGGI PEMBACAAN SENSOR SAAT SENSOR TERKENA GARIS/BIDANG HITAM, DAN
  CARI NILAI TERENDAH PEMBACAAN SENSOR SAAT SENSOR TERKANA GARIS/BIDANG PUTIH

  RUMUS LIMIT = (PEMBACAAN TERTINGGI + PEMBACAAN TERENDAH) / 2

  UNTUK MENJALANKAN ROBOT GUNAKAN TOMBOL CANCEL (OKR)
*/

int limit_value[14] = {600, 600, 600, 750, 600, 800, 750, 600, 600, 600, 600, 600, 600, 600};

/*
 
  PROGRAM INI MENGGUNAKAN KENDALI Kp dan Kd
  ATUR PARAMETERNILAI KP, KD, KECEPATAN ROBOT, MIN SPEED, DAN MAX SPEED DIBAWAH INI

*/

int Kp = 7;
int Kd = 18;
int run_speed = 60;
int max_speed = 250;
int min_speed = -150;


#define OLED_RESET     4
Adafruit_SSD1306 lcd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int adcValue[14];
char buff[100];

#define PIN_PWM_MOTOR_L       14
#define PIN_DIR_MOTOR_L       15

#define PIN_PWM_MOTOR_R       13
#define PIN_DIR_MOTOR_R       12

void setup() {
  Serial.begin(9600);
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  lcd.clearDisplay();
  pinMode(PIN_DIR_MOTOR_L, OUTPUT);
  pinMode(PIN_PWM_MOTOR_L, OUTPUT);
  pinMode(PIN_DIR_MOTOR_R, OUTPUT);
  pinMode(PIN_PWM_MOTOR_R, OUTPUT);
  pinMode(PIN_BTN_OKR, INPUT_PULLUP);

  lcd.setTextColor(WHITE);
  lcd.setRotation(2);
  lcd.clearDisplay();
  lcd.display();

  setMotor(0, 0);

  lcd.setCursor(34, 15);
  lcd.print(F("HELLO WORLD"));
  lcd.setCursor(0, 30);
  lcd.print(F("ICHIBOT LINE FOLLOWER"));
  lcd.setCursor(25, 45);
  lcd.print(F("WWW.ICHIBOT.ID"));
  lcd.display();

  delay(1000);
  lcd.clearDisplay();
  lcd.display();
}

void loop() {
  display_sensor();
  if (digitalRead(PIN_BTN_OKR) == LOW) {
    int data_Sensor;
    while (1) {
      lcd.clearDisplay();
      lcd.display();
      data_Sensor = readSensor();
      followLine(data_Sensor);
    }
  }
  lcd.display();
  lcd.clearDisplay();
}

double P = 0;
double D = 0;
double error = 0;
double lastError = 0;

void followLine (int dataSensor) {
  switch (dataSensor) {
    case 0b00000011000000: error = 0;    break;

    case 0b00000110000000: error = 1;    break;
    case 0b00000100000000: error = 2;    break;
    case 0b00001100000000: error = 3;    break;
    case 0b00001000000000: error = 4;    break;
    case 0b00011000000000: error = 5;    break;
    case 0b00010000000000: error = 6;    break;
    case 0b00110000000000: error = 7;    break;
    case 0b00100000000000: error = 8;    break;
    case 0b01100000000000: error = 9;    break;
    case 0b01000000000000: error = 10;    break;
    case 0b11000000000000: error = 11;    break;
    case 0b10000000000000: error = 12;    break;

    case 0b00000001100000: error = -1;    break;
    case 0b00000000100000: error = -2;    break;
    case 0b00000000110000: error = -3;    break;
    case 0b00000000010000: error = -4;    break;
    case 0b00000000011000: error = -5;    break;
    case 0b00000000001000: error = -6;    break;
    case 0b00000000001100: error = -7;    break;
    case 0b00000000000100: error = -8;    break;
    case 0b00000000000110: error = -9;    break;
    case 0b00000000000010: error = -10;    break;
    case 0b00000000000011: error = -11;    break;
    case 0b00000000000001: error = -12;    break;
  }

  P = error * Kp;
  D = (error - lastError) * Kd ;

  double rateError = error - lastError;
  lastError = error;
  double moveVal = P + D;
  double moveLeft = run_speed - moveVal;
  double moveRight = run_speed + moveVal;

  moveLeft = constrain(moveLeft, min_speed, max_speed);
  moveRight = constrain(moveRight, min_speed, max_speed);

  setMotor(moveLeft, moveRight);
}

byte x[14] = {0, 0, 0, 0, 30, 30, 30, 30, 60, 60, 60, 60, 90, 90};
byte y[14] = {20, 30, 40, 50, 20, 30, 40, 50, 20, 30, 40, 50, 20, 30};

void display_sensor() {
  int sens = readSensor();
  for (int i = 0; i < 14; i++) {
    if ((sens << i) & 0b10000000000000) {
      lcd.fillRect(2 + (8 * i), 1, 5, 13, WHITE);
    } else {
      lcd.fillRect(2 + (8 * i), 1, 5, 13, BLACK);
      lcd.fillRect(2 + (8 * i), 1 + 13 - 1, 5, 1, WHITE);
    }

    if (i < 14) {
      sprintf(buff, "%4d", adcValue[i]);
      lcd.setCursor(x[i], y[i]);
      lcd.print(adcValue[i]);
    }
  }
  delay(50);
}

void setMotor(int LL, int RR) {
  if (RR > 0) {
    analogWrite(PIN_PWM_MOTOR_R, 255 - RR);
    analogWrite(PIN_DIR_MOTOR_R, 255);
  } else {
    analogWrite(PIN_PWM_MOTOR_R, 255 );
    analogWrite(PIN_DIR_MOTOR_R, 255 + RR);
  }

  if (LL > 0) {
    analogWrite(PIN_PWM_MOTOR_L, 255 - LL);
    analogWrite(PIN_DIR_MOTOR_L, 255);
  } else {
    analogWrite(PIN_PWM_MOTOR_L, 255);
    analogWrite(PIN_DIR_MOTOR_L, 255 + LL);
  }
}

#define PIN_EN_SENSOR_L 23
#define PIN_EN_SENSOR_R 0
byte posSensor[14] = {A4, A3, A5, A2, A6, A1, A7, A7, A1, A6, A2, A5, A3, A4};

int readSensor() {
  unsigned int valSensor[14];
  int dataSensorBit = 0b00000000000000;

  digitalWrite(PIN_EN_SENSOR_L, HIGH);
  digitalWrite(PIN_EN_SENSOR_R, LOW);
  delayMicroseconds(300);
  for (int x = 0; x < 7; x++) {
    adcValue[x] = analogRead(posSensor[x]);
  }
  delayMicroseconds(300);
  digitalWrite(PIN_EN_SENSOR_L, LOW);
  digitalWrite(PIN_EN_SENSOR_R, HIGH);
  delayMicroseconds(300);
  for (int x = 0; x < 7; x++) {
    adcValue[x + 7] = analogRead(posSensor[x + 7]);
  }
  digitalWrite(PIN_EN_SENSOR_L, HIGH);
  digitalWrite(PIN_EN_SENSOR_R, HIGH);


  for (int i = 0; i < 14; i++) {
    if ( adcValue[i] > limit_value[i]) {
      dataSensorBit = dataSensorBit  + (0b10000000000000 >> i);
    }
  }
  return dataSensorBit;
}
