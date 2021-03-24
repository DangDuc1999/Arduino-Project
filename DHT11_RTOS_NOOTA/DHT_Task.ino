void DHT_Task(void* parameter) {
  int i = 0;
  float t;
  int h;
  while (1) {
    char* hisH;
    i++;
    String index = String(i);
    t = dht.readTemperature();
    h = dht.readHumidity();
    //    json2.clear();
    json2.set("t", t);
    json2.set("h", h);
    json2.set("HistoryT/" + index, t);
    json2.set("HistoryH/" + index, h);
    Firebase.set(firebaseData, "/DHT11", json2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
