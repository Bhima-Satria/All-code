/***************************************
 * PROGRAM INVERSE KINEMATIC
 **************************************/
#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoWrist;
Servo servoGripper;

LiquidCrystal lcd(2,3,4,5,6,7);

/********** ARDUINO PIN *******************/
/*Pin Number 2,3,4,5,6,7 use as LCD       */
#define SERVO_EN                8
#define SERVO_BASE_PIN          9
#define SERVO_SHOULDER_PIN      10
#define SERVO_ELBOW_PIN         11
#define SERVO_WRIST_PIN         12
#define SERVO_GRIPPER_PIN       13
#define BTN_START               A0
#define BTN_STOP                A1

/******* Arm Robot Dimension ************/
const long L_SHOULDER = 148;
const long L_ELBOW    = 160;

/******* Min-Max Pulse Servo ************/
#define BASE_MIN_PULSE        415
#define BASE_MAX_PULSE        2325
#define SHOULDER_MIN_PULSE    645
#define SHOULDER_MAX_PULSE    2210
#define ELBOW_MIN_PULSE       583
#define ELBOW_MAX_PULSE       2257
#define WRIST_MIN_PULSE       550
#define WRIST_MAX_PULSE       2504
#define GRIPPER_MIN_PULSE     665
#define GRIPPER_MAX_PULSE     2400

/******* Min-Max Angle Servo ************/
#define BASE_MIN        0
#define BASE_MAX        180
#define SHOULDER_MIN    15
#define SHOULDER_MAX    130
#define ELBOW_MIN       3
#define ELBOW_MAX       110
#define WRIST_MIN       3
#define WRIST_MAX       180
#define GRIPPER_MIN     120
#define GRIPPER_MAX     50

/******* Servo Offset Value *************/
#define SHOULDER_OFFSET       5
#define ELBOW_OFFSET          8
#define BASE_OFFSET           0

/******* EEPROM ADDRESS ****************/
#define BASE_ADD      90
#define SHOULDER_ADD  91
#define ELBOW_ADD     92


/****************************************
 * SETUP FUNCTION
 ****************************************/
int x,y,z;
 
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BTN_START, INPUT);
  pinMode(BTN_STOP, INPUT);
  pinMode(SERVO_EN, OUTPUT);
  
  /* Pengaturan Pulsa Pada Masing-Masing Servo */
  servoBase.attach(SERVO_BASE_PIN,BASE_MIN_PULSE, BASE_MAX_PULSE);
  servoShoulder.attach(SERVO_SHOULDER_PIN,SHOULDER_MIN_PULSE, SHOULDER_MAX_PULSE);
  servoElbow.attach(SERVO_ELBOW_PIN,ELBOW_MIN_PULSE, ELBOW_MAX_PULSE);
  servoWrist.attach(SERVO_WRIST_PIN,WRIST_MIN_PULSE,WRIST_MAX_PULSE);
  servoGripper.attach(SERVO_GRIPPER_PIN,GRIPPER_MIN_PULSE,GRIPPER_MAX_PULSE);

  /* Posisi Awal Motor Servo */
  servoBase.write(EEPROM.read(BASE_ADD));
  servoShoulder.write(EEPROM.read(SHOULDER_ADD));
  servoElbow.write(EEPROM.read(ELBOW_ADD));
  
  //inverse_kinematik_3dof(0, 160, 148);
  digitalWrite(SERVO_EN, HIGH);
  lcd.setCursor(0,0);
  lcd.print("Inverse Kinematic");
}

/*****************************************
 * IK FUNCTION
 ****************************************/
