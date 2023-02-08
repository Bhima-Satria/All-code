float miu_dingin, miu_sejuk, miu_normalc, miu_hangat, miu_panas;
float miu_Tkering, miu_kering, miu_normalm, miu_lembab, miu_basah;
float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float rule10, rule11, rule12, rule13, rule14, rule15, rule16, rule17, rule18;
float rule19, rule20, rule21, rule22, rule23, rule24, rule25;
float SC, C, N, L, SL;
float H_SC, H_C, H_N, H_L, H_SL;
float Centroid;

boolean dingin = false;
boolean sejuk = false;
boolean normalc = false;
boolean hangat = false;
boolean panas = false;
boolean Tkering = false;
boolean kering = false;
boolean normalm = false;
boolean lembab = false;
boolean basah = false ;


void fuzzy(float suhu, float kelembaban) {

  miu_dingin = 0;
  miu_sejuk = 0;
  miu_normalc = 0;
  miu_hangat = 0;
  miu_panas = 0;
  miu_Tkering = 0;
  miu_kering = 0;
  miu_normalm = 0;
  miu_lembab = 0;
  miu_basah = 0;
  rule1 = 0; rule2 = 0; rule3 = 0;
  rule4 = 0; rule5 = 0; rule6 = 0;
  rule7 = 0; rule8 = 0; rule9 = 0;
  rule10 = 0; rule11 = 0; rule12 = 0;
  rule13 = 0; rule14 = 0; rule15 = 0;
  rule16 = 0; rule17 = 0; rule18 = 0;
  rule19 = 0; rule20 = 0; rule21 = 0;
  rule22 = 0; rule23 = 0; rule24 = 0;
  rule25 = 0;
  SC = 0; C = 0; N = 0; L = 0; SL = 0;
  H_SC = 0; H_C = 0; H_N = 0; H_L = 0; H_SL = 0;
  Centroid = 0;

  dingin = false;
  sejuk = false;
  normalc = false;
  hangat = false;
  panas = false;
  Tkering = false;
  kering = false;
  normalm = false;
  lembab = false;
  basah = false ;


  Serial.println("===Data masukkan fuzzy===");
  Serial.print("Suhu :");
  Serial.println(suhu);
  Serial.print("Kelembapan : ");
  Serial.println(kelembaban);

  //=====================//suhu//=========================
  //***Label S.Dingin***
  if (suhu == 18) {
    miu_dingin = 1 ;
    dingin = true;
  }
  else if (suhu >= 16 && suhu < 18) {
    miu_dingin = (suhu - 0) / (18 - 0);
    dingin = true;
  }
  else if (suhu > 18 && suhu <= 20) {
    miu_dingin = (20 - suhu) / (20 - 18);
    dingin = true;
  }
  else {
    miu_dingin = 0;
  }

  //***Label Dingin***
  if (suhu == 20.5) {
    miu_sejuk = 1 ;
    sejuk = true;
  }
  else if (suhu >= 19 && suhu < 20.5) {
    miu_sejuk = (suhu - 19) / (20.5 - 19);
    sejuk = true;
  }
  else if (suhu > 20.5 && suhu <= 22) {
    miu_sejuk = (22 - suhu) / (22 - 20.5);
    sejuk = true;
  }
  else {
    miu_sejuk = 0;
  }

  //***Label Normal***
  if (suhu == 24) {
    miu_normalc = 1;
    normalc = true;
  }
  else if (suhu >= 21 && suhu < 24) {
    miu_normalc = (suhu - 21) / (24 - 21);
    normalc = true;
  }
  else if (suhu > 24 && suhu <= 27) {
    miu_normalc = (27 - suhu) / (27 - 24);
    normalc = true;
  }
  else {
    miu_normalc = 0;
  }

  //***Label Hangat***
  if (suhu == 27.5) {
    miu_hangat = 1;
    hangat = true;
  }
  else if (suhu >= 26 && suhu < 27.5) {
    miu_hangat = (suhu - 26) / (27.6 - 26);
    hangat = true;
  }
  else if (suhu > 27.5 && suhu <= 29) {
    miu_hangat = (29 - suhu) / (29 - 27.5);
    hangat = true;
  }
  else {
    miu_hangat = 0;
  }
  ///***Label Panas***
  if (suhu >= 30) {
    miu_panas = 1;
    panas = true;
  }
  else if (suhu >= 28 && suhu < 30) {
    miu_panas = (suhu - 28) / (30 - 28);
    panas = true;
  }
  //else if (suhu >30 && suhu <=32){
  //  miu_panas=(32-suhu)/(32-30);
  //  panas=true;
  //}
  else {
    miu_panas = 0;
  }

  //=================//Kelembaban//=================
  //***label Tkering***
  if (kelembaban == 30 ) {
    miu_Tkering = 1;
    Tkering = true;
  }
  else if (kelembaban >= 19 && kelembaban < 30) {
    miu_Tkering = (kelembaban - 19) / (30 - 19);
    Tkering = true;
  }
  else if (kelembaban > 30 && kelembaban <= 40) {
    miu_Tkering = (40 - kelembaban) / (40 - 30);
    Tkering = true;
  }
  else {
    miu_Tkering = 0;
  }

  //***Label Kering***
  if (kelembaban == 45) {
    miu_kering = 1;
    kering = true;
  }
  else if (kelembaban >= 35 && kelembaban < 45) {
    miu_kering = (kelembaban - 35) / (45 - 35);
    kering = true;
  }
  else if (kelembaban > 45 && kelembaban <= 55) {
    miu_kering = (55 - kelembaban) / (55 - 45);
    kering = true;
  }
  else {
    miu_kering = 0;
  }

  //***Label Normal***
  if (kelembaban == 60 ) {
    miu_normalm = 1;
    normalm = true;
  }
  else if (kelembaban >= 50 && kelembaban < 60) {
    miu_normalm = (kelembaban - 50) / (60 - 50);
    normalm = true;
  }
  else if (kelembaban > 60 && kelembaban <= 70) {
    miu_normalm = (70 - kelembaban) / (70 - 60);
    normalm = true;
  }
  else {
    miu_normalm = 0;
  }

  //***Label lembab***
  if (kelembaban == 75) {
    miu_lembab = 1;
    lembab = true;
  }
  else if (kelembaban >= 65 && kelembaban < 75) {
    miu_lembab = (kelembaban - 65) / (75 - 65);
    lembab = true;
  }
  else if (kelembaban > 75 && kelembaban <= 85) {
    miu_lembab = (85 - kelembaban) / (85 - 75);
    lembab = true;
  }
  else {
    miu_lembab = 0;
  }

  //***Label Sangat Lembab***
  if (kelembaban >= 90) {
    miu_basah = 1;
    basah = true;
  }
  else if (kelembaban >= 80 && kelembaban < 90) {
    miu_basah = (kelembaban - 80) / (90 - 80);
    basah = true;
  }
  //else if (kelembaban >90 && kelembaban <=98){
  //  miu_basah = (98-kelembaban)/(98-90);
  //  basah=true;
  //}
  else {
    miu_basah = 0;
  }

  //===============Tampilan miu=================
  delay(100);
  Serial.println("======SUHU======");
  Serial.print("miu_dingin : ");
  Serial.println(miu_dingin);
  Serial.print("miu_sejuk : ");
  Serial.println(miu_sejuk);
  Serial.print("miu_normal : ");
  Serial.println(miu_normalc);
  Serial.print("miu_hangat : ");
  Serial.println(miu_hangat);
  Serial.print("miu_panas : ");
  Serial.println(miu_panas);
  Serial.println("   ");
  delay(100);
  Serial.println("===KELEMBABAN===");
  Serial.print("miu_Tkering : ");
  Serial.println(miu_Tkering);
  Serial.print("miu_kering : ");
  Serial.println(miu_kering);
  Serial.print("miu_normal : ");
  Serial.println(miu_normalm);
  Serial.print("miu_lembab : ");
  Serial.println(miu_lembab);
  Serial.print("miu_Slembab : ");
  Serial.println(miu_basah);
  Serial.println("   ");
  delay(100);

  //===========Tabel Rule=============
  Serial.println("===Inference Rule & Implikasi Min===");
  if (dingin == true && Tkering == true) {
    rule1 = min(miu_dingin, miu_Tkering);
    Serial.print("rule1 : ");
    Serial.println(rule1);
    delay(100);
  }
  if (dingin == true && kering == true) {
    rule2 = min(miu_dingin, miu_kering);
    Serial.print("rule2 : ");
    Serial.println(rule2);
    delay(100);
  }
  if (dingin == true && normalm == true) {
    rule3 = min(miu_dingin, miu_normalm);
    Serial.print("rule3 : ");
    Serial.println(rule3);
    delay(100);
  }
  if (dingin == true && lembab == true) {
    rule4 = min(miu_dingin, miu_lembab);
    Serial.print("rule4 : ");
    Serial.println(rule4);
    delay(100);
  }
  if (dingin == true && basah == true) {
    rule5 = min(miu_dingin, miu_basah);
    Serial.print("rule5 : ");
    Serial.println(rule5);
    delay(100);
  }
  if (sejuk == true && Tkering == true) {
    rule6 = min(miu_sejuk, miu_Tkering);
    Serial.print("rule6 : ");
    Serial.println(rule6);
    delay(100);
  }
  if (sejuk == true && kering == true) {
    rule7 = min(miu_sejuk, miu_kering);
    Serial.print("rule7 : ");
    Serial.println(rule7);
    delay(100);
  }
  if (sejuk == true && normalm == true) {
    rule8 = min(miu_sejuk, miu_normalm);
    Serial.print("rule8 : ");
    Serial.println(rule8);
    delay(100);
  }
  if (sejuk == true && lembab == true) {
    rule9 = min(miu_sejuk, miu_lembab);
    Serial.print("rule9 : ");
    Serial.print(rule9);
    delay(100);
  }
  if (sejuk == true && basah == true) {
    rule10 = min(miu_sejuk, miu_basah);
    Serial.print("rule10 : ");
    Serial.println(rule10);
    delay(100);
  }
  if (normalc == true && Tkering == true) {
    rule11 = min(miu_normalc, miu_Tkering);
    Serial.print("rule11 : ");
    Serial.println(rule11);
    delay(100);
  }
  if (normalc == true && kering == true) {
    rule12 = min(miu_normalc, miu_kering);
    Serial.print("rule12 : ");
    Serial.println(rule12);
    delay(100);
  }
  if (normalc == true && normalm == true) {
    rule13 = min(miu_normalc, miu_normalm);
    Serial.print("rule13 : ");
    Serial.println(rule13);
    delay(100);
  }
  if (normalc == true && lembab == true) {
    rule14 = min(miu_normalc, miu_lembab);
    Serial.print("rule14 :");
    Serial.println(rule14);
    delay(100);
  }
  if (normalc == true && basah == true) {
    rule15 = min(miu_normalc, miu_basah);
    Serial.print("rule15 :");
    Serial.println(rule15);
    delay(100);
  }
  if (hangat == true && Tkering == true) {
    rule16 = min(miu_hangat, miu_Tkering);
    Serial.print("rule16 :");
    Serial.println(rule16);
    delay(100);
  }
  if (hangat == true && kering == true) {
    rule17 = min(miu_hangat, miu_kering);
    Serial.print("rule17 :");
    Serial.println(rule17);
    delay(100);
  }
  if (hangat == true && normalm == true) {
    rule18 = min(miu_hangat, miu_normalm);
    Serial.print("rule18 :");
    Serial.println(rule18);
    delay(100);
  }
  if (hangat == true && lembab == true) {
    rule19 = min(miu_hangat, miu_lembab);
    Serial.print("rule19 :");
    Serial.println(rule19);
    delay(100);
  }
  if (hangat == true && basah == true) {
    rule20 = min(miu_hangat, miu_basah);
    Serial.print("rule20 :");
    Serial.println(rule20);
    delay(100);
  }
  if (panas == true && Tkering == true) {
    rule21 = min(miu_panas, miu_Tkering);
    Serial.print("rule21 :");
    Serial.println(rule21);
    delay(100);
  }
  if (panas == true && kering == true) {
    rule22 = min(miu_panas, miu_kering);
    Serial.print("rule22 :");
    Serial.println(rule22);
    delay(100);
  }
  if (panas == true && normalm == true) {
    rule23 = min(miu_panas, miu_normalm);
    Serial.print("rule23 :");
    Serial.println(rule23);
    delay(100);
  }
  if (panas == true && lembab == true) {
    rule24 = min(miu_panas, miu_lembab);
    Serial.print("rule24 :");
    Serial.println(rule24);
    delay(100);
  }
  if (panas == true && basah == true) {
    rule25 = min(miu_panas, miu_basah);
    Serial.print("rule25 :");
    Serial.println(rule25);
    delay(100);
  }

  Serial.println("   ");
  Serial.println("===Fungsi Implikasi Max===");
  SC = max(max(rule14, rule5),  max(max(rule9, rule10), rule15));
  C  = max(max(rule4,rule25),rule20);
  N  = max(max(max(rule3, rule8), max(rule13, rule19)), rule24);
  L  = max(max(max(rule2, rule7), max(rule12, rule17)), (max(rule18, rule23)));
  SL = max(max(max(rule1, rule6), max(rule11, rule16)), (max(rule21, rule22)));

  Serial.print("Sangat Cepat: ");
  Serial.println(SC);
  Serial.print("Cepat       : ");
  Serial.println(C);
  Serial.print("Normal      : ");
  Serial.println(N);
  Serial.print("Lama        : ");
  Serial.println(L);
  Serial.print("Sangat Lama : ");
  Serial.println(SL);
  Serial.println("   ");
  delay(100);

  H_SC  = (SC * 5 + 10 + 15 + 20 );
  H_C   = (C * (20 + 25 + 30 + 35 + 40 + 45 + 50 + 55 + 60));
  H_N   = (N * (40 + 45 + 50 + 55 + 60 + 65 + 70 + 75 + 80));
  H_L   = (L * (60 + 65 + 70 + 75 + 80 + 85 + 90 + 95 + 100));
  H_SL  = (SL * (80 + 85 + 90 + 95 + 100 + 105 + 110));

  Centroid = (H_SC + H_C + H_N + H_L + H_SL) / ((SC * 9) + (C * 9) + (N * 9) + (L * 9) + (SL * 7));
  Serial.println("=== Defuzzifikasi ===");
  Serial.print("Centroid : ");
  Serial.println(Centroid);
  Serial.print("\n \n");
  delay(1000);

}
