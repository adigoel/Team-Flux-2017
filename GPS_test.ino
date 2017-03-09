#include <math.h>

//servos
#include <Servo.h>

//comms
#include <Wire.h>

//humidity
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            54         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

//gyro
#include <L3G.h>

//accelerometer
#include <LSM303.h>
#include <SFE_BMP180.h>

//GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

//IMU
L3G gyro;
LSM303 compass;
SFE_BMP180 pressure;
char report[80];

//sd card
#include <SD.h>
#include <SPI.h>

//declare servos
Servo RightServo;
Servo LeftServo;
//clock for alt speed
unsigned long CurrentTime = millis();
unsigned long ElapsedTime;
unsigned long nofloops = 0;
int backupspd = 0;
double R = 6371.00;

//declare variables
int lastknownlat;
int lastknownlong;
int lastknownalt;
int currentServo = 0;
double latcan;
double longcan;
double latdest;
double longdest;
double canspeed;
double canlatspeed;
double canlongspeed;
int canaltspeed;
double cancourse;
int altcan; //in dm
int altdest; //in dm
int longdist; //in dm
int latdist; //in dm
int altdist; //in dm
int altarray[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  RightServo.attach(9);
  LeftServo.attach(10);
  Serial.begin(9600);
  Wire.begin();
  gyro.enableDefault();
  compass.init();
  compass.enableDefault();
  // Initialize device.
  dht.begin();
  delayMS = 1000;
  ss.begin(GPSBaud);
  RightServo.write(90);
  LeftServo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  String datastring = "";
  //gps
  while (ss.available() > 0) {
    if (gps.encode(ss.read())){
      datastring += String(gps.time.value());
      datastring += ", ";
      /*
      datastring += String(gps.time.hour());
      datastring += ", "
      datastring += String(gps.time.minute());
      datastring += ", ";
      datastring += String(gps.time.second());
      datastring += ", ";
      */
      latcan = gps.location.lat();
      longcan = gps.location.lat();
      canspeed = gps.speed.mps();
      cancourse = gps.course.deg();
      datastring += String(latcan);
      datastring += ", ";
      datastring += String(longcan);
      datastring += ", ";
      datastring += String(gps.altitude.meters());
      datastring += ", ";
      datastring += String(canspeed);
      datastring += ", ";
      datastring += String(cancourse);
      datastring += ", ";
      altcan = gps.altitude.meters()*10; //in dm
      Serial.print("here i am, and the string is ");
      Serial.println(datastring);
    }
    Serial.println("this should print once. ");
  }
  Serial.println("as should this");
  delay(delayMS);
}
