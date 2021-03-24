void readMPU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  float r;
  r = sqrt(pow(AcX, 2) + pow(AcY, 2) + pow(AcZ, 2));
  ax = (PI / 2 - acos(AcX / r)) * RAD_TO_DEG;
  ay = (PI / 2 - acos(AcY / r)) * RAD_TO_DEG;
  az = acos(AcZ / r) * RAD_TO_DEG;
  gx = GyX / 131;
  gy = GyY / 131;
  gz = GyZ / 131;
  json1.clear();
  json1.set("AcX", ax);
  json1.set("AcY", ay);
  json1.set("AcZ", az);
  json1.set("GyX", gx);
  json1.set("GyY", gy);
  json1.set("GyZ", gz);
  Firebase.set(firebaseData, "/MPU6050", json1);
}
