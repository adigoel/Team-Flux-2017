char str[4];

void setup() {
  Serial.begin(9600);
}

void loop() {
  int i=0;

  if (Serial.available()) {
    delay(100); //allows all serial sent to be received together
    while(Serial.available() && i<4) {
      str[i++] = Serial.read();
      Serial.println(str);
    }
    str[i++]='\0';
  }
}
