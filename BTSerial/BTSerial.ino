#include <SoftwareSerial.h>

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define Led 2
#define Relay1 13

SoftwareSerial mySerial(18, 19); // RX, TX

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  SerialBT.begin("ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(Led, OUTPUT);
  pinMode(Relay1, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.println(Serial.readString());
    //    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    String string = SerialBT.readString();
    Serial.println(string);
    mySerial.println(string);
    //    Serial.write(string);
    if (string == "1") {
      digitalWrite(Led, HIGH);
      digitalWrite(Relay1, HIGH);
    }
    if (string == "0") {
      digitalWrite(Led, LOW);
      digitalWrite(Relay1, LOW);
    }
  }
  delay(20);
}
