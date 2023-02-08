
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5 //Sensor Suhu

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int sensor_pin = A0; //Sensor Tanah
int x;
float suhu=0;
float kelembaban;

void setup() {

   Serial.begin(9600);
   sensors.begin();
   Serial.println("Reading From the Sensor ...");
   delay(2000);
   pinMode(12,OUTPUT);
   }

void loop() {
//==============//Proses Input//=======================
   sensors.requestTemperatures();
   suhu=sensors.getTempCByIndex(0);
   kelembaban= analogRead(sensor_pin);
   kelembaban = map(kelembaban,1023,402,0,100);
   x=kelembaban;


if (x < 0){
  x=0;
}
else
  x=kelembaban;
 
  Serial.print("Suhu :");
  Serial.println(suhu);
   Serial.print("Moisture : ");
   Serial.print(x);
   Serial.println("%");
   delay(1000);
}


