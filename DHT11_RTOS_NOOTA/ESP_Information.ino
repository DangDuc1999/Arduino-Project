void ESP_Information(void* parameter ) {
  for (int i = 1; i <= 10; i++) {
    json3.clear();
    json3.set("WiFi", WiFi.SSID().c_str());
    json3.set("IP", WiFi.localIP().toString());
    json3.set("Subnet mask", WiFi.subnetMask().toString());
    json3.set("Gateway IP", WiFi.gatewayIP().toString().c_str());
    Firebase.set(firebaseData, "/ESP Information", json3);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(xHandleInfo);
}
