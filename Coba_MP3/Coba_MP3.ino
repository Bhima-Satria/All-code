#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h>
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;


void setup() {
  // put your setup code here, to run once:
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
  MP3player.setVolume(0, 0); 
}

void loop() {
  // put your main code here, to run repeatedly:
 MP3player.available();
 MP3player.playTrack("0016");
}
