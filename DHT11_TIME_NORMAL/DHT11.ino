void readDHT11() {
  // Nhiet do
  int t, h;
  t = dht.readTemperature();
  h = dht.readHumidity();
  json2.clear();
  //  json2.set("t", t);
  //  json2.set("h", h);
  //  json2.set("History/" + String(Time_Date()) + "/t", t);
  //  json2.set("History/" + String(Time_Date()) + "/h", h);
  json2.set("/t", t);
  json2.set("/h", h);
  Firebase.set(firebaseData, "/DHT11/Current", json2);
  Firebase.set(firebaseData, "/DHT11/History/" + Date() + "/" + String(Time_Date()), json2);
}

//void readDHT11() {
//  // Nhiet do
//  int t, h;
//  t = dht.readTemperature();
//  h = dht.readHumidity();
//  int count = 0;
//  for (int i = 0; i < 200; i++) {
//    count++;
//    json2.clear();
//    json2.set("/t", t + count);
//    json2.set("/h", h + count);
//    Firebase.set(firebaseData, "/DHT11/Current", json2);
//    Firebase.set(firebaseData, "/DHT11/History/" + Date() +"/"+ count, json2);
//  }
//}
