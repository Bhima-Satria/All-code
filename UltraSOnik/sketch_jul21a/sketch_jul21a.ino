int trig= 8;            // membuat varibel trig yang di set ke-pin 8
int echo= 9;            // membuat variabel echo yang di set ke-pin 9
int kipas = 7;
long durasi, jarak;     // membuat variabel durasi dan jarak
 
void setup() {
pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
pinMode(echo, INPUT);     // set pin echo menjadi INPUT
pinMode(kipas, OUTPUT);
Serial.begin(9600);       // digunakan untuk komunikasi Serial dengan komputer
}
 
void loop() {
 
// program dibawah ini agar trigger memancarakan suara ultrasonic
digitalWrite(trig, LOW);
delayMicroseconds(8);
digitalWrite(trig, HIGH);
delayMicroseconds(8);
digitalWrite(trig, LOW);
delayMicroseconds(8);
 
durasi= pulseIn(echo, HIGH);  // menerima suara ultrasonic
jarak= (durasi/2) / 29.1;     // mengubah durasi menjadi jarak (cm)
Serial.print("jarak =");        // menampilkan jarak pada Serial Monitor
Serial.print(jarak);
Serial.println(" Cm");

if (jarak <= 20)
{digitalWrite(kipas, HIGH);}
else 
{digitalWrite(kipas, LOW);}

}
