#include <FirebaseESP32.h>
//#include <FirebaseESP32HTTPClient.h>
//#include <FirebaseJson.h>
#include <WiFi.h>
#include <Adafruit_AHT10.h>
//#include <DHT.h>
//#include <string.h>
#include <WiFiManager.h>
//Time
#include<time.h>
#include "PMS.h"

/* PMS7003 */
PMS pms(Serial2);
PMS::DATA data;

Adafruit_AHT10 aht;
/* Time  variable */
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;
/* ************************************** */
//int Hour, Minute, Second;
//int th = 0; // Count for DHT11
/* PMS7003 */
int pm1 = 0;
int pm2_5 = 0;
int pm10 = 0;
/* ************************************** */
/* DHT11 */
//const int DHTPIN = 15;
//const int DHTTYPE = DHT11;
//DHT dht(DHTPIN, DHTTYPE);
/* ************************************* */

FirebaseData firebaseData;

FirebaseJson json2; // DHT11
FirebaseJson json3; // ESP information wifi
FirebaseJson json4; // Time
FirebaseJson json5; // AHT10
FirebaseJson json6; // PMS7003

//FirebaseJsonData jsonData;
//FirebaseJsonArray arr1;
#define FIREBASE_HOST "duc-bkhn-k62.firebaseio.com"
#define FIREBASE_AUTH "MOAca0CPWTTT7uXKQ7ULUbHBHo4Fs80bZDoN91ze"

//const char* SSID = "Async";
//const char* PASS = "0211000487252";

#define runEvery(t) for (static int last;\
                         (int)((int)millis() - last) >= (t);\
                         last += (t))

#define oneS(S) static String s;\
  while(S != s){ Serial.print(F("Text Input: "));\
    Serial.println(S);\
    s = S;}
void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial2.begin(9600);
  //  WiFi.begin(SSID, PASS);
  aht.begin();
  WiFiManager wm;
  //reset settings - for testing
  // wm.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wm.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wm.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    //    ESP.restart();
    delay(5000);
  }
  //if you get here you have connected to the WiFi

  print_wakeup_reason();
  //  esp_sleep_enable_timer_wakeup(time_sleep * us_to_s);
  //  esp_sleep_enable_timer_wakeup(3600000000);
  //  esp_sleep_enable_timer_wakeup(119000);
  //Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //  printLocalTime();
  Serial.println("Almost Reaady");
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  delay(5000);
  ESP_Infor();

  readPMS7003();
  ahtRead();
  //  esp_deep_sleep_start();
}

void loop() {
  runEvery(10000) {
    ahtRead();
    readPMS7003();
  }
  //  delay(1000);
  //  readPMS7003();
  //  ahtRead();
}
