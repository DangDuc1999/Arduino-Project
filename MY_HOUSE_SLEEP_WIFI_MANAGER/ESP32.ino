void ESP_Infor() {
  json3.clear();
  json3.set("WiFi", WiFi.SSID().c_str());
  json3.set("IP", WiFi.localIP().toString());
  json3.set("Subnet mask", WiFi.subnetMask().toString());
  json3.set("Gateway IP", WiFi.gatewayIP().toString().c_str());
  Firebase.set(firebaseData, "/ESP Information", json3);
}