void inverse_kinematik_2dof(long x, long y, long z){
  float q1, q2, q1a, q1b;   //tetha
  int sudutBase, sudutShoulder, sudutElbow, sudutWrist;
  long im_1, a, b;
  boolean inRange = false;
    
//Hitung sisi miring x dan y (Persamaan 3.11)
  im_1 = sqrt(sq(x)+ sq(y)) - 25;  
//Hitung sudut q1a (Persamaan 3.10)
  q1a  = (atan2(y, x)) * RAD_TO_DEG;
//Hitung sudut q1b (Persamaan 3.12)
  a = sq(L_SHOULDER) + sq(im_1) - sq(L_ELBOW);
  b = 2 * L_SHOULDER * im_1;
  q1b = acos((float)a / (float)b);
//Jumlahkan sudut q1 (Persamaan 3.12)
  q1 = (q1a + q1b) * RAD_TO_DEG;
// Hitung sudut q2 
  a = sq(L_SHOULDER) + sq(L_ELBOW) - sq(im_1);
  b = 2 * L_SHOULDER * L_ELBOW;
  q2 = (acos((float)a / (float)b)) * RAD_TO_DEG;

// Periksa apakah sudut ada dalam jangkauan servo?
  if((q1 <= 0) || (q1 >= 0)) inRange = true;
    else inRange = false;
  if((q2 <= 0) || (q2 >= 0)) inRange = true;
    else inRange = false;
  
  if(inRange){ 
    // Pengaturan Arah Pergerakan Sudut Tiap Servo
    sudutShoulder = q1 - SHOULDER_OFFSET;
    sudutElbow    = (180 - q2 - q1) + ELBOW_OFFSET;
  
    // Batas Nilai Servo
    sudutShoulder = constrain(sudutShoulder, SHOULDER_MIN,SHOULDER_MAX);
    sudutElbow = constrain(sudutElbow, ELBOW_MIN, ELBOW_MAX);
    // Write Servo
    servoShoulder.write(sudutShoulder);
    servoElbow.write(sudutElbow);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("S1="); lcd.print((int)q1);
    lcd.setCursor(0,1);
    lcd.print("S2="); lcd.print((int)q2);
    lcd.setCursor(7,1);
    lcd.print("S3="); lcd.print((int)q2);
    }
  else{
    Serial.println("Target Di Luar Jangkauan");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Out of Range....");
    }
  }

void inverse_kinematik_3dof(long x, long y, long z){  
  float q1,q2,q2a,q2b,q3; //tetha
  int sudutBase, sudutShoulder, sudutElbow, sudutWrist; 
  long im_1, im_2, a, b;
  boolean inRange =  false; 
  
  // Sisi Miring Imajiner
  im_1 = (sqrt(sq(x) + sq(y)));
  im_2 = sqrt(sq(z) + sq(im_1));
  
  // IK Sudut Base 
  q1 = (atan2(x,y)) * RAD_TO_DEG;
  
  // IK Sudut Shoulder
  q2a = atan2(z, im_1);
  a = sq(L_SHOULDER) + sq(im_2) - sq(L_ELBOW);
  b = 2 * L_SHOULDER * im_2;
  q2b = acos((float)a / (float)b);
  q2 = (q2a + q2b) * RAD_TO_DEG;

  // IK Sudut Elbow
  a = sq(L_SHOULDER) + sq(L_ELBOW) - sq(im_2);
  b = 2 * L_SHOULDER * L_ELBOW;
  q3 = (acos((float)a / (float)b)) * RAD_TO_DEG;

  // Periksa Apakah Sudut Berada Dalam Jangkauan?
  if((q2 <= 0) || (q2 >= 0)) inRange = true;
    else inRange = false;
  if((q3 <= 0) || (q3 >= 0)) inRange = true;
    else inRange = false;
  
  if(inRange){ 
    // Pengaturan Arah Pergerakan Sudut Tiap Servo
    sudutBase     = 90 - q1 - BASE_OFFSET;
    sudutShoulder = q2 - SHOULDER_OFFSET;
    sudutElbow    = (180 - q3 - q2) + ELBOW_OFFSET;
  
    // Batas Nilai Servo
    sudutBase = constrain(sudutBase, BASE_MIN,BASE_MAX);
    sudutShoulder = constrain(sudutShoulder, SHOULDER_MIN,SHOULDER_MAX);
    sudutElbow = constrain(sudutElbow, ELBOW_MIN, ELBOW_MAX);
    sudutWrist = constrain(sudutBase, WRIST_MIN, WRIST_MAX);
    // Write Servo
    servoBase.write(sudutBase);
    servoShoulder.write(sudutShoulder);
    servoElbow.write(sudutElbow);
    servoWrist.write(sudutBase);
    // Save Last Position
    EEPROM.write(BASE_ADD, sudutBase);
    EEPROM.write(SHOULDER_ADD, sudutShoulder);
    EEPROM.write(ELBOW_ADD, sudutElbow);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("S1="); lcd.print((int)q1);
    lcd.setCursor(0,1);
    lcd.print("S2="); lcd.print((int)q2);
    lcd.setCursor(7,1);
    lcd.print("S3="); lcd.print((int)q3);
    }
  else{
    Serial.println("Target Di Luar Jangkauan");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Out of Range....");
    }
  }


/*****************************************
 * Loop
 ****************************************/
void loop() {
  if(digitalRead(BTN_START) == 0){
    delay(500);
    digitalWrite(SERVO_EN, HIGH);
 
 // Posisi yang dituju:
    x = 0; y = 200; z = 10; 
 
 // kinematik:
    inverse_kinematik_3dof(x, y, z);
    }
    
  if(digitalRead(BTN_STOP) == 0){
    delay(500);
    digitalWrite(SERVO_EN,LOW);
    }
}
