#define trig1 A0
#define echo1 A1
#define trig2 A2
#define echo2 A3

long durasi1, durasi2, jarak1, jarak2;

//Motor A Direction
#define dirL 4 
#define pwmL 5 
//Motor B Direction
#define pwmR 6 
#define dirR 7 
//kipas
#define Fan 13
//Sen_Flame
#define Flame_Pin 10
//button scan sensor
#define Button 9


int Button_State = 0; // belum tergunakan

int speed = 120;
int maxSpeed = 250;

float integer =0;
float derivative =0;
float lastError =0;
float error =0;
float pid = 0;

float Kp = 0.5;
float Kd = 0;
float Ki = 0.1;
int setkiri=8;
int setdepan=10;

int turnLeft;
int turnRight;

int Sen_Flame;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  //ultrasonic
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  
  //motor
  pinMode(dirL, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(dirR, OUTPUT);
  pinMode(pwmR, OUTPUT);

  //button
  pinMode(Button, INPUT);

  //Fan
  pinMode(Fan, OUTPUT);

  //Sen_Flame
  pinMode(Flame_Pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bacadinding();
  motor_move(200,200);
  pid_perhitungan(); 
  jalan(turnLeft, turnRight);
  Api();
  if(jarak1<setdepan){
  turnRight ;
  delay(400);    
  }
}

void bacadinding(){
 //sensor depan 
  digitalWrite(trig1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig1, LOW);
  durasi1 = pulseIn(echo1, HIGH);
  jarak1 = (durasi1*.034)/2;
    
//sensor samping
  digitalWrite(trig2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig2, LOW);
  durasi2 = pulseIn(echo2, HIGH);
  jarak2= (durasi2/2) / 29.1;

  Serial.print (jarak1);
  Serial.print (" ");
  Serial.println (jarak2);
  }
  
int fungsierror(){
 long durasi2, jarak2;
  digitalWrite(trig2, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig2, LOW);
  durasi2 = pulseIn(echo2, HIGH);
  jarak2 = (durasi2*.0343)/2;
   
  int error = setkiri-jarak2; // setpoint sensor kiri
  return error;
}

void pid_perhitungan(){
  error = fungsierror();
  integer += error;
  if(integer>255){
     integer = 255; 
    }    
    if(integer<-255){
     integer = 0; 
    }
  int derivative = error-lastError;
  pid = error*Kp + integer*Ki + derivative * Kd;
  turnLeft = speed + pid;
    if(turnLeft>maxSpeed){
     turnLeft = maxSpeed; 
      }
    else if(turnLeft<-maxSpeed){
      turnLeft = 0;
    }
  turnRight = speed-pid;
    if(turnRight>maxSpeed){
      turnRight = maxSpeed; 
    }
    else if(turnRight<-maxSpeed){
      turnRight = 0;
    }
    lastError = error;
  }

void jalan(int speedLeft, int speedRight){
 if(speedLeft>0){
    digitalWrite(pwmL, HIGH);
    digitalWrite(dirL, LOW);
    analogWrite(pwmL, speedLeft);
    }
    else {
      digitalWrite(pwmL, LOW);
      digitalWrite(dirL, HIGH);
      analogWrite(dirL, speedLeft);
    }

  if(speedRight>0){
    digitalWrite(pwmR, HIGH);
    digitalWrite(dirR, LOW);
    analogWrite(pwmR, speedRight);
    }
    else{
      digitalWrite(pwmR, LOW);
      digitalWrite(dirR, HIGH);
      analogWrite(dirR, speedRight);
   }
  }

void motor_move(int motorL, int motorR){
  motorL=constrain(motorL, -255, 255);
  motorR=constrain(motorR, -255, 255);

  analogWrite(pwmL, motorL < 0 ? 255 + motorL : motorL);
  analogWrite(pwmR, motorR < 0 ? 255 + motorR : motorR);
  digitalWrite(dirL, motorL < 0 ? HIGH : LOW);
  digitalWrite(dirR, motorR < 0 ? HIGH : LOW);
}

void Api ()
{
 Sen_Flame = digitalRead(Flame_Pin);
  
 if (Sen_Flame == HIGH){
 digitalWrite(Fan, HIGH);
  digitalWrite(pwmR, LOW);
    digitalWrite(dirR, LOW); 
     digitalWrite(pwmL, LOW);
      digitalWrite(dirL, LOW);
 }
 else {
  digitalWrite(Fan, LOW);
 }
 Serial.print("Sen_Flame : ");
 Serial.print(Sen_Flame);
}

