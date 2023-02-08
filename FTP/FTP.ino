#include <SD.h>

const int chipSelect = 4;
int8_t answer;
int onModulePin= 2;

char aux_str[50];

char file_name[ ]="test.txt";

void setup(){
  delay(5000);
    // SD function
    Serial.begin(9600);
    pinMode(chipSelect, OUTPUT);
    pinMode(10, OUTPUT);  // SD library to work
    digitalWrite(10,HIGH);
    Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect))
    {
    Serial.println("Card failed, or not present");
    return;
    }
    Serial.println("card initialized.");
    File dataFile = SD.open("datalog.txt", FILE_READ);
    if (dataFile)
      Serial.println(" datalog.txt is opened in read mode.");
    // GSM function
    pinMode(onModulePin, OUTPUT);
    Serial1.begin(9600);
    delay(3000);
   
    sendATcommand("AT", "OK", 5000);
    Serial.println("GSM modem working!");
    delay(3000);
   
    // waits for signal
    while( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) ||
            sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );
   
    // sets APN, user name and password
    sendATcommand("AT+CGSOCKCONT=1,\"IP\",\"airtelgprs.com\"", "OK", 2000);
    // ther is no username and password for my GPRS connection so I commented out this line
    //sendATcommand("AT+CSOCKAUTH=1,1,\"\",\"\"", "OK", 2000);
   
    // sets the paremeters for the FTP server
    sendATcommand("AT+CFTPSERV=\"mydomain.in\"", "OK", 2000);
    sendATcommand("AT+CFTPPORT=21", "OK", 2000);
    sendATcommand("AT+CFTPMODE=1", "OK", 2000);
    sendATcommand("AT+CFTPUN=\"username\"", "OK", 2000);
    sendATcommand("AT+CFTPPW=\"password\"", "OK", 2000);
   
    // the file must be in the current directory
    sprintf(aux_str, "AT+CFTPPUTFILE=\"%s\",0", file_name);
    answer = sendATcommand(aux_str, "+CFTPPUTFILE: 0", 60000);
   
    if (answer == 1)
    {       
        Serial.println("Upload done");   
    }
    else
    {
        Serial.println("Upload fail");   
    }
   

}
void loop(){
   
   

}

void power_on(){

    uint8_t answer=0;
   
    // checks if the module is started
    answer = sendATcommand("AT", "OK", 2000);
    if (answer == 0)
    {
        // power on pulse
        digitalWrite(onModulePin,HIGH);
        delay(3000);
        digitalWrite(onModulePin,LOW);
   
        // waits for an answer from the module
        while(answer == 0){   
            // Send AT every two seconds and wait for the answer
            answer = sendATcommand("AT", "OK", 2000);   
        }
    }
   
}


unsigned char sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout)
{

    unsigned char x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial1.available() > 0) Serial1.read();    // Clean the input buffer

    Serial1.println(ATcommand);    // Send the AT command


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{

        if(Serial1.available() != 0){   
            response[x] = Serial1.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer1) != NULL)   
            {
                answer = 1;
            }
        }
        // Waits for the asnwer with time out
    }
    while((answer == 0) && ((millis() - previous) < timeout));   

    return answer;
}
