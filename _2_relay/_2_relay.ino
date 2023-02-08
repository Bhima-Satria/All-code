#include "SIM900.h"
#include "sms.h"
#include "SoftwareSerial.h"
#include "sms.h"
#include <PString.h>
SMSGSM sms;

boolean started=false;
char smsbuffer[160];
int led=13;
char n[20];
char msg[160];
char buffer[160];
int relay1=0;
int relay2=1;
int relay3=4;
int relay4=5;
void setup(){
  pinMode(led,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
  if(gsm.begin(9600)){
    started=true;
    
  }
  
  if(started){
   delsms(); 
  }
  delay(1000);

  }

void loop(){
 PString str(buffer, sizeof(buffer));
 str.begin();
 
 int pos=0;
 if(started){
  pos=sms.IsSMSPresent(SMS_ALL);
  if(pos){
    digitalWrite(led,HIGH);
    sms.GetSMS(pos,n,smsbuffer,100);
   
     
    if(!strcmp(smsbuffer,"relay1on")){
      
      digitalWrite(relay1,LOW);
      sms.SendSMS(n,"Relay 1 Telah Aktif");
    }
  
    if(!strcmp(smsbuffer,"relay2on")){
      
      digitalWrite(relay2,LOW);
      sms.SendSMS(n,"Relay 2 Telah Aktif");
    }
    
   
    
    if(!strcmp(smsbuffer,"relay1off")){
      
      digitalWrite(relay1,HIGH);
      sms.SendSMS(n,"Relay 1 Telah di Nonaktifkan");
    }
    if(!strcmp(smsbuffer,"relay2off")){
      
      digitalWrite(relay2,HIGH);
      sms.SendSMS(n,"Relay 2 Telah di Nonaktifkan");
      
    }
   
    
    delsms();
    digitalWrite(led,LOW);
  }
 }
  delay(100);
}



void delsms()
{
  for (int i=0; i<10; i++)
  {  
      int pos=sms.IsSMSPresent(SMS_ALL);
      if (pos!=0)
      {
        if (sms.DeleteSMS(pos)==1){}else{}
      }
  }
}
