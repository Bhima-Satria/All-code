

int x;
float v;
float kpa;


void setup() {
  Serial.begin(9600);

}

void loop() {

 
  
  x = analogRead(A0);
  v = x*(5.0/1023.0);
  kpa = ((v/5.0)-0.04)/0.0012858;
   
 Serial.print(x);
  Serial.println("Analog");
 Serial.print(v);
  Serial.println("Volt");
 Serial.print(kpa);
  Serial.println("Pascal");
  delay(2000);
 
  
}
