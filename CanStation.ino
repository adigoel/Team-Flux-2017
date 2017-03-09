#include <SPI.h>
#include <Wire.h>
#include <qbcan.h>

#define NODEID  2
#define NETID   200



//New Radio Object
RFM69 telemetry;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  telemetry.initialize(FREQUENCY, NODEID, NETID);
  telemetry.setHighPower();
  telemetry.encrypt("sampleEncryptKey");

}
char payload[50];

void loop() {
  // put your main code here, to run repeatedly:
  int variableToSend;
  variableToSend = 31415;
  sprintf(payload, "this is %d", variableToSend);
  Serial.print(payload);
  telemetry.send(1, payload, 50);
  Serial.println("Send complete");
  delay(500);
}
