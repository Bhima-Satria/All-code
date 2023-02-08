void suara(int play)//play suara
{
  uint8_t offset = 0;
  offset = 5000;
  String trackName="000"+String (play)+".mp3";
  char track[50];
  trackName.toCharArray(track, 50);
  //lcd.print("play");
  MP3player.playMP3(track,offset);
  delay(1000);
//  MP3player.stopTrack();
//  MP3player.playTrack(play);
//  delay(700);                                                           // Delay 700ms = 0,7detik
//  MP3player.stopTrack();
}
