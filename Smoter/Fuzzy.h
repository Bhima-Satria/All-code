 float miu_kering, miu_lembab, miu_basah ;
float miu_Dkering, miu_Dlembab, miu_Dbasah;
float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float terbaik, cukup, kurang;
float h_t, h_c, h_k;
float centroid;

bool kering   = false;
bool lembab   = false;
bool basah    = false;

bool Dkering  = false;
bool Dlembab  = false;
bool Dbasah   = false;

void fuzzy(float error, float D_error) {

  miu_kering = 0;
  miu_lembab = 0;
  miu_basah  = 0 ;
  miu_Dkering = 0;
  miu_Dlembab = 0;
  miu_Dbasah  = 0;

  rule1 = 0;
  rule2 = 0;
  rule3 = 0;
  rule4 = 0;
  rule5 = 0;
  rule6 = 0;
  rule7 = 0;
  rule8 = 0;
  rule9 = 0;

  terbaik = 0;
  cukup   = 0;
  kurang  = 0;
  
  h_t = 0;
  h_c = 0;
  h_k = 0;

  centroid = 0;

  //miu_kering
  Serial.print ("\n \n");
  if (error <= -2) {
    miu_kering = 1;
    kering     = true;
    Serial.print ("Miu_kering   : "); Serial.println(miu_kering);
  }
  else if (error > -2 && error <= 0) {
    miu_kering = (0 - (error)) / (0 - (-2));
    kering     = true;
    Serial.print ("Miu_kering   : "); Serial.println(miu_kering);
  }

  //miu_lembab
  if (error == 0) {
    miu_lembab = 1;
    lembab     = true;
    Serial.print ("Miu_lembab   : "); Serial.println(miu_lembab);
  }
  else if (error > -2 && error <= 0 ) {
    miu_lembab = (error - (-2)) / (0 - (-2));
    lembab     = true;
    Serial.print ("Miu_lembab   : "); Serial.println(miu_lembab);
  }
  else if (error >= 0 && error < 2) {
    miu_lembab = (2 - (error)) / (2 - 0);
    lembab     = true;
    Serial.print ("Miu_lembab   : "); Serial.println(miu_lembab);
  }

  //miu_basah
  if (error >= 2) {
    miu_basah = 1;
    basah     = true;
    Serial.print ("Miu_basah    : "); Serial.println(miu_basah);
  }
  else if (error <= 2 && error > 0 ) {
    miu_basah = (error - 0) / (2 - 0);
    basah     = true;
    Serial.print ("Miu_basah    : "); Serial.println(miu_basah);
  }

  //miu_Dkering
  if (D_error <= -2) {
    miu_Dkering = 1;
    Dkering     = true;
    Serial.print ("Miu_Dkering  : "); Serial.println(miu_Dkering);
  }
  else if (D_error > -2 && D_error <= 0 ) {
    miu_Dkering = (0 - (D_error)) / (0 - (-2));
    Dkering     = true;
    Serial.print ("Miu_Dkering  : "); Serial.println(miu_Dkering);
  }

  //miu_Dlembab
  if (D_error == 0) {
    miu_Dlembab = 1;
    Dlembab     = true;
    Serial.print ("Miu_Dlembab  : "); Serial.println(miu_Dlembab);
  }
  else if (D_error >= -2 && D_error < 0 ) {
    miu_Dlembab = (D_error - (-2)) / (0 - (-2));
    Dlembab     = true;
    Serial.print ("Miu_Dlembab  : "); Serial.println(miu_Dlembab);
  }
  else if (D_error > 0 && D_error <= 2 ) {
    miu_Dlembab = (2 - (D_error)) / (2 - 0);
    Dlembab     = true;
    Serial.print ("Miu_Dlembab  : "); Serial.println(miu_Dlembab);
  }

  //miu_Dbasah
  if (D_error >= 2 ) {
    miu_Dbasah  = 1;
    Dbasah      = true;
    Serial.print ("Miu_Dbasah   : "); Serial.println(miu_Dbasah);
  }
  else if (D_error >= 0 && D_error < 2) {
    miu_Dbasah  = (D_error - 0) / (2 - 0);
    Dbasah      = true;
    Serial.print ("Miu_Dbasah   : "); Serial.println(miu_Dbasah);
  }


  //Tampilkan rule
  Serial.print ("\n \n");

  //Rule base
  if (kering == true && Dkering == true) {
    rule1 = min(miu_kering, miu_Dkering);
    Serial.print ("Rule 1 : "); Serial.println(rule1);
  }

  if (kering == true && Dlembab == true) {
    rule2 = min(miu_kering, miu_Dlembab);
    Serial.print ("Rule 2 : "); Serial.println(rule2);
  }

  if (kering == true && Dbasah == true) {
    rule3 = min(miu_kering, miu_Dbasah);
    Serial.print ("Rule 3 : "); Serial.println(rule3);
  }

  if (lembab == true && Dkering == true) {
    rule4 = min(miu_lembab, miu_Dkering);
    Serial.print ("Rule 4 : "); Serial.println(rule4);
  }

  if (lembab == true && Dlembab == true) {
    rule5 = min(miu_lembab, miu_Dlembab);
    Serial.print ("Rule 5 : "); Serial.println(rule5);
  }

  if (lembab == true && Dbasah == true) {
    rule6 = min(miu_lembab, miu_Dbasah);
    Serial.print ("Rule 6 : "); Serial.println(rule6);
  }

  if (basah == true && Dkering == true) {
    rule7 = min(miu_basah, miu_Dkering);
    Serial.print ("Rule 7 : "); Serial.println(rule7);
  }

  if (basah == true && Dlembab == true) {
    rule8 = min(miu_basah, miu_Dlembab);
    Serial.print ("Rule 8 : "); Serial.println(rule8);
  }

  if (basah == true && Dbasah == true) {
    rule9 = min(miu_basah, miu_Dbasah);
    Serial.print ("Rule 9 : "); Serial.println(rule9);
  }

  //Implikasi maks
  terbaik = rule1;
  cukup   = max(max(rule2, rule4), rule5);
  kurang  = max(max(rule3, rule6), max(max(rule7, rule7), rule9));

  Serial.print("\n\n");
  Serial.print("Terbaik : ");
  Serial.println(terbaik);
  Serial.print("Cukup   : ");
  Serial.println(cukup);
  Serial.print("Kurang  : ");
  Serial.println(kurang);
  Serial.print("\n\n");

  h_t = (terbaik * (0 + 0.2 + 0.4 + 0.6 + 0.8 + 1 + 1.2 + 1.4 + 1.6 + 1.8 + 2));
  h_c = (cukup * (1 + 1.2 + 1.4 + 1.6 + 1.8 + 2 + 2.2 + 2.4 + 2.6 + 2.8 + 3));
  h_k = (kurang * (2 + 2.5 + 3 + 3.5 + 4 + 4.5 + 5 + 5.5 + 6 + 6.5 + 7 + 7.5 + 8 + 8.5 + 9 + 9.5 + 10));

  centroid = (h_t + h_c + h_k) / ((terbaik * 11) + (cukup * 11) + (kurang * 17)) ;

  Serial.print("\n \n");
  Serial.print("Defuzzyfikasi = ");
  Serial.println(centroid);
  Serial.print("\n\n");
  delay(1000);

  kering   = false;
  lembab   = false;
  basah    = false;

  Dkering  = false;
  Dlembab  = false;
  Dbasah   = false;
}
