float miu_NE_S, miu_N_S, miu_PE_S;
float miu_NE_U, miu_N_U, miu_PE_U;
float miu_NE_T, miu_N_T, miu_PE_T;

float rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9;
float rule10, rule11, rule12, rule13, rule14, rule15, rule16, rule17, rule18;
float rule19, rule20, rule21, rule22, rule23, rule24, rule25, rule26, rule27;

float hrule1, hrule2, hrule3, hrule4, hrule5, hrule6, hrule7, hrule8, hrule9;
float hrule10, hrule11, hrule12, hrule13, hrule14, hrule15, hrule16, hrule17, hrule18;
float hrule19, hrule20, hrule21, hrule22, hrule23, hrule24, hrule25, hrule26, hrule27;

float Z = 0;
float prediksi = 0;

boolean NE_S  = false;
boolean N_S   = false;
boolean PE_S  = false;

boolean NE_U  = false;
boolean N_U   = false;
boolean PE_U  = false;

boolean NE_T  = false;
boolean N_T   = false;
boolean PE_T  = false;

void setup() {
  Serial.begin(115200);
}
void loop() {
  fuzzy(0.30, 1.20, 1.40, 20);
  delay(10000);
}
void fuzzy(float in_suhu, float in_udara, float in_tanah, float in_harga) {
  //fuzzy
  Serial.println("=== Data Untuk Fuzzy ===");
  Serial.print("Suhu : ");
  Serial.println(in_suhu);
  Serial.print("Udara : ");
  Serial.println(in_udara);
  Serial.print("Tanah : ");
  Serial.println(in_tanah);
  Serial.print("Harga Komoditi : ");
  Serial.println(in_harga);

  //***** SUHU *****
  //=== MIU NE ===
  if (in_suhu <= -1.5) {
    miu_NE_S = 1;
    NE_S = true;
  }
  else if (in_suhu > -1.5 && in_suhu < 0) {
    miu_NE_S = (0 - (in_suhu)) / (0 - (-1.5));
    NE_S = true;
  }
  else {
    miu_NE_S = 0;
  }

  //=== MIU N ===
  if (in_suhu == 0) {
    miu_N_S = 1;
    N_S = true;
  }
  else if (in_suhu > -1.5 && in_suhu < 0) {
    miu_N_S = ((in_suhu) - (-1.5)) / (0 - (-1.5));
    N_S = true;
  }
  else if (in_suhu > 0 && in_suhu < 1.5) {
    miu_N_S = (1.5 - (in_suhu)) / (1.5 - 0);
    N_S = true;
  }
  else {
    miu_N_S = 0;
  }

  //=== MIU PE ===
  if (in_suhu >= 1.5) {
    miu_PE_S = 1;
    PE_S = true;
  }
  else if (in_suhu > 0 && in_suhu < 1.5) {
    miu_PE_S = (in_suhu - 0) / (1.5 - 0);
    PE_S = true;
  }
  else {
    miu_PE_S = 0;
  }

  //***** KELEMBAPAN TANAH *****
  //=== MIU NE ===
  if (in_tanah <= -5) {
    miu_NE_T = 1;
    NE_T = true;
  }
  else if (in_tanah > -5 && in_tanah < 0) {
    miu_NE_T = (0 - (in_tanah)) / (0 - (-5));
    NE_T = true;
  }
  else {
    miu_NE_T = 0;
  }

  //=== MIU N ===
  if (in_tanah == 0) {
    miu_N_T = 1;
    N_T = true;
  }
  else if (in_tanah < 0 && in_tanah > -5) {
    miu_N_T = (in_tanah - (-5)) / (0 - (-5));
    N_T = true;
  }
  else if (in_tanah > 0 && in_tanah < 5) {
    miu_N_T = (5 - (in_tanah)) / (5 - 0);
    N_T = true;
  }
  else {
    miu_N_T = 0;
  }

  //=== MIU PE ===
  if (in_tanah >= 5) {
    miu_PE_T = 1;
    PE_T = true;
  }
  else if (in_tanah > 0 && in_tanah < 5) {
    miu_PE_T = (in_tanah - (0)) / (5 - 0);
    PE_T = true;
  }
  else {
    miu_PE_T = 0;
  }

  //***** KELEMBAPAN UDARA *****
  //=== MIU NE ===
  if (in_udara <= -5) {
    miu_NE_U = 1;
    NE_U = true;
  }
  else if (in_udara > -5 && in_udara < 0) {
    miu_NE_U = (0 - (in_udara)) / (0 - (-5));
    NE_U = true;
  }
  else {
    miu_NE_U = 0;
  }

  //=== MIU N ===
  if (in_udara == 0) {
    miu_N_U = 1;
    N_U = true;
  }
  else if (in_udara > -5 && in_udara < 0) {
    miu_N_U = (in_udara - (-5)) / (0 - (-5));
    N_U = true;
  }
  else if (in_udara > 0 && in_udara < 5) {
    miu_N_U = (5 - (in_udara)) / (5 - 0);
    N_U = true;
  }
  else {
    miu_N_U = 0;
  }

  //=== MIU PE ===
  if (in_udara >= 5) {
    miu_PE_U = 1;
    PE_U = true;
  }
  else if (in_udara > 0 && in_udara < 5) {
    miu_PE_U = (in_udara - (0)) / (5 - 0);
    PE_U = true;
  }
  else {
    miu_PE_U = 0;
  }

  Serial.println("=== Nilai MIU ===");
  Serial.println("**miu_ERROR_suhu**");
  Serial.print("miu_NE_S : ");
  Serial.println(miu_NE_S);
  Serial.print("miu_N_S  : ");
  Serial.println(miu_N_S);
  Serial.print("miu_PE_S : ");
  Serial.println(miu_PE_S);
  Serial.println("**miu_ERROR_tanah**");
  Serial.print("miu_NE_T : ");
  Serial.println(miu_NE_T);
  Serial.print("miu_N_T  : ");
  Serial.println(miu_N_T);
  Serial.print("miu_PE_T : ");
  Serial.println(miu_PE_T);
  Serial.println("**miu_ERROR_udara**");
  Serial.print("miu_NE_U : ");
  Serial.println(miu_NE_U);
  Serial.print("miu_N_U  : ");
  Serial.println(miu_N_U);
  Serial.print("miu_PE_U : ");
  Serial.println(miu_PE_U);

  Serial.println("===== Inference Rule =====");

  if (NE_S == true && NE_T == true && NE_U == true) {
    rule1 = min(min(miu_NE_S, miu_NE_T), miu_NE_U);
    Serial.print("Rule 1 : ");
    Serial.print(rule1);
    hrule1 = 55 - (rule1 * (55 - 0));
    Serial.print("   HRule 1 : ");
    Serial.println(hrule1);
  }
  if (NE_S == true && NE_T == true && N_U == true) {
    rule2 = min(min(miu_NE_S, miu_NE_T), miu_N_U);
    Serial.print("Rule 2 : ");
    Serial.print(rule2);
    hrule2 = 55 - (rule2 * (55 - 0));
    Serial.print("   HRule 2 : ");
    Serial.println(hrule2);
  }
  if (NE_S == true && NE_T == true && PE_U == true) {
    rule3 = min(min(miu_NE_S, miu_NE_T), miu_PE_U);
    Serial.print("Rule 3 : ");
    Serial.print(rule3);
    hrule3 = 55 - (rule3 * (55 - 0));
    Serial.print("   HRule 3 : ");
    Serial.println(hrule3);
  }
  if (NE_S == true && N_T == true && NE_U == true) {
    rule4 = min(min(miu_NE_S, miu_N_T), miu_NE_U);
    Serial.print("Rule 4 :");
    Serial.print(rule4);
    hrule4 = 55 - (rule4 * (55 - 0));
    Serial.print("   HRule 4 : ");
    Serial.println(hrule4);
  }
  if (NE_S == true && N_T == true && N_U == true) {
    rule5 = min(min(miu_NE_S, miu_N_T), miu_N_U);
    Serial.print("Rule 5 :");
    Serial.print(rule5);
    hrule5 = (rule5 * (75 - 50) + 50);
    Serial.print("   HRule 5 : ");
    Serial.println(hrule5);
  }
  if (NE_S == true && N_T == true && PE_U == true) {
    rule6 = min(min(miu_NE_S, miu_N_T), miu_PE_U);
    Serial.print("Rule 6 :");
    Serial.print(rule6);
    hrule6 = 55 - (rule6 * (55 - 0));
    Serial.print("   HRule 6 : ");
    Serial.println(hrule6);
  }
  if (NE_S == true && PE_T == true && NE_U == true) {
    rule7 = min(min(miu_NE_S, miu_PE_T), miu_NE_U);
    Serial.print("Rule 7 :");
    Serial.print(rule7);
    hrule7 = 55 - (rule7 * (55 - 0));
    Serial.print("   HRule 7 : ");
    Serial.println(hrule7);
  }
  if (NE_S == true && PE_T == true && N_U == true) {
    rule8 = min(min(miu_NE_S, miu_PE_T), miu_N_U);
    Serial.print("Rule 8 :");
    Serial.print(rule8);
    hrule8 = 55 - (rule8 * (55 - 0));
    Serial.print("   HRule 8 : ");
    Serial.println(hrule8);
  }
  if (NE_S == true && PE_T == true && PE_U == true) {
    rule9 = min(min(miu_NE_S, miu_PE_T), miu_PE_U);
    Serial.print("Rule 9 :");
    Serial.print(rule9);
    hrule9 = 55 - (rule9 * (55 - 0));
    Serial.print("   HRule 9 : ");
    Serial.println(hrule9);
  }
  if (N_S == true && NE_T == true && NE_U == true) {
    rule10 = min(min(miu_N_S, miu_NE_T), miu_NE_U);
    Serial.print("Rule 10 : ");
    Serial.print(rule10);
    hrule10 = 55 - (rule10 * (55 - 0));
    Serial.print("   HRule 10 : ");
    Serial.println(hrule10);
  }
  if (N_S == true && NE_T == true && N_U == true) {
    rule11 = min(min(miu_N_S, miu_NE_T), miu_N_U);
    Serial.print("Rule 11 : ");
    Serial.print(rule11);
    hrule11 = (rule11 * (75 - 50) + 50);
    Serial.print("   HRule 11 : ");
    Serial.println(hrule11);
  }
  if (N_S == true && NE_T == true && PE_U == true) {
    rule12 = min(min(miu_N_S, miu_NE_T), miu_PE_U);
    Serial.print("Rule 12 : ");
    Serial.print(rule12);
    hrule12 = 55 - (rule12 * (55 - 0));
    Serial.print("   HRule 12 : ");
    Serial.println(hrule12);
  }
  if (N_S == true && N_T == true && NE_U == true) {
    rule13 = min(min(miu_N_S, miu_N_T), miu_NE_U);
    Serial.print("Rule 13 : ");
    Serial.print(rule13);
    hrule13 = (rule13 * (75 - 50) + 50);
    Serial.print("   HRule 13 : ");
    Serial.println(hrule13);
  }
  if (N_S == true && N_T == true && N_U == true) {
    rule14 = min(min(miu_N_S, miu_N_T), miu_N_U);
    Serial.print("Rule 14 : ");
    Serial.print(rule14);
    hrule14 = (rule14 * (100 - 75) + 75);
    Serial.print("   HRule 14 : ");
    Serial.println(hrule14);
  }
  if (N_S == true && N_T == true && PE_U == true) {
    rule15 = min(min(miu_N_S, miu_N_T), miu_PE_U);
    Serial.print("Rule 15 : ");
    Serial.print(rule15);
    hrule15 = (rule15 * (75 - 50) + 50);
    Serial.print("   HRule 15 : ");
    Serial.println(hrule15);
  }
  if (N_S == true && PE_T == true && NE_U == true) {
    rule16 = min(min(miu_N_S, miu_PE_T), miu_NE_U);
    Serial.print("Rule 16 : ");
    Serial.print(rule16);
    hrule16 = 55 - (rule16 * (55 - 0));
    Serial.print("   HRule 16 : ");
    Serial.println(hrule16);
  }
  if (N_S == true && PE_T == true && N_U == true) {
    rule17 = min(min(miu_N_S, miu_PE_T), miu_N_U);
    Serial.print("Rule 17 : ");
    Serial.print(rule17);
    hrule17 = (rule17 * (75 - 50) + 50);
    Serial.print("   HRule 17 : ");
    Serial.println(hrule17);
  }
  if (N_S == true && PE_T == true && PE_U == true) {
    rule18 = min(min(miu_N_S, miu_PE_T), miu_PE_U);
    Serial.print("Rule 18 : ");
    Serial.print(rule18);
    hrule18 = 55 - (rule18 * (55 - 0));
    Serial.print("   HRule 18 : ");
    Serial.println(hrule18);
  }
  if (PE_S == true && NE_T == true && NE_U == true) {
    rule19 = min(min(miu_PE_S, miu_NE_T), miu_NE_U);
    Serial.print("Rule 19 : ");
    Serial.print(rule19);
    hrule19 = 55 - (rule19 * (55 - 0));
    Serial.print("   HRule 19 : ");
    Serial.println(hrule19);
  }
  if (PE_S == true && NE_T == true && N_U == true) {
    rule20 = min(min(miu_PE_S, miu_NE_T), miu_N_U);
    Serial.print("Rule 20 : ");
    Serial.print(rule20);
    hrule20 = 55 - (rule20 * (55 - 0));
    Serial.print("   HRule 20 : ");
    Serial.println(hrule20);
  }
  if (PE_S == true && NE_T == true && PE_U == true) {
    rule21 = min(min(miu_PE_S, miu_NE_T), miu_PE_U);
    Serial.print("Rule 21 : ");
    Serial.print(rule21);
    hrule21 = 55 - (rule21 * (55 - 0));
    Serial.print("   HRule 21 : ");
    Serial.println(hrule21);
  }
  if (PE_S == true && N_T == true && NE_U == true) {
    rule22 = min(min(miu_PE_S, miu_N_T), miu_NE_U);
    Serial.print("Rule 22 : ");
    Serial.print(rule22);
    hrule22 = 55 - (rule22 * (55 - 0));
    Serial.print("   HRule 22 : ");
    Serial.println(hrule22);
  }
  if (PE_S == true && N_T == true && N_U == true) {
    rule23 = min(min(miu_PE_S, miu_N_T), miu_N_U);
    Serial.print("Rule 23 : ");
    Serial.print(rule23);
    hrule23 = (rule23 * (75 - 50) + 50);
    Serial.print("   HRule 23 : ");
    Serial.println(hrule23);
  }
  if (PE_S == true && N_T == true && PE_U == true) {
    rule24 = min(min(miu_PE_S, miu_N_T), miu_PE_U);
    Serial.print("Rule 24 : ");
    Serial.print(rule24);
    hrule24 = 55 - (rule24 * (55 - 0));
    Serial.print("   HRule 24 : ");
    Serial.println(hrule24);
  }
  if (PE_S == true && PE_T == true && NE_U == true) {
    rule25 = min(min(miu_PE_S, miu_PE_T), miu_NE_U);
    Serial.print("Rule 25 : ");
    Serial.print(rule25);
    hrule25 = 55 - (rule25 * (55 - 0));
    Serial.print("   HRule 25 : ");
    Serial.println(hrule25);
  }
  if (PE_S == true && PE_T == true && N_U == true) {
    rule26 = min(min(miu_PE_S, miu_PE_T), miu_N_U);
    Serial.print("Rule 26 : ");
    Serial.print(rule26);
    hrule26 = 55 - (rule26 * (55 - 0));
    Serial.print("   HRule 26 : ");
    Serial.println(hrule26);
  }
  if (PE_S == true && PE_T == true && PE_U == true) {
    rule27 = min(min(miu_PE_S, miu_PE_T), miu_PE_U);
    Serial.print("Rule 27 : ");
    Serial.print(rule27);
    hrule27 = 55 - (rule27 * (55 - 0));
    Serial.print("   HRule 27 : ");
    Serial.println(hrule27);
  }

  float zi = ((hrule1 * rule1) + (hrule2 * rule2) + (hrule3 * rule3) + (hrule4 * rule4) + (hrule5 * rule5) + (hrule6 * rule6) + (hrule7 * rule7) +
              (hrule8 * rule8) + (hrule9 * rule9) + (hrule10 * rule10) + (hrule11 * rule11) + (hrule12 * rule12) + (hrule13 * rule13) + (hrule14 * rule14) +
              (hrule15 * rule15) + (hrule16 * rule16) + (hrule17 * rule17) + (hrule18 * rule18) + (hrule19 * rule19) + (hrule20 * rule20) + (hrule21 * rule21) +
              (hrule22 * rule22) + (hrule23 * rule23) + (hrule24 * rule24) + (hrule25 * rule25) + (hrule26 * rule26) + (hrule27 * rule27));

  float ai = (rule1 + rule2 + rule3 + rule4 + rule5 + rule6 + rule7 + rule8 + rule9 + rule10 + rule11 + rule12 +
              rule13 + rule14 + rule15 + rule16 + rule17 + rule18 + rule19 + rule20 + rule21 + rule22 + rule23 +
              rule24 + rule25 + rule26 + rule27);

  Z = zi / ai;
  prediksi = (in_harga * Z) / 100;

  String kategori;

  Serial.print("Nilai Zi : ");
  Serial.println(zi);
  Serial.print("Nilai ai : ");
  Serial.println(ai);

  if (Z < 55 ) {
    kategori = "buruk";
  }
  else if (Z >= 55 && Z <= 75) {
    kategori = "sedang";
  }
  else {
    kategori = "optimal";
  }

  Serial.print("Defuzzyfikasi : ");
  Serial.println(kategori);
  Serial.print("Nilai : ");
  Serial.println(Z);
  Serial.print("Harga Prediksi : ");
  Serial.println(prediksi);
}
