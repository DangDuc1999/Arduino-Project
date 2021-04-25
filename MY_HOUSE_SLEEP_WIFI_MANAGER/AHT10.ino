void ahtRead(){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
//  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
//  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  float t = (float) temp.temperature;
  int h = (int) humidity.relative_humidity;
  json5.clear();
  json5.set("/t", t);
  json5.set("/h", h);
  Firebase.set(firebaseData, "/AHT10/Current", json5);
  Firebase.set(firebaseData, "/AHT10/History/" + Date() + "/" + String(Time_Date()), json5);
}
