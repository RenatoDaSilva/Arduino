String format(int valor, int zeros) {
  String v = String(valor);
  if (v.length() < zeros) {
    for (int i = 1; i < zeros; i++) {
      v = "0" + v;
    }
    return v;
  }
  return v;
}
