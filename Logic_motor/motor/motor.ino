#define enA 4
#define in1 2
#define in2 3

#define enB 7
#define in3 5
#define in4 6


void setup() {
  pinMode(enA, OUTPUT); pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);

}

void loop() {
 gerak_maju();
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
