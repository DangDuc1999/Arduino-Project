#include <MPU6050.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <DHT.h>
#include <string.h>
// OTA
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//End OTA
//Time
#include<time.h>
// Time  var
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 7 * 3600;
String Hour, Minute, Second;
//
const int DHTPIN = 15;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;
FirebaseJson json1; // MPU6050
FirebaseJson json2; // DHT11
FirebaseJson json3; // ESP information wifi
FirebaseJson json4; // Time
//FirebaseJsonData jsonData;
//FirebaseJsonArray arr1;
#define FIREBASE_HOST "duc-bkhn-k62.firebaseio.com/"
#define FIREBASE_AUTH "MOAca0CPWTTT7uXKQ7ULUbHBHo4Fs80bZDoN91ze"
char ssid[] = "IPS";
char pass[] = "0211000487252";
#define runEvery(t) for (static uint16_t last;\
                         (uint16_t)((uint16_t)millis() - last) >= (t);\
                         last += (t))

#define oneS(S) static String s;\
  while(S != s){ Serial.print(F("Text Input: "));\
    Serial.println(S);\
    s = S;}
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int ax, ay, az, tmp, gx, gy, gz;
//float t, h;
String getS;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  ArduinoOTA.setPassword((const char *)"234728");
  Wire.begin();
  Wire.beginTransmission(MPU); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x6B);
  Wire.write(0x00);     //Đưa về 0 để bật MPU
  Wire.endTransmission(true);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  //Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //  printLocalTime();
  //
  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
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
}

void loop() {
  ArduinoOTA.handle();
  runEvery(2000) {
    setTimer();
  }
  runEvery(10000) {
    readDHT11();
    ESP_Infor();
    //    readMPU();
    //    getDatabase();
  }

}
inline void readDHT11() {
  // Nhiet do
  float t, h;
  int core = xPortGetCoreID();
  t = dht.readTemperature();
  h = dht.readHumidity();
  json2.clear();
  json2.set("t", t);
  json2.set("h", h);
  json2.set("Core", core);
  Firebase.set(firebaseData, "/DHT11", json2);
}
void ESP_Infor() {
  int Ram = ESP.getFreeHeap() / 1024;
  int core = xPortGetCoreID();
  json3.clear();
  json3.set("WiFi", WiFi.SSID().c_str());
  json3.set("IP", WiFi.localIP().toString());
  json3.set("Subnet mask", WiFi.subnetMask().toString());
  json3.set("Gateway IP", WiFi.gatewayIP().toString().c_str());
  json3.set("Ram Free", Ram);
  json3.set("Core",core);
  Firebase.set(firebaseData, "/ESP Information", json3);
}
inline void setTimer() {
  Time_Date();
  int core = xPortGetCoreID();
  json4.clear();
  json4.set("Time/Hour", Hour);
  json4.set("Time/Minute", Minute);
  json4.set("Time/Second", Second);
  json4.set("Core",core);
  //  int core = xPortGetCoreID();
  //  json4.set("Hardware/Core", core);
  Firebase.set(firebaseData, "/ESP Timer", json4);
}
void getDatabase() {
  Firebase.getString(firebaseData, "TextInput/line1", getS);
  oneS(getS);
}
