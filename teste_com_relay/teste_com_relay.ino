int in7 = 7;
int in6 = 6;

void setup() {
  Serial.begin(9600);
  pinMode(in7, OUTPUT);
  pinMode(in6, OUTPUT);
  digitalWrite(in7, HIGH);
  digitalWrite(in6, HIGH);
}
void loop() {
//    inverte(in7);
//    inverte(in6);
//    delay(1000);

  entrada();
}

void inverte(int pino) {
  boolean estado = digitalRead(pino);

  estado = not estado;

  Serial.print("Pino ");
  Serial.print(String(pino));
  Serial.print(" com valor ");
  Serial.println(String(estado));

  digitalWrite(pino, estado);
}

void entrada() {
  String inString = "";
  int pino;
  if (Serial.available() > 0) {
    pino = Serial.read();
    inString += (char)pino;
    inverte(inString.toInt());
    inString = "";
  }
}

