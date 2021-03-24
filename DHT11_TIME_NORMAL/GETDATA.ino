void getDatabase() {
  Firebase.getString(firebaseData, "TextInput/line1", getS);
  oneS(getS);
}
