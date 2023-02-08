float miu_SA, miu_A, miu_N, miu_B, miu_SB;
float miu_D, miu_NP, miu_P;

float R[15];
float HX[15]; // ph down
float HY[15]; // ph up
float HZ[15]; // heater

float HXb[15]; // ph down
float HYb[15]; // ph up
float HZb[15]; // heater

bool SA = false;
bool A = false;
bool N = false;
bool B = false;
bool SB = false;

bool D = false;
bool NP = false;
bool P = false;

float X = 0; //Output aktuator pompa down(hasil def)
float Y = 0; //Outpuit Aktuator pompa up (hasil def)
float Z = 0; //Output Aktuator pemanas (hasil def)

void fuzzy(float ph, float suhu)
{
    //Fuzzyfikasi
    if (ph <= 3)
    {
        miu_SA = 1;
        SA = true;
    }

    if (ph > 2 && ph <= 5)
    {
        miu_SA = (5 - ph) / (5 - 2);
        SA = true;
    }

    if (ph == 5)
    {
        miu_A = 1;
        A = true;
    }

    if (ph >= 2 && ph < 5)
    {
        miu_A = (ph - 2) / (5 - 2);
        A = true;
    }

    if (ph > 5 && ph <= 6.5)
    {
        miu_A = (6.5 - ph) / (6.5 - 5);
        A = true;
    }

    if (ph == 6.5)
    {
        miu_N = 1;
        N = true;
    }

    if (ph >= 5 && ph < 6.5)
    {
        miu_N = (ph - 5) / (6.5 - 5);
        N = true;
    }

    if (ph > 6.5 && ph <= 8)
    {
        miu_N = (8 - ph) / (8 - 6.5);
        N = true;
    }

    if (ph == 9)
    {
        miu_B = 1;
        B = true;
    }

    if (ph >= 6.5 && ph < 9)
    {
        miu_B = (ph - 6.5);
        B = true;
    }

    if (ph > 9 && ph <= 12)
    {
        miu_B = (12 - ph) / (12 - 9);
        B = true;
    }

    if (ph >= 12)
    {
        miu_SB = 1;
        SB = true;
    }

    if (ph < 12 && ph >= 10)
    {
        miu_SB = (ph - 10) / (12 - 10);
        SB = true;
    }

    if (suhu <= 15)
    {
        miu_D = 1;
        D = true;
    }

    if (suhu > 15 && suhu <= 22.5)
    {
        miu_D = (22.5 - suhu) / (22.5 - 15);
        D = true;
    }

    if (suhu == 22.5)
    {
        miu_NP = 1;
        NP = true;
    }

    if (suhu >= 15 && suhu < 22.5)
    {
        miu_NP = (suhu - 15) / (22.5 - 15);
        NP = true;
    }

    if (suhu > 22.5 && suhu <= 30)
    {
        miu_NP = (30 - suhu) / (30 - 22.5);
        NP = true;
    }

    if (suhu >= 30)
    {
        miu_P = 1;
        P = true;
    }

    if (suhu < 30 && suhu >= 22.5)
    {
        miu_P = (suhu - 22.5) / (30 - 22.5);
        P = true;
    }


    //Rule Base fungsi implikasi min
    if (D == true && SA == true)
    {
        R[0] = min(miu_D, miu_SA);
        HX[0] = 40 - (R[0] * 5);
        HY[0] = 10 - (R[0] * 5);
        HZ[0] = 150 - (R[0] * 30);

        HXb[0] = 30 + (R[0] * 5);
        HYb[0] = 0 + (R[0] * 5);
        HZb[0] = 90 + (R[0] * 30);
    }

    if (D == true && A == true)
    {
        R[1] = min(miu_D, miu_A);
        HX[1] = 30 - (R[1] * 5);
        HY[1] = 10 - (R[1] * 5);
        HZ[1] = 150 - (R[1] * 30);

        HXb[1] = 20 + (R[1] * 5);
        HYb[1] = 0 + (R[1] * 5);
        HZb[1] = 90 + (R[1] * 30);
    }

    if (D == true && N == true)
    {
        R[2] = min(miu_D, miu_N);
        HX[2] = 10 - (R[2] * 5);
        HY[2] = 10 - (R[2] * 5);
        HZ[2] = 150 - (R[2] * 30);

        HXb[2] = 0 + (R[2] * 5);
        HYb[2] = 0 + (R[2] * 5);
        HZb[2] = 90 + (R[2] * 30);
    }

    if (D == true && B == true)
    {
        R[3] = min(miu_D, miu_B);
        HX[3] = 10 - (R[3] * 5);
        HY[3] = 20 - (R[3] * 5);
        HZ[3] = 150 - (R[3] * 30);

        HXb[3] = 0 + (R[3] * 5);
        HYb[3] = 10 + (R[3] * 5);
        HZb[3] = 90 + (R[3] * 30);
    }

    if (D == true && SB == true)
    {
        R[4] = min(miu_D, miu_SB);
        HX[4] = 10 - (R[4] * 5);
        HY[4] = 40 - (R[4] * 5);
        HZ[4] = 150 - (R[4] * 30);

        HXb[4] = 0 + (R[4] * 5);
        HYb[4] = 30 + (R[4] * 5);
        HZb[4] = 90 + (R[4] * 30);
    }

    if (NP == true && SA == true)
    {
        R[5] = min(miu_NP, miu_SA);
        HX[5] = 40 - (R[5] * 5);
        HY[5] = 10 - (R[5] * 5);
        HZ[5] = 100 - (R[5] * 35);

        HXb[5] = 30 + (R[5] * 5);
        HYb[5] = 0 + (R[5] * 5);
        HZb[5] = 30 + (R[5] * 35);
    }

    if (NP == true && A == true)
    {
        R[6] = min(miu_NP, miu_A);
        HX[6] = 20 - (R[6] * 5);
        HY[6] = 10 - (R[6] * 5);
        HZ[6] = 100 - (R[6] * 35);

        HXb[6] = 10 + (R[6] * 5);
        HYb[6] = 0 + (R[6] * 5);
        HZb[6] = 30 + (R[6] * 35);
    }

    if (NP == true && SB == true)
    {
        R[7] = min(miu_NP, miu_SB);
        HX[7] = 10 - (R[7] * 5);
        HY[7] = 30 - (R[7] * 5);
        HZ[7] = 100 - (R[7] * 35);

        HXb[7] = 0 + (R[7] * 5);
        HYb[7] = 20 + (R[7] * 5);
        HZb[7] = 30 + (R[7] * 35);
    }

    if (NP == true && B == true)
    {
        R[8] = min(miu_NP, miu_B);
        HX[8] = 10 - (R[8] * 5);
        HY[8] = 20 - (R[8] * 5);
        HZ[8] = 100 - (R[8] * 35);

        HXb[8] = 0 + (R[8] * 5);
        HYb[8] = 10 + (R[8] * 5);
        HZb[8] = 30 + (R[8] * 35);
    }

    if (NP == true && N == true)
    {
        R[9] = min(miu_NP, miu_N);
        HX[9] = 10 - (R[9] * 5);
        HY[9] = 10 - (R[9] * 5);
        HZ[9] = 100 - (R[9] * 35);

        HXb[9] = 0 + (R[9] * 5);
        HYb[9] = 0 + (R[9] * 5);
        HZb[9] = 30 + (R[9] * 35);
    }

    if (P == true && SA == true)
    {
        R[10] = min(miu_P, miu_SA);
        HX[10] = 40 - (R[10] * 5);
        HY[10] = 10 - (R[10] * 5);
        HZ[10] = 50 - (R[10] * 25);

        HXb[10] = 30 + (R[10] * 5);
        HYb[10] = 0 + (R[10] * 5);
        HZb[10] = 0 + (R[10] * 25);
    }

    if (P == true && A == true)
    {
        R[11] = min(miu_P, miu_A);
        HX[11] = 20 - (R[11] * 5);
        HY[11] = 10 - (R[11] * 5);
        HZ[11] = 50 - (R[11] * 25);

        HXb[11] = 10 + (R[11] * 5);
        HYb[11] = 0 + (R[11] * 5);
        HZb[11] = 0 + (R[11] * 25);
    }

    if (P == true && SB == true)
    {
        R[12] = min(miu_P, miu_SB);
        HX[12] = 10 - (R[12] * 5);
        HY[12] = 40 - (R[12] * 5);
        HZ[12] = 50 - (R[12] * 25);

        HXb[12] = 0 + (R[12] * 5);
        HYb[12] = 30 + (R[12] * 5);
        HZb[12] = 0 + (R[12] * 25);
    }

    if (P == true && B == true)
    {
        R[13] = min(miu_P, miu_B);
        HX[13] = 10 - (R[13] * 5);
        HY[13] = 20 - (R[13] * 5);
        HZ[13] = 50 - (R[13] * 25);

        HXb[13] = 0 + (R[13] * 5);
        HYb[13] = 10 + (R[13] * 5);
        HZb[13] = 0 + (R[13] * 25);
    }

    if (P == true && N == true)
    {
        R[14] = min(miu_P, miu_N);
        HX[14] = 10 - (R[14] * 5);
        HY[14] = 10 - (R[14] * 5);
        HZ[14] = 50 - (R[14] * 25);

        HXb[14] = 0 + (R[14] * 5);
        HYb[14] = 0 + (R[14] * 5);
        HZb[14] = 0 + (R[14] * 25);
    }

    //Defuzzyfikasi 
    float Xi = 0;
    float xi = 0;
    float Yi = 0;
    float yi = 0;
    float Zi = 0;
    float zi = 0;

    float Xib = 0;
    float xib = 0;
    float Yib = 0;
    float yib = 0;
    float Zib = 0;
    float zib = 0;

    //Menampilkan hasil fungsi implikasi min
    for (int x = 0; x < 15; x++)
    {
        Serial.print("R ke-" + String(x + 1) + " : ");
        Serial.println(R[x]);
    }

    Serial.println("===========");

    //Menampilkan nilai Zi, Yi, Xi pada metode def CoA
    for (int x = 0; x < 15; x++)
    {
        Serial.print("HX ke-" + String(x + 1) + " : ");
        Serial.println(HX[x]);
        Serial.print("HXb ke-" + String(x + 1) + " : ");
        Serial.println(HXb[x]);
    }

    Serial.println("===========");

    for (int x = 0; x < 15; x++)
    {
        Serial.print("HY ke-" + String(x + 1) + " : ");
        Serial.println(HY[x]);
        Serial.print("HYb ke-" + String(x + 1) + " : ");
        Serial.println(HYb[x]);
    }

    Serial.println("===========");

    for (int x = 0; x < 15; x++)
    {
        Serial.print("HZ ke-" + String(x + 1) + " : ");
        Serial.println(HZ[x]);
        Serial.print("HZb ke-" + String(x + 1) + " : ");
        Serial.println(HZb[x]);
    }

    //Fungsi penentuan defuzzyfikasi crisp output rumus CoA
    for (int x = 0; x < 15; x++)
    {
        Xi += (HX[x] * R[x]);
        xi += (R[x]);

        Yi += (HY[x] * R[x]);
        yi += (R[x]);

        Zi += (HZ[x] * R[x]);
        zi += (R[x]);

        Xib += (HXb[x] * R[x]);
        xib += (R[x]);

        Yib += (HYb[x] * R[x]);
        yib += (R[x]);

        Zib += (HZb[x] * R[x]);
        zib += (R[x]);
    }

    X = (Xi + Xib) / (xi + xib);
    Y = (Yi + Yib) / (yi + yib);
    Z = (Zi + Zib) / (zi + zib);

    //Tampilkan nilai hasil defuzzyfikasi
    Serial.println("===========");

    Serial.print("Nilai Xi : ");
    Serial.println(Xi);
    Serial.print("Nilai xi : ");
    Serial.println(xi);

    Serial.print("Nilai Yi : ");
    Serial.println(Yi);
    Serial.print("Nilai yi : ");
    Serial.println(yi);

    Serial.print("Nilai Zi : ");
    Serial.println(Zi);
    Serial.print("Nilai zi : ");
    Serial.println(zi);

    Serial.println("===========");

    Serial.print("Nilai Xib : ");
    Serial.println(Xib);
    Serial.print("Nilai xib : ");
    Serial.println(xib);

    Serial.print("Nilai Yib : ");
    Serial.println(Yib);
    Serial.print("Nilai yib : ");
    Serial.println(yib);

    Serial.print("Nilai Zib : ");
    Serial.println(Zib);
    Serial.print("Nilai zib : ");
    Serial.println(zib);

    Serial.println("===========");

    Serial.print("Nilai pH Down : ");
    Serial.println(X);

    Serial.print("Nilai pH Up : ");
    Serial.println(Y);

    Serial.print("Nilai Pemanas : ");
    Serial.println(Z);
}