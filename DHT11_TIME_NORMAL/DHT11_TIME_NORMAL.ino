#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <DHT.h>
#include <string.h>
//Time
#include<time.h>
// Time  var
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 3600;
int Hour, Minute, Second;
int th = 0; // Count for DHT11
//
const int DHTPIN = 15;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;

FirebaseJson json2; // DHT11
FirebaseJson json3; // ESP information wifi
FirebaseJson json4; // Time

FirebaseJsonArray arr1;

//FirebaseJsonData jsonData;
//FirebaseJsonArray arr1;
#define FIREBASE_HOST "duc-bkhn-k62.firebaseio.com/"
#define FIREBASE_AUTH "MOAca0CPWTTT7uXKQ7ULUbHBHo4Fs80bZDoN91ze"
char ssid[] = "IPS";
char pass[] = "0211000487252";
#define runEvery(t) for (static int last;\
                         (int)((int)millis() - last) >= (t);\
                         last += (t))

#define oneS(S) static String s;\
  while(S != s){ Serial.print(F("Text Input: "));\
    Serial.println(S);\
    s = S;}
String getS;
void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  //Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //  printLocalTime();
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
  ESP_Infor();
}

void loop() {
  runEvery(1000 * 60 * 30) {
    readDHT11();
  }
}
