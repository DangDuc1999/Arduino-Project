#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid[] = "Deviot JSC";
const char* pass[] = "12345679";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  HTTPClient client;
  client.begin("https://rfid-3c0f9-default-rtdb.firebaseio.com/.json");
  int httpCode = client.GET();
  if (httpCode > 0) {
    String payload = client.getString();
    Serial.println(payload);
    client.end();
  }
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
