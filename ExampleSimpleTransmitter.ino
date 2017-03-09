#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>

//Radio
RFM69 radio;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.initialize(FREQUENCY, 2, 200);
  radio.setHighPower();
  radio.encrypt("sampleEncryptKey");
}
char payload[50];

void loop() {
  // put your main code here, to run repeatedly:
  int variableToSend;
  variableToSend = 31415;
  sprintf(payload, "I want to send this number: %d", (int)variableToSend);
  Serial.print(payload);
  radio.send(1, payload, 50);
  Serial.println("Send complete");
  delay(500);
}
