#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11
#define SensorPin A0
#define ONE_WIRE_BUS 6 //Pin Sensor Suhu DS18B20

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float suhu;

float kelembaban;
int x;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
}

void loop() {
  delay(2000);
  Serial.print("Humi : ");
  humi();
  Serial.print("Soil : ");
  soil();
  Serial.print("Suhu : ");
  temp();
}


void humi() {
  float h = dht.readHumidity();
  Serial.println(h - 9);
}

void soil() {
  kelembaban = analogRead(SensorPin);
  kelembaban = map(kelembaban, 880, 300, 0, 100);
  x = kelembaban;

  if (x < 0) {
    x = 0;
  }
  else if (x > 100) {
    x = 100;
  } else
    x = kelembaban;

  Serial.print(x);
  Serial.println("%");
  delay(1000);
}

void temp() {
  //Proses pembacaan sensor
  sensors.requestTemperatures();
  suhu = sensors.getTempCByIndex(0);

  //proses menampilkan ke serial monitor
  Serial.println(suhu);
  delay(1000);
}
