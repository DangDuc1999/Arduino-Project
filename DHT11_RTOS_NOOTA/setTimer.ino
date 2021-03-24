void setTimer(void *parameter) {
  while (1) {
    String Hour, Minute, Second;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return;
    }
    char timeWeekDay[10];
    char timeHour[3];
    char timeMinute[3];
//    char timeSecond[3];
    strftime(timeHour, 3, "%H", &timeinfo);
    strftime(timeWeekDay, 10, "%A", &timeinfo);
    strftime(timeMinute, 3, "%M", &timeinfo);
//    strftime(timeSecond, 3, "%S", &timeinfo);
    Hour = atoi(timeHour);
    Minute = atoi(timeMinute);
//    Second = atoi(timeSecond);
    json4.clear();
    json4.set("Time/Hour", Hour);
    json4.set("Time/Minute", Minute);
//    json4.set("Time/Second", Second);
    Firebase.set(firebaseData, "/ESP Timer", json4);
    vTaskDelay(60000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
