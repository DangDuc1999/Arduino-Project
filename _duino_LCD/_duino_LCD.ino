#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8);//RX, TX
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String LP;
void setup() {
  mySerial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("License Plate");
  
}

void loop() {
  readMySerial();
  delay(100);
  lcd.setCursor(1, 1);
  lcd.print(LP);
}
