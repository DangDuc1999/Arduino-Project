int Time_Date() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return 0;
  }
  char timeHour[3];
  char timeMinute[3];
  //  char timeSecond[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  strftime(timeMinute, 3, "%M", &timeinfo);
  //  strftime(timeSecond, 3, "%S", &timeinfo);
  Hour = atoi(timeHour); // convert to int
  Minute = atoi(timeMinute);
  int Time = Hour * 60 + Minute;
  //  Second = atoi(timeSecond);
  return Time;
}
String STime_Date() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return "";
  }
  char timeHour[3];
  char timeMinute[3];
  //  char timeSecond[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  strftime(timeMinute, 3, "%M", &timeinfo);
  //  strftime(timeSecond, 3, "%S", &timeinfo);
  Hour = atoi(timeHour); // convert to int
  Minute = atoi(timeMinute);
  int Time = Hour * 60 + Minute;
  String STime = String(Hour) + " : " + String(Minute);
  return STime;
}

String Date() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return "";
  }
  char timeDay[5];
  char timeMonth[12];
  char timeYear[5];
  String Day,Month,Year;
  strftime(timeDay, 5, "%d", &timeinfo);
  strftime(timeMonth, 12, "%B", &timeinfo);
  strftime(timeYear, 5, "%Y", &timeinfo);
  Day = String(timeDay);
  Month = String(timeMonth);
  Year = String(timeYear);
  return Day + " " + Month+ " " + Year;
}
void setDateTime(String day, String month, String year) {
  json4.clear();
  json4.set("Date/Day", day);
  json4.set("Date/Month", month);
  json4.set("Date/Year", year);
  Firebase.set(firebaseData, "/ESP Time", json4);
}
