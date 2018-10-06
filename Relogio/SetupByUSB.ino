void setupByUSB() {
  String inString;
  if (Serial.available() > 0) {
    inString = Serial.readString();
    day = inString.substring(1, 2).toInt();
    month = inString.substring(4, 6).toInt();
    year = inString.substring(6, 10).toInt();
    hour = inString.substring(11, 13).toInt();
    minute = inString.substring(14, 16).toInt();
    second = inString.substring(17, 19).toInt();

    Serial.print("Nova data/hora ajustada para ");
    Serial.println(inString);
  }
}