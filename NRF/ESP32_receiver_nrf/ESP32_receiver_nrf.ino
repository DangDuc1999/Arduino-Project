#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#define led 2
char msg[32];
// RF24(uint16_t _cepin, uint16_t _cspin, uint16_t sck, uint16_t miso, uint16_t mosi)
//RF24 radio(33, 15, 14, 12, 13); // Quan
RF24 radio(12, 14, 26, 25, 27);
uint64_t addres = 0x11223344AA;
void setup(void) {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  radio.begin();
  radio.setChannel(52);
  radio.setAutoAck(false);
  radio.setPayloadSize(32);
  // radio.setDataRate(RF24_250KBPS);
  radio.setDataRate(RF24_2MBPS);
  radio.openReadingPipe(1, addres);
  radio.startListening();
}

void loop(void) {
  if (radio.available()) {
    radio.read(msg, 4);
    Serial.println(msg);
    if (msg[0] == '1') {
      digitalWrite(led, HIGH);
    } else if (msg[0] == '0') {
      digitalWrite(led, LOW);
    }
  }
  else {
    //    Serial.println("No radio available");
  }
  delay(200);
}
