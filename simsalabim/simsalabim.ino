#include <BLEDevice.h> 
#define ADDRESS "ff:ff:10:00:2e:ce"
#define RELAY_PIN 4 
#define SCAN_INTERVAL 100 
#define TARGET_RSSI -100 
#define MAX_MISSING_TIME 5000
int hitung=0;
BLEScan* pBLEScan; 
uint32_t lastScanTime = 0;
boolean found = false;
uint32_t lastFoundTime = 0;
int rssi = 0;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks 
{ 
    void onResult(BLEAdvertisedDevice advertisedDevice) 
    { 
       
        Serial.print("Device found: ");      
        Serial.println(advertisedDevice.toString().c_str()); 
 
       
        if(advertisedDevice.getAddress().toString() == ADDRESS) 
        { 
            
            found = true; 
            advertisedDevice.getScan()->stop(); 
            rssi = advertisedDevice.getRSSI();
            Serial.println("RSSI: " + rssi);
        } 
    } 
};

void setup() 
{ 
    Serial.begin(115200); 
   
    pinMode(RELAY_PIN, OUTPUT); 
    digitalWrite(RELAY_PIN, LOW); 
 
  
    BLEDevice::init(""); 
    pBLEScan = BLEDevice::getScan(); 
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); 
    pBLEScan->setActiveScan(true); 
}

void loop()
{   
    uint32_t now = millis(); 
 
    if(found){
        lastFoundTime = millis(); 
        found = false;
         
        if(rssi > TARGET_RSSI){ 
            hitung=5;
            digitalWrite(RELAY_PIN, HIGH);
            delay(500);
            
        }
        else{
            hitung-=1;
            if(hitung<0){
              hitung=0;
            }
            if(hitung==0){
            digitalWrite(RELAY_PIN, LOW);
            }
        }
    }
   
    else if(now - lastFoundTime > MAX_MISSING_TIME){
        digitalWrite(RELAY_PIN, LOW);  
    }
     
    if(now - lastScanTime > SCAN_INTERVAL){ 
       
        lastScanTime = now;
        pBLEScan->start(1);
    }
}
