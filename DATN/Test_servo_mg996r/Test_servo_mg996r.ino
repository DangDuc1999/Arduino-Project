#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(19);  // (pin, min, max)
}

void loop() {

  //    for (int i = 0 ; i <= 180; i += 90) {
  //      myservo.write(i);
  //      delay(3000);
  //    }
  myservo.write(0);
  delay(2000);
  myservo.write(90);
  delay(2000);
  myservo.write(180);
  delay(2000);
}
