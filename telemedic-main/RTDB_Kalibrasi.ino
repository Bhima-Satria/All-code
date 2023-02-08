#include <FS.h>
#include "SPIFFS.h"
#include <WebServer.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <time.h>

#include <Adafruit_GFX.h>        //OLED libraries
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "MAX30105.h"           //MAX3010x library
#include "heartRate.h"          //Heart rate calculating algorithm

MAX30105 particleSensor;

const byte RATE_SIZE = 10; 
byte rates[RATE_SIZE]; 
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;


double avered = 0;
double aveir = 0;
double sumirrms = 0;
double sumredrms = 0;

double SpO2 = 0;
double ESpO2 = 0.0;
double FSpO2 = 0.7; //filter factor for estimated SpO2
double frate = 0.95; //low pass filter for IR/red LED value to eliminate AC component
int i = 0;
int Num = 30;
#define FINGER_ON 7000
#define MINIMUM_SPO2 0.0


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)

#define USEFIFO

int timezone = 7 * 3600;
int dst = 0,jam,menit,detik,hari,bulan,tahun;


const char* ssid = "IF&Partners";
const char* password = "officiumnobile";

#if defined(ESP32)
#include <WiFi.h>

#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
/* 2. Define the API Key */
#define API_KEY "AIzaSyAqbXsjy57NTI5OXmt0T86GJhE4cVBgvgU"

/* 3. Define the RTDB URL */
#define DATABASE_URL "iotum-getwellsoon-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "esp8266@gmail.com"
#define USER_PASSWORD "esp8266"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseData fbdo2;
FirebaseData fbdo3;
FirebaseJson jsonKu = fbdo.to<FirebaseJson>();

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

int count = 0;

const float alpha = 0.5;
double data_filtered[] = {0, 0};
const int n = 1;

  FirebaseData fData ; 
  FirebaseJson json = fData.to<FirebaseJson>();
  FirebaseJson json2;

static const unsigned char PROGMEM logo2_bmp[] =
{ 0x03, 0xC0, 0xF0, 0x06, 0x71, 0x8C, 0x0C, 0x1B, 0x06, 0x18, 0x0E, 0x02, 0x10, 0x0C, 0x03, 0x10,              //Logo2 and Logo3 are two bmp pictures that display on the OLED if called
  0x04, 0x01, 0x10, 0x04, 0x01, 0x10, 0x40, 0x01, 0x10, 0x40, 0x01, 0x10, 0xC0, 0x03, 0x08, 0x88,
  0x02, 0x08, 0xB8, 0x04, 0xFF, 0x37, 0x08, 0x01, 0x30, 0x18, 0x01, 0x90, 0x30, 0x00, 0xC0, 0x60,
  0x00, 0x60, 0xC0, 0x00, 0x31, 0x80, 0x00, 0x1B, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x04, 0x00,
};

static const unsigned char PROGMEM logo3_bmp[] =
{ 0x01, 0xF0, 0x0F, 0x80, 0x06, 0x1C, 0x38, 0x60, 0x18, 0x06, 0x60, 0x18, 0x10, 0x01, 0x80, 0x08,
  0x20, 0x01, 0x80, 0x04, 0x40, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, 0x02, 0xC0, 0x00, 0x08, 0x03,
  0x80, 0x00, 0x08, 0x01, 0x80, 0x00, 0x18, 0x01, 0x80, 0x00, 0x1C, 0x01, 0x80, 0x00, 0x14, 0x00,
  0x80, 0x00, 0x14, 0x00, 0x80, 0x00, 0x14, 0x00, 0x40, 0x10, 0x12, 0x00, 0x40, 0x10, 0x12, 0x00,
  0x7E, 0x1F, 0x23, 0xFE, 0x03, 0x31, 0xA0, 0x04, 0x01, 0xA0, 0xA0, 0x0C, 0x00, 0xA0, 0xA0, 0x08,
  0x00, 0x60, 0xE0, 0x10, 0x00, 0x20, 0x60, 0x20, 0x06, 0x00, 0x40, 0x60, 0x03, 0x00, 0x40, 0xC0,
  0x01, 0x80, 0x01, 0x80, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x30, 0x0C, 0x00,
  0x00, 0x08, 0x10, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x01, 0x80, 0x00
};

static const unsigned char PROGMEM O2_bmp[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x3f, 0xc3, 0xf8, 0x00, 0xff, 0xf3, 0xfc,
  0x03, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0xfe, 0x0f, 0xff, 0xff, 0x7e,
  0x1f, 0x80, 0xff, 0xfc, 0x1f, 0x00, 0x7f, 0xb8, 0x3e, 0x3e, 0x3f, 0xb0, 0x3e, 0x3f, 0x3f, 0xc0,
  0x3e, 0x3f, 0x1f, 0xc0, 0x3e, 0x3f, 0x1f, 0xc0, 0x3e, 0x3f, 0x1f, 0xc0, 0x3e, 0x3e, 0x2f, 0xc0,
  0x3e, 0x3f, 0x0f, 0x80, 0x1f, 0x1c, 0x2f, 0x80, 0x1f, 0x80, 0xcf, 0x80, 0x1f, 0xe3, 0x9f, 0x00,
  0x0f, 0xff, 0x3f, 0x00, 0x07, 0xfe, 0xfe, 0x00, 0x0b, 0xfe, 0x0c, 0x00, 0x1d, 0xff, 0xf8, 0x00,
  0x1e, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00,
  0x0f, 0xe0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  Serial.begin(115200);
  

  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  
  Serial.print("Connecting");

  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  //Or use legacy authenticate method
  //config.database_url = DATABASE_URL;
  //config.signer.tokens.legacy_token = "<database secret>";

  Firebase.begin(&config, &auth);

  while( WiFi.status() != WL_CONNECTED ){
      delay(100);
      Serial.print(".");        
  }


  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK");  

  Serial.println("System Start");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.display();
  delay(3000);

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30102");
    while (1);
  }
  byte ledBrightness = 0x7F; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only(心跳), 2 = Red + IR(血氧)
  //Options: 1 = IR only, 2 = Red + IR on MH-ET LIVE MAX30102 board
  int sampleRate = 1000; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 215; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384
  // Set up the wanted parameters
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
  particleSensor.enableDIETEMPRDY();

  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

void loop() {
  long irValue = particleSensor.getIR();    //Reading the IR value it will permit us to know if there's a finger on the sensor or not

  
  if  (irValue > FINGER_ON ) {
  
    display.clearDisplay();
    display.drawBitmap(5, 5, logo2_bmp, 24, 21, WHITE);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(42, 10);
    display.print(beatAvg); display.println(" BPM");
    display.drawBitmap(0, 35, O2_bmp, 32, 32, WHITE);
    display.setCursor(42, 40);
  
    if (beatAvg > 30) display.print(String(ESpO2) + "%");
    else display.print("---- %" );
    display.display();
   
    if (checkForBeat(irValue) == true) {
      display.clearDisplay();
      display.drawBitmap(0, 0, logo3_bmp, 32, 32, WHITE);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(42, 10);
      display.print(beatAvg); display.println(" BPM");
      display.drawBitmap(0, 35, O2_bmp, 32, 32, WHITE);
      display.setCursor(42, 40);
     
      if (beatAvg > 10) display.print(String(ESpO2) + "%");
      else display.print("---- %" );
      display.display();
  
 
      Serial.print("beatAvg="); Serial.println(beatAvg);
      long delta = millis() - lastBeat;
      lastBeat = millis();
      beatsPerMinute = 60 / (delta / 1000.0);
      if (beatsPerMinute < 255 && beatsPerMinute > 20) {
       
        rates[rateSpot++] = (byte)beatsPerMinute; 
        rateSpot %= RATE_SIZE;
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++) beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }

   
    uint32_t ir, red ;
    double fred, fir;
    particleSensor.check(); //Check the sensor, read up to 3 samples
    if (particleSensor.available()) {
      i++;
      red = particleSensor.getFIFOIR(); 
      ir = particleSensor.getFIFORed(); 
      //Serial.println("red=" + String(red) + ",IR=" + String(ir) + ",i=" + String(i));
      fred = (double)red;//轉double
      fir = (double)ir;//轉double
      avered = avered * frate + (double)red * (1.0 - frate);//average red level by low pass filter
      aveir = aveir * frate + (double)ir * (1.0 - frate); //average IR level by low pass filter
      sumredrms += (fred - avered) * (fred - avered); //square sum of alternate component of red level
      sumirrms += (fir - aveir) * (fir - aveir);//square sum of alternate component of IR level
      if ((i % Num) == 0) {
        double R = (sqrt(sumredrms) / avered) / (sqrt(sumirrms) / aveir);
        SpO2 = -23.3 * (R - 0.4) + 100;
        ESpO2 = FSpO2 * ESpO2 + (1.0 - FSpO2) * SpO2;//low pass filter
        if (ESpO2 <= MINIMUM_SPO2) ESpO2 = MINIMUM_SPO2; //indicator for finger detached
        if (ESpO2 > 100) ESpO2 = 99.9;
        Serial.print("Oxygen % = "); Serial.println(ESpO2);
        sumredrms = 0.0; sumirrms = 0.0; SpO2 = 0;
        i = 0;
      }
      particleSensor.nextSample(); //We're finished with this sample so move to next sample
    }

  }
  
 
 
 else  {
   
    for (byte rx = 0 ; rx < RATE_SIZE ; rx++) rates[rx] = 0;
    beatAvg = 0; rateSpot = 0; lastBeat = 0;
   
    avered = 0; aveir = 0; sumirrms = 0; sumredrms = 0;
    SpO2 = 0; ESpO2 = 0.0;
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(30, 5);
    display.println("Finger");
    display.setCursor(30, 35);
    display.println("Please");
    display.display();
 }
   
 
  int raw = analogRead(35);
  double celcius = raw*0.15113671875;
   double suhu = celcius + 2;

    // Low Pass Filter
    data_filtered[n] = alpha * suhu + (1 - alpha) * data_filtered[n-1];

    // Store the last filtered data in data_filtered[n-1]
    data_filtered[n-1] = data_filtered[n];

   
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);

  hari = p_tm->tm_mday;
  bulan = p_tm->tm_mon + 1;
  tahun = p_tm->tm_year + 1900;

  String day = String(hari)+"/"+ String (bulan)+"/"+tahun;
  

  jam = p_tm->tm_hour;
  menit = p_tm->tm_min;
  detik = p_tm->tm_sec;


  String Waktu = String(jam)+":"+ String (menit)+":"+detik;

  String Time = String(jam)+":"+ String (menit)+":"+String (detik)+" "+String(hari)+"/"+ String (bulan)+"/"+String (tahun);

if ((millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();




    
    FirebaseJson json;
    json.add("historyHeart", beatAvg);
    json.add("historyOxygen", ESpO2);
    json.add("historyTemp", data_filtered[n]);
    json.add("historyTime", Waktu);
    json.add("historyDate", day);

    Serial.printf("Push json... %s\n", Firebase.RTDB.pushJSON(&fbdo, "/deviceData/11072021025/-MhIKRhWKun6goXDhbE8/deviceHistory", &json) ? "ok" : fbdo.errorReason().c_str());

    count++;
   
  }
}
