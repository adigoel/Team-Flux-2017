#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>

//Radio
RFM69 radio;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  radio.initialize(FREQUENCY, 1, 200);
  radio.setHighPower();
  radio.encrypt("sampleEncryptKey");
}

int packetCount = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (radio.receiveDone())
  {
    Serial.print("#[");
    Serial.print(++packetCount);
    Serial.print(']');
    Serial.print('[');Serial.print(radio.SENDERID);Serial.print("]");
    Serial.print((char*)radio.DATA);
    Serial.print("received succ");
    Serial.println();
  }
}
