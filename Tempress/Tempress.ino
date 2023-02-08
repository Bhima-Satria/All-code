

// Note the the tilda symbol ~ does not exist in some fonts at the moment
#define TEXT "SELAMAT DATANG" // Text that will be printed on screen in any font

#include "SPI.h"
#include "TFT_eSPI.h"
#include "fuzzy.h"

// Stock font and GFXFF reference handle
#define GFXFF 1
#define FF24 &FreeSansBold24pt7b

// Custom are fonts added to library "TFT_eSPI\Fonts\Custom" folder
// a #include must also be added to the "User_Custom_Fonts.h" file
// in the "TFT_eSPI\User_Setups" folder. See example entries.
#define CF_OL24 &Orbitron_Light_24
#define CF_OL32 &Orbitron_Light_32
#define CF_RT24 &Roboto_Thin_24
#define CF_S24  &Satisfy_24
#define CF_Y32  &Yellowtail_32


// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

#include "WiFi.h"

#include "DHT.h"

#define DHTPIN 15
#define relay1 33
#define relay2 32

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup(void) {

  Serial.begin(250000);
  
  tft.begin();

  tft.setRotation(1);

  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);            // Clear screen
  tft.setFreeFont(FF24);                 // Select the font
  tft.drawString("TEMPRESS", 160, 120, GFXFF);// Print the string name of the font
  delay(2000);
  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
    tft.setFreeFont(CF_RT24);                 // Select the font
    tft.drawString("Connecting...", 160, 200, GFXFF);// Print the test text in the custom font
  }

  Serial.println("");
  Serial.println("SmartConfig received.");

  //Wait for WiFi to connect to AP
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi Connected.");
  tft.setFreeFont(CF_RT24);                 // Select the font
  tft.drawString("WiFi Connected.", 160, 200, GFXFF);// Print the test text in the custom font

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(1000);

  dht.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.fillScreen(TFT_BLACK);            // Clear screen
  tft.setFreeFont(FF24);                 // Select the font
  tft.drawString("TEMPRESS", 160, 50, GFXFF);// Print the string name of the font
  tft.setTextDatum(ML_DATUM);
  tft.setFreeFont(CF_RT24);                 // Select the font
  tft.drawString("Kelembaban :", 20, 120, GFXFF);// Print the test text in the custom font
  tft.drawFloat(h, 2,  200, 120, GFXFF);
  tft.drawString("%",  270, 120, GFXFF);
  tft.drawString("Suhu             :", 20, 160, GFXFF);// Print the test text in the custom font
  tft.drawFloat(t, 2,  200, 160, GFXFF);
  tft.drawString("°C",  270, 160, GFXFF);
  


  // Reset text padding to zero (default)
  tft.setTextPadding(0);


  //Fuzzy 
  fuzzy(t, h);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  delay(Centroid * 1000);
  //Sampai sini
  
  digitalWrite(relay2, LOW);
  digitalWrite(relay1, HIGH);
  delay(500);

  
}
