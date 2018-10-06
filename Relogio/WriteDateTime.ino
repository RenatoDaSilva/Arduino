void writeDate() {
  writeSegment(3, 0, day, 2);
  writeSegment(6, 0, month, 2);
  writeSegment(9, 0, year, 4);
}

void writeTime() {
  writeSegment(4, 1, hour, 2);
  writeSegment(7, 1, minute, 2);
  writeSegment(10, 1, second, 2);
}

void writeSegment(int row, int col, int value, int zeroes) {
  lcd.setCursor(row, col);
  lcd.print(format(value, zeroes));
}