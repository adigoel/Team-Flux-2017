#include <qbcan.h>

#define NODEID  1
#define NETID   200

//New Radio Object
RFM69 telemetry;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  telemetry.initialize(FREQUENCY, NODEID, NETID);
  telemetry.setHighPower();
  telemetry.encrypt("sampleEncryptKey");
}

int packetCount = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (telemetry.receiveDone())
  {
    //Serial.print("#[");
    //Serial.print(++packetCount);
    //Serial.print(']');
    Serial.print('[');Serial.print(telemetry.SENDERID);Serial.print("]");
    Serial.print((char*)telemetry.DATA);
    //Serial.print("received succ");
    Serial.println();
  }
}

void serialEvent() {
  
}

