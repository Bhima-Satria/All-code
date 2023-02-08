//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);

int pengepas = 1500;
int a,b;
boolean x,y,z;
int kasus,memori,kunci;

// button
int openLt1 = 46;
int openLt2 = 44;
int openLt3 = 42;
int openLt4 = 40;

int lt1 = 47;
int lt2 = 48;
int lt3 = 50;
int lt4 = 52;

int buka  = 49;
int tutup = 43;

int sensor = 30;

// limit switch
int lmBuka  = 53;
int lmTutup = 51;

int lmLt1   = 39;
int lmLt2   = 37;
int lmLt3   = 35;
int lmLt4   = 33;

/*
//LED
int diam = 38;
int LED1 = 44;
int LED2 = 45;
int LED3 = 46;
int LED4 = 47;
*/

// motor
int motorDC1 = 31;
int motorDC2 = 29;

int motorAC1 = 27;
int motorAC2 = 25;

// Pin to wemos
int pin_lt1 = 15;
int pin_lt2 = 19;
int pin_lt3 = 21;
int pin_lt4 = 23;
int pin_up  = 11;
int pin_down= 13;

void setup() {
  Serial.begin(9600);
  //lcd.init();
  //lcd.backlight();

  // button
  pinMode(openLt1,INPUT_PULLUP);
  pinMode(openLt2,INPUT_PULLUP);
  pinMode(openLt3,INPUT_PULLUP);
  pinMode(openLt4,INPUT_PULLUP);
  
  pinMode(lt1,INPUT_PULLUP);
  pinMode(lt2,INPUT_PULLUP);
  pinMode(lt3,INPUT_PULLUP);
  pinMode(lt4,INPUT_PULLUP);

  pinMode(buka, INPUT_PULLUP);
  pinMode(tutup,INPUT_PULLUP);
  
  pinMode(sensor,INPUT_PULLUP);

  //limit switch
  pinMode(lmBuka, INPUT_PULLUP);
  pinMode(lmTutup,INPUT_PULLUP);
  
  pinMode(lmLt1,  INPUT_PULLUP);
  pinMode(lmLt2,  INPUT_PULLUP);
  pinMode(lmLt3,  INPUT_PULLUP);
  pinMode(lmLt4,  INPUT_PULLUP);

  /*
  //LED
  pinMode(diam,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  */

  //motor
  pinMode(motorDC1,OUTPUT);
  pinMode(motorDC2,OUTPUT);
  pinMode(motorAC1,OUTPUT);
  pinMode(motorAC2,OUTPUT);

  //Pin to wemos
  pinMode(pin_lt1 ,OUTPUT);
  pinMode(pin_lt2 ,OUTPUT);
  pinMode(pin_lt3 ,OUTPUT);
  pinMode(pin_lt4 ,OUTPUT);
  pinMode(pin_up  ,OUTPUT);
  pinMode(pin_down,OUTPUT);

  digitalWrite(motorAC1, HIGH); 
  digitalWrite(motorAC2, HIGH);
  digitalWrite(motorDC1, HIGH); 
  digitalWrite(motorDC2, HIGH);
  
}
void loop() {
  //call lantai 1 kabin di lantai 2, 3, 4
  if (((digitalRead(lmLt2) == LOW) || (digitalRead(lmLt3) == LOW) || (digitalRead(lmLt4) == LOW)) && ((digitalRead(openLt1) == LOW)||(digitalRead(lt1) == LOW)||memori == 1) && x == 0) {
    kasus = 1;
    perbaruiData();
    pin_pintu(0,1);
    //lcd.setCursor(0,1);
    Serial.println("TURUN KE LT1    ");    
    tunda(1500);
  }
  turun(1,lmLt1);
  berhenti(1,lmLt1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //call lt2 kabin di lantai 1
  if ((digitalRead(lmLt1) == LOW) && ((digitalRead(openLt2) == LOW)||(digitalRead(lt2) == LOW)||memori == 2) && x == 0) {
    kasus = 2;
    perbaruiData();
    pin_pintu(1,0);
    //lcd.setCursor(0,1);
    Serial.println("NAIK KE LT2     ");   
    tunda(1500);
  }
  naik(2,lmLt2);
  berhenti(2,lmLt2);
  
  //call lt2 kabin di lantai 3 dan 4
  if (((digitalRead(lmLt3) == LOW) || (digitalRead(lmLt4) == LOW)) && ((digitalRead(openLt2) == LOW)||(digitalRead(lt2) == LOW)||memori == 2) && x == 0) {
    kasus = 3;
    perbaruiData();
    pin_pintu(0,1);
    //lcd.setCursor(0,1);
    Serial.println("TURUN KE LT2    ");   
    tunda(1500);
  }
  turun(3,lmLt2);
  berhenti(3,lmLt2);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
   //call lt3 kabin di lantai 1 dan 2
  if (((digitalRead(lmLt1) == LOW) || (digitalRead(lmLt2) == LOW) ) && ((digitalRead(openLt3) == LOW)||(digitalRead(lt3) == LOW)||memori == 3) && x == 0) {
    kasus = 4;
    perbaruiData();
    pin_pintu(1,0);
    //lcd.setCursor(0,1);
    Serial.println("NAIK KE LT3   ");   
    tunda(1500);
  }
  naik(4,lmLt3);
  berhenti(4,lmLt3);
  
     //call lt3 kabin di lantai 4
  if ((digitalRead(lmLt4) == LOW)  && ((digitalRead(openLt3) == LOW)||(digitalRead(lt3) == LOW)||memori == 3) && x == 0) {
    kasus = 5;
    perbaruiData();
    pin_pintu(0,1);
    //lcd.setCursor(0,1);
    Serial.println("TURUN KE LT3    ");   
    tunda(1500);
  }
  turun(5,lmLt3);
  berhenti(5,lmLt3);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //call lt4 kabin di lantai 1, 2, 3
  if (((digitalRead(lmLt2) == LOW) || (digitalRead(lmLt3) == LOW) || (digitalRead(lmLt1) == LOW)) && ((digitalRead(openLt4) == LOW)||(digitalRead(lt4) == LOW)||memori == 4) && x == 0) {
    kasus =6;
    perbaruiData();
    pin_pintu(1,0);
    //lcd.setCursor(0,1);
    Serial.println("NAIK KE LT4     ");   
    tunda(1500);
  }
  naik(6,lmLt4);
  berhenti(6,lmLt4);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Memori
  if((digitalRead(openLt1) == LOW || digitalRead(lt1) == LOW)&& kunci == 0){
    memori = 1; 
    kunci = 1; 
    //digitalWrite(LED1, HIGH);
  }
  if((digitalRead(openLt2) == LOW || digitalRead(lt2) == LOW)&& kunci == 0){
    memori = 2;  
    kunci = 1;
    //digitalWrite(LED2, HIGH); 
  }
  if((digitalRead(openLt3) == LOW || digitalRead(lt3) == LOW)&& kunci == 0){
    memori = 3; 
    kunci = 1;  
    //digitalWrite(LED3, HIGH);
  }
  if((digitalRead(openLt4) == LOW || digitalRead(lt4) == LOW)&& kunci == 0){
    memori = 4; 
    kunci = 1; 
    //digitalWrite(LED4, HIGH); 
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
  // LCD
  if(digitalRead(lmLt1) == LOW){
    pin_lantai(0,0,0,0);
    //lcd.setCursor(0,0);
    Serial.println("KABIN DI LT1    ");  
  }
  if(digitalRead(lmLt2) == LOW){
    pin_lantai(0,1,0,0);
    //lcd.setCursor(0,0);
    Serial.println("KABIN DI LT2    ");  
  }
  if(digitalRead(lmLt3) == LOW){
    pin_lantai(0,0,1,0);
    //lcd.setCursor(0,0);
    Serial.println("KABIN DI LT3    ");  
  }
  if(digitalRead(lmLt4) == LOW){
    pin_lantai(0,1,1,0);
    //lcd.setCursor(0,0);
    Serial.println("KABIN DI LT4    ");  
  }
}
