#include <SPI.h>
#include <WiFi.h>
#include <MQTT.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <string.h>
#include <WiFiManager.h>
#define runEvery(t) for (static int last;\
                         (int)((int)millis() - last) >= (t);\
                         last += (t))

/* nRF config */
// RF24(uint16_t _cepin, uint16_t _cspin, uint16_t sck, uint16_t miso, uint16_t mosi)
//RF24 radio(12, 14, 26, 25, 27);
//RF24 radio(33, 15, 14, 12, 13);//Quan
RF24 radio(5, 15, 17, 16, 2);
const uint64_t addres = 0x11223344AA;

/* WiFi */
//const char ssid[] = "Async";
//const char password[] = "0211000487252";
/* MQTT */
const char host[] = "test.mosquitto.org";
const int port = 1883;
WiFiClient net;
MQTTClient client;

String topic = "dangduc/esp32"; // Subsribé topic
char message[50];

void setup(void) {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);

  WiFiManager wm;
  //reset settings - for testing
  //   wm.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wm.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wm.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    delay(5000);
  }
  //if you get here you have connected to the WiFi
  Serial.println("Almost Reaady");
  Serial.println();
  nRF24_config();

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin(host, port, net);
  client.onMessage(messageReceived);

  connect();
  client.subscribe(topic);
}
void loop(void) {

  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    connect();
    client.subscribe(topic);
  }
}
