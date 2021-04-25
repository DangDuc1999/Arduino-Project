#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define time_delay 200
/* nRF variable */
#define CE 5
#define CSN 15
#define SCK 17
#define MISO 16
#define MOSI 2
/* end nRF */
char msg[50] = "01\r\n";
char msg1[10] = "10\r\n";
char msg2[10] = "11\r\n";
char msg3[10] = "00\r\n";

// RF24(uint16_t _cepin, uint16_t _cspin, uint16_t sck, uint16_t miso, uint16_t mosi)
//RF24 radio(12, 14, 26, 25, 27);
//RF24 radio(33, 15, 14, 12, 13);//Quan
RF24 radio(CE, CSN, SCK, MISO, MOSI);
const uint64_t addres = 0x11223344AA;

void setup(void) {
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(52);
  radio.setAutoAck(true);
  radio.setPayloadSize(32);
  //  radio.setDataRate(RF24_250KBPS);
  radio.setDataRate(RF24_2MBPS);
  radio.openWritingPipe(addres);
}
void loop(void) {
  radio.write("01\r\n", 4);
  delay(time_delay);
  radio.write(msg1, strlen(msg1));
  delay(time_delay);
  radio.write(msg2, strlen(msg2));
  delay(time_delay);
  radio.write(msg3, strlen(msg3));
  delay(time_delay);
}
