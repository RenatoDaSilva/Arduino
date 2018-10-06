void ticTac() {
  delay(1000);
  second++;
  if (second == 60) {
    second = 0;
    minute++;
  }
  if (minute == 60) {
    minute = 0;
    hour++;
  }
  if (hour == 24) {
    hour = 0;
    day++;
  }

  incMonthIf();

  if (month == 13) {
    month = 1;
    year++;
  }
}

void incMonthIf() {
  int m;
  boolean change = false;
  switch (month) {
    case 2:
      if (isLeap(year)) {
        change = (day > 29);
      }
      else {
        change = (day > 28);
      }
      break;
    case 4:
      change = (day == 30);
      break;
    case 6:
      change = (day == 30);
      break;
    case 9:
      change = (day == 30);
      break;
    case 11:
      change = (day == 30);
      break;
    default:
      change = (day == 31);
      break;
  }
  if (change == true) {
   month++;
   day = 1;
   } 
}

boolean isLeap(int year) {
  if (year % 4 == 0) {
    if ( year % 100 == 0) {
      return ( year % 400 == 0);
    }
    else
      return true;
  }
  else
    return false;
}