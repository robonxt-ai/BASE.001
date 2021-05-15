/*
    Blynk code for BASE.001
    ------
    A (start from small)™ program
    ------
    Designed for version: humanoid_ESP_v2021.4.1.ino
    Last modified: 2021.04.14
    Programmer: robonxt
    ------
    Changelogs:
    2021.04.14: Initial commit.

*/

void setupBlynk()
{

    // You should get Auth Token in the Blynk App.
    // Go to the Project Settings (nut icon).
    char auth[] = "YOURAUTHTOKENHERE";

    // Your WiFi credentials.
    // Set password to "" for open networks.
    char ssid[] = "NETWORKSSID";
    char pass[] = "NETWOKRPASS";

    Debug.print(DBG_INFO, F("- Blynk setup %s -"), "START");
    Blynk.begin(auth, ssid, pass);
    // You can also specify server:
    //Blynk.begin(auth, ssid, pass);
    //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
    //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
    hbLED.off();
    errLED.off();
    isBusyLED.off();
    isTipLED.off();
    Debug.print(DBG_INFO, F("- Blynk setup %s -"), "DONE");
}

void sendBlynkData()
{
    hbLED.on();
    Blynk.virtualWrite(V1, mpu.GetAngX());
    Blynk.virtualWrite(V2, mpu.GetAngY());
    Blynk.virtualWrite(V3, mpu.GetAngZ());
    hbLED.off();
}
