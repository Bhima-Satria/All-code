#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int R= 0;
int G= 0;
int B= 0;
int Y= 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,LOW);
  digitalWrite(S1,HIGH);
  
  Serial.begin(9600);
}

void loop (){
  filter();  
}

void filter() {
  
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  R = pulseIn(sensorOut, LOW);
  R = map(R, 100, 102, 255, 0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(R);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  G = pulseIn(sensorOut, LOW);
  G = map(G, 74, 75, 255, 0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(G);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  B = pulseIn(sensorOut, LOW);
  B = map(B, 37, 39, 255, 0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(B);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  
  // Setting yellow filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  Y = pulseIn(sensorOut, LOW);
  Y = map(Y, 74, 76, 255, 0);
  // Printing the value on the serial monitor
  Serial.print("Y= ");//printing name
  Serial.print(Y);//printing RED color frequency
  Serial.print("  ");
  delay(100);

  // Setting Purple filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Reading the output frequency
 int P = pulseIn(sensorOut, LOW);
  P = map(P, 52, 54, 255, 0);
  // Printing the value on the serial monitor
  Serial.print("P= ");//printing name
  Serial.print(P);//printing RED color frequency
  Serial.print("  ");
  delay(100);

    // Setting orange filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  // Reading the output frequency
 int O = pulseIn(sensorOut, LOW);
  O = map(O, 69, 70, 255, 0);
  // Printing the value on the serial monitor
  Serial.print("O= ");//printing name
  Serial.print(O);//printing RED color frequency
  Serial.println("  ");
  delay(100);

Serial.print ("Adalah ");
  
if (R == 255){
  Serial.println("Warna merah");
}
else if (G == 255) {
  Serial.println("Warna Hijau");
}
else if (B == 255) {
  Serial.println("Warna Biru");
}
else if (Y == 255) {
  Serial.println("Warna Kuning");
}
}
