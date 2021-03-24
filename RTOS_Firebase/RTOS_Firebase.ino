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
// Variables
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int ax, ay, az, tmp, gx, gy, gz;
String getS;
//RTOS
TaskHandle_t xHandleInfo = NULL;
void setup() {
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
    ESP.restart();
  }
  //Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
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
  xTaskCreatePinnedToCore(setTimer, "SetTimer", 10000, NULL, 5, NULL, 0);
  xTaskCreatePinnedToCore(ESP_Information, "ESP Information", 10240, NULL, 3, &xHandleInfo, 1);
  xTaskCreatePinnedToCore(DHT_Task, "DHT11", 5120, NULL, 4, NULL, 1);
  //  xTaskCreatePinnedToCore(MPU_Task, "MPU6050", 10000, NULL, 1, NULL, 1);

  configASSERT(xHandleInfo);
}

void loop() {
  ArduinoOTA.handle();

}
inline void setTimer(void *parameter) {
  while (1) {
    String Hour, Minute, Second;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return;
    }
    char timeWeekDay[10];
    char timeHour[3];
    char timeMinute[3];
    char timeSecond[3];
    strftime(timeHour, 3, "%H", &timeinfo);
    //  Serial.println(timeHour);
    strftime(timeWeekDay, 10, "%A", &timeinfo);
    strftime(timeMinute, 3, "%M", &timeinfo);
    strftime(timeSecond, 3, "%S", &timeinfo);
    Hour = atoi(timeHour);
    Minute = atoi(timeMinute);
    Second = atoi(timeSecond);
    int core = xPortGetCoreID();
    json4.clear();
    json4.set("Time/Hour", Hour);
    json4.set("Time/Minute", Minute);
    json4.set("Time/Second", Second);
    json4.set("Core", core);
    Firebase.set(firebaseData, "/ESP Timer", json4);
    Serial.println("Set timer running");
    Serial.println(millis());
    vTaskDelay(1800 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
void MPU_Task(void* parameter) {
  while (1) {
    mpu();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
void ESP_Information(void* parameter ) {
  for (int i = 1; i <= 10; i++) {
    int Ram = ESP.getFreeHeap() / 1024;
    int core = xPortGetCoreID();
    json3.clear();
    json3.set("WiFi", WiFi.SSID().c_str());
    json3.set("IP", WiFi.localIP().toString());
    json3.set("Subnet mask", WiFi.subnetMask().toString());
    json3.set("Gateway IP", WiFi.gatewayIP().toString().c_str());
    json3.set("Ram Free", Ram);
    json3.set("Core", core);
    Firebase.set(firebaseData, "/ESP Information", json3);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(xHandleInfo);
}
void DHT_Task(void* prm) {
  while (1) {
    float t, h;
    int core = xPortGetCoreID();
    t = dht.readTemperature();
    h = dht.readHumidity();
    json2.clear();
    json2.set("t", t);
    json2.set("h", h);
    json2.set("Core", core);
    Firebase.set(firebaseData, "/DHT11", json2);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
