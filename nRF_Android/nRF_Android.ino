#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>

RF24 radio(12, 14, 26, 25, 27);
BTLE btle(&radio);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print("BLE and DHT Starting... ");
  Serial.println("Send Temperature Data over BTLE");
  btle.begin("CD Temp");    // 8 chars max
  Serial.println("Successfully Started");
}

void loop() {                                              
  nrf_service_data buf;
  buf.service_uuid = NRF_TEMPERATURE_SERVICE_UUID;
  buf.value = BTLE::to_nRF_Float(25);

  if (!btle.advertise(0x16, &buf, sizeof(buf))) {
    Serial.println("BTLE advertisement failed..!");
  }
  btle.hopChannel(); 
  delay(2000);
}
