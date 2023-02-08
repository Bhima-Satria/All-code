int servo_base = 7;
int i;

void setup() {
  pinMode(servo_base, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(5);
}

void putar(char j, int sud) {
  for (i=0; i<j; i++) {
    digitalWrite(servo_base, HIGH);
    delayMicroseconds(sud);
    digitalWrite(servo_base, LOW);
    delay(50);
  }
}

void loop() {
  int x,y;
  if (Serial.available()){
    while(Serial.available()){
      byte incomingByte = Serial.read();
      if (incomingByte =='x') x=Serial.parseInt();
      if (incomingByte =='y') y=Serial.parseInt();
    }
    Serial.println("\tx : " + String(x) + "\ty : " + String (y));
   }
   putar(20,(y*2)+600);
}
