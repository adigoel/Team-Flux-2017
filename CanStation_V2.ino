#include <SPI.h>
#include <Wire.h>
#include <qbcan.h>
#include <string.h>

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
  // this loop collects data from i2c then passes it to data function for transmition
  String variableToSend = "hi, my name is";
  variableToSend += "jeff";
  data(variableToSend);
}

void data(String datastring) {
  datastring.toCharArray(payload, 50);
  telemetry.send(1, payload, 50);
}

