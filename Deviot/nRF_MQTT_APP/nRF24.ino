void nRF24_config(){
  radio.begin();
  radio.setChannel(52);
  radio.setAutoAck(false);
  radio.setPayloadSize(32);
  //  radio.setDataRate(RF24_250KBPS);
  radio.setDataRate(RF24_2MBPS);
  radio.openWritingPipe(addres);
}
