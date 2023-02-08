int hum = 15;
int Relay = 22;

void setup() {
 Serial.begin(9600);
 pinMode(Relay,OUTPUT);
 Serial.print("ready");
 delay(1000);
 digitalWrite(Relay, LOW);
}

void loop() {
   int humi = analogRead(hum);
   humi = map(humi, 4095, 1293,0,100);
   if (humi > 100) {
    humi =100;
   }
   else humi=humi;
   
   Serial.println(humi);
   delay(1000);

   if (humi < 50){
   digitalWrite(Relay, LOW); 
  // Serial.print("Empan Bos");
   }
   else digitalWrite(Relay, HIGH); 
   // Serial.print("Mati Bos");
}
