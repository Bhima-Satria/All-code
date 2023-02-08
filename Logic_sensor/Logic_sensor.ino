//deklrasasi pin sensor
int pin_sensor[] = {8, 9, 10, 11, 12};

//hasil pembacaan ditampung
int hasil_baca[] = {0, 0, 0, 0, 0};
int baca_sensor;
int inp;

void setup() {
  Serial.begin(9600);
  int a = 0;
  //setting pin sensor sebagai INPUT
  while (a < 5) {
    pinMode(pin_sensor[a], INPUT);
    a = a + 1;
  }
  Serial.println("Configuration Process");
  Serial.println("Ready for testing....");
}

void loop() {
  baca_sensor = readOut(pin_sensor);
  Serial.print("Logika = "); Serial.print(baca_sensor);
  Serial.println("");
  delay(500);
}

//fungsi untuk membaca & mengubah hasil baca menjadi interger
int readOut(int pin_sensor[]) {
  int a;
  int b = 0;
  int c = 0;
  inp = 0;

  while (c < 5) {
    hasil_baca[c] = 0;
    c = c + 1;
  }
  for (a = 0; a < 5; a++) {
    hasil_baca[a] = digitalRead(pin_sensor[a]);
  }
  while (b < 5) {
    inp = inp * 10 + hasil_baca[b];
    b = b + 1;
  }
  return inp;
}
