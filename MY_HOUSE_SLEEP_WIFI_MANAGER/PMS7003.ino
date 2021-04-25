void readPMS7003() {
  Serial.println("Send read request...");
  pms.requestRead();

  Serial.println("Wait max. 1 second for read...");
  if (pms.readUntil(data))
  {        
    pm1 = data.PM_AE_UG_1_0;              
   
    pm2_5 = data.PM_AE_UG_2_5;
 
    pm10 = data.PM_AE_UG_10_0; 
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);
  }
  else
  {
    Serial.println("No data.");
  }    
  //  while (Serial2.available()) Serial2.read();
  json6.clear();
  json6.set("/pm1", pm1);
  json6.set("/pm25", pm2_5);
  json6.set("/pm10", pm10);
  Firebase.set(firebaseData, "/PMS7003/Current", json6);
  Firebase.set(firebaseData, "/PMS7003/History/" + Date() + "/" + String(Time_Date()), json6);

}
