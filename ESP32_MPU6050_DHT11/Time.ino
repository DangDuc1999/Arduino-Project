
void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
inline void Time_Date() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  char timeWeekDay[10];
  char timeHour[3];
  char timeMinute[3];
  char timeSecond[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.println(timeHour);
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  strftime(timeMinute, 3, "%M", &timeinfo);
  strftime(timeSecond, 3, "%S", &timeinfo);
  Hour = atoi(timeHour);
  Minute = atoi(timeMinute);
  Second = atoi(timeSecond);
  //    Serial.println(timeWeekDay);
  //    Serial.println(timeMinute);
  //  Serial.println(timeSecond);
  //  Serial.println();
}
