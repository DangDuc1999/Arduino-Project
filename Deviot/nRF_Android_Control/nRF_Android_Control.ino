#include  <SPI.h>
#include <FirebaseESP32.h>
#include <WiFi.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <WiFiManager.h>
char msg[50] = "Hello\r\n";
// RF24(uint16_t _cepin, uint16_t _cspin, uint16_t sck, uint16_t miso, uint16_t mosi)
RF24 radio(12, 14, 26, 25, 27);
//RF24 radio(33, 15, 14, 12, 13);//Quan
const uint64_t addres = 0x11223344AA;

#define FIREBASE_HOST "deviot-duc-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "4PiXcaJXn14Yq8Ychox0TaY3s4bleDPcruPiQPrN"

#define runEvery(t) for (static int last;\
                         (int)((int)millis() - last) >= (t);\
                         last += (t))
FirebaseData firebaseData;

FirebaseJson json1;

void setup(void) {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  WiFiManager wm;
  radio.begin();
  radio.setChannel(52);
  radio.setAutoAck(false);
  //radio.setPayloadSize(7);
  //  radio.setDataRate(RF24_250KBPS);
  radio.setDataRate(RF24_2MBPS);
  radio.openWritingPipe(addres);
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
    ESP.restart();
    delay(5000);
  }
  //if you get here you have connected to the WiFi
  Serial.println("Almost Reaady");
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
void loop(void) {
  //  Serial.println("send ...");
  String led;
  //  Firebase.getInt(firebaseData, "Ok");
  Firebase.getString(firebaseData, "LED", led);
  Serial.println(led);
  //  Serial.println(firebaseData.intData());
  if (led == "1") {
    radio.write("1\r\n", 3);
  } else if (led == "0") {
    radio.write("0\r\n", 3);
  }
  //  radio.write(msg, strlen(msg));
  delay(100);
}
