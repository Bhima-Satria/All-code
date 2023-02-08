void hasilsuara(){
  while (1){
    switch (hasil1){
      case 0:    // your hand is on the sensor
        suara(0);
        break;
      case 1:    // your hand is close to the sensor
        suara(1);
        break;
      case 2:    // your hand is a few inches from the sensor
        suara(2);
        break;
      case 3:    // your hand is nowhere near the sensor
        suara(3);
        break;
      case 4:    // your hand is on the sensor
        suara(4);
        break;
      case 5:    // your hand is close to the sensor
        suara(5);
        break;
      case 6:    // your hand is a few inches from the sensor
        suara(6);
        break;
      case 7:    // your hand is nowhere near the sensor
        suara(7);
        break;
      case 8:    // your hand is on the sensor
        suara(8);
        break;
      case 9:    // your hand is close to the sensor
        suara(9);
        break; 
    }
    delay(100);                                                                         // Delay reset otomatis 100ms = 0,1detik
    fl_operasi = 0;                                                                     // f1_operasi = variabel operasi aritmatika
    hasil1 = 0;
    scantombol();
  }
}
