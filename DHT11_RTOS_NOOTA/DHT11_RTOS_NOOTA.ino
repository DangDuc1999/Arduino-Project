#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <DHT.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
//Time
#include<time.h>
// Time  var
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 3600;
//
const int DHTPIN = 15;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;
FirebaseJson json2; // DHT11
FirebaseJson json3; // ESP information
FirebaseJson json4; // Time
//FirebaseJsonData jsonData;
//FirebaseJsonArray arr1;
#define FIREBASE_HOST "duc-bkhn-k62.firebaseio.com/"
#define FIREBASE_AUTH "MOAca0CPWTTT7uXKQ7ULUbHBHo4Fs80bZDoN91ze"
char ssid[] = "IPS";
char pass[] = "0211000487252";
String getS;
//RTOS
TaskHandle_t xHandleInfo = NULL;
void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    ESP.restart();
  }
  //Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Mac Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Subnet mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP().toString().c_str());
  Serial.println("Almost Reaady");
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  xTaskCreatePinnedToCore(setTimer, "SetTimer", 10240, NULL, 5, NULL, 0);
  xTaskCreatePinnedToCore(ESP_Information, "ESP Infor", 10240, NULL, 3, &xHandleInfo, 1);
  xTaskCreatePinnedToCore(DHT_Task, "DHT11", 10240, NULL, 4, NULL, 1);
  configASSERT(xHandleInfo);
}

void loop() {
}
