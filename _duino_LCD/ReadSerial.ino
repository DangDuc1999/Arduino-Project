void readMySerial() {
  String rev = mySerial.readString();
  String nhan =  mySerial.readStringUntil('}');
  for (int i = 0; i < 1; i++) {
    String data1 = getValue(nhan, ',', i);
    String data2 = getValue(data1, ':', 1);
    //    data[i] = data2.toInt();
    LP = data2;
  }
}
