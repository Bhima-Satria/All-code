#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <time.h>
const int ChipID = ESP.getChipId();
bool setclockchecked = false;
int setClock()
{
    // config time (GMT +7,daylight saving, server 1, server2, server 3)
    if(setclockchecked == false){ //biar ga tiap dipanggil update ntp
    configTime(7 * 3600, 0, "id.pool.ntp.org", "pool.ntp.org", "time.nist.gov");
    }
    Serial.print("Waiting for NTP time sync: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2)
    {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println("");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    Serial.print("Current time: ");
    Serial.println(asctime(&timeinfo));
    Serial.print("time now : " + now);
    time_t timeSinceEpoch = mktime(&timeinfo);
    Serial.println(timeSinceEpoch+(7*3600));
    return timeSinceEpoch+(7*3600);
}

void sendData(float humid, float temp){
  Serial.println("proses mengirim data");
  BearSSL::WiFiClientSecure client;
    const char *test_root_ca =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\n"
        "A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n"
        "b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\n"
        "MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n"
        "YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\n"
        "aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\n"
        "jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\n"
        "xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n"
        "1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\n"
        "snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\n"
        "U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n"
        "9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\n"
        "BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\n"
        "AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\n"
        "yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n"
        "38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\n"
        "AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\n"
        "DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\n"
        "HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
        "-----END CERTIFICATE-----\n";
    BearSSL::X509List cert(test_root_ca);
    client.setTrustAnchors(&cert);

    HTTPClient https;
    const String urlku = "asia-southeast1-iotum-smartgarden.cloudfunctions.net/telemetrySend";
    https.begin(client, "https://" + urlku + "/" + String(ChipID));
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("X-Timestamp", String(setClock()));
    int httpscode = https.POST("T=" + String(temp) + "&H=" + String(humid));
    if (httpscode > 0)
    {
        Serial.println("HTTP POST : " + httpscode);
        if (httpscode == HTTP_CODE_OK)
        {
            const String &payload = https.getString();
            Serial.println("received payload:\n<<");
            Serial.println(payload);
            Serial.println(">>");
            if (setclockchecked == false){
                setclockchecked = true;
            }
        }
        else
        {
            Serial.println("error " + httpscode);
            Serial.println(String(https.getString()));
        }
    }
}
