#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>
#include <FirebaseJson.h>
#include <string.h>
#include <ArduinoJson.h>
StaticJsonDocument<256> doc;
FirebaseData firebaseData;
FirebaseJson json1;
#define FIREBASE_HOST "iot-cam-6db9c.firebaseio.com/"
#define FIREBASE_AUTH "MKS8oFhvZahmNynLXqPXEP3f855WF6n0TMIzhS41"
char ssid[] = "IPS";
char pass[] = "0211000487252";
String getS;
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    ESP.restart();
  }
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
  getDatabase();
  delay(1000);
}
void getDatabase() {
  String LP;
  Firebase.getString(firebaseData, "Number Plate", LP);
  sendData(LP);
}
void sendData(String data) {
  doc["1"] = data;
  serializeJson(doc, Serial2);
//  serializeJson(doc, Serial);
  Serial2.println();
//  Serial.println();
}
