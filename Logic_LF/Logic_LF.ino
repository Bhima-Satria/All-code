#define enA 4
#define in1 2
#define in2 3

#define enB 7
#define in3 5
#define in4 6


int pin_sensor[] = {8, 9, 10, 11, 12};
int baca_sensor;
int inp;
int hasil_baca[] = {0, 0, 0, 0, 0};

void setup() {
  pinMode(enA, OUTPUT); pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);

  int a;
  //setting pin sensor sebagai INPUT
  while (a < 5) {
    pinMode(pin_sensor[a], INPUT);
    a = a + 1;
  }
}
void loop() {
  baca_sensor = readOut(pin_sensor);
  switch (baca_sensor) {
    //hasil baca sensor untuk belok kiri
    case 11110: case 11000:
    case 11100: case 11101:
    case 10000:
      belok_kiri(); break;

    //hasil baca sensor untuk arah maju
    case 11001: case 11011:
    case 10011:
      gerak_maju(); break;

    //hasil baca sensor untuk belok kanan
    case 10111: case 111:  case 11:
    case 1111: case 1:
      belok_kanan(); break;

    //baca hitam semua=stop
    case 0:
      motor_stop(); break;
  }
}

//menampung hasil baca sensor menjadi integer
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

//kendali motor
void gerak_maju() {
  analogWrite (enA, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite (enB, 255);
}
void belok_kanan() {
  analogWrite (enA, 0);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite (enB, 200);
}

void belok_kiri() {
  analogWrite (enA, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite (enB, 0);
}
void motor_stop() {
  analogWrite (enA, 0);
  analogWrite (enB, 0);
}
