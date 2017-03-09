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

static const int RXPin = 7, TXPin = 8;
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
bool gpsfailed = true;
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
String cantime;



const int chipSelect = BUILTIN_SDCARD;

'
void setup() {
  // put your setup code here, to run once:
  RightServo.attach(9);
  LeftServo.attach(10);
  Serial.begin(9600);
  Wire.begin();
  gyro.enableDefault();
  compass.init();
  compass.enableDefault();
  SD.begin(chipSelect);
  // Initialize device.
  dht.begin();
  delayMS = 1000;
  ss.begin(GPSBaud);
  RightServo.write(90);
  LeftServo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  // datastring is = "gps time, gps lat, gps long, gps alt, gps speed, gps course, gyroX, gyroy, gyroZ, compass, temp, humidity, pressure, long dist, lat dist, alt dist"
  delay(delayMS);
  char status;
  double T, P;
  String datastring = "";
  bool reading = false;
  //gps
  while (ss.available() > 0) {
    gps.encode(ss.read())
    if gps.time.isValid() {
      if gps.time.isUpdated() {
        reading = true;
        cantime = String(gps.time.value);
        gpsfailed = false;
        /*
        datastring += String(gps.time.hour());
        datastring += ", "
        datastring += String(gps.time.minute());
        datastring += ", ";
        datastring += String(gps.time.second());
        datastring += ", ";
        */
      }
      else {
        if (gps.time.age() > 1500) {
          gpsfailed = true;
          reading = true
        }
      }
    }
    if gps.location.isValid() {
      if gps.location.isUpdated() {
        latcan = gps.location.lat();
        longcan = gps.location.lat();
        gpsfailed = false;
//        if (!(gps.location.isUpdated())) {
//          if (gps.location.age() > 2000) {
//            gpsfailed = true;
//          }
//        }
//        else {
//          gpsfailed = false;
//        }
//      }
//      else {
//        gpsfailed = true;
//      }
      }
    }
    else {
      gpsfailed = true;
    }
    if gps.altitude.isValid() {
      if gps.altitude.isUpdated() {
        datastring += String(gps.altitude.meters());
        altcan = gps.altitude.meters()*10; //in dm
        datastring += ", ";
        gpsfailed = false;
      }
    }
    if gps.speed.isValid() {
      if gps.speed.isUpdated() {
        canspeed = gps.speed.mps();
        datastring += String(canspeed);
        datastring += ", ";
        gpsfailed = false;
      }
    }
    if gps.course.isValid() {
      if course.isUpdated() {
        cancourse = gps.course.deg();
        datastring += String(cancourse);
        datastring += ", ";
        gpsfailed = false;
      }
    }
  }
  if reading {
    if gpsfailed {
      datastring += "00000000, 0.0, 0.0, 0, 0, 0";
    }
    else {
      datastring += String(cantime);
      datastring += ", ";
      datastring += String(latcan);
      datastring += ", ";
      datastring += String(longcan);
      datastring += ", ";
    }
      
    //Gyro
    gyro.read();
    datastring += String(gyro.g.x);
    datastring += ", ";
    datastring += String(gyro.g.y);
    datastring += ", ";
    datastring += String(gyro.g.z);
    datastring += ", ";
    //compass
    compass.read();
    datastring += String(compass.heading());
    datastring += ", ";
    //temperature
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    datastring += String(event.temperature);
    datastring += ", ";
    //humidity
    dht.humidity().getEvent(&event);
    datastring+=String(event.relative_humidity);
    //pressure
    status = pressure.getPressure(P,T);
    if (status != 0) {
      datastring += String(P,2);
      datastring += ", ";
    }
    else {
      datastring += "000.00";
      datastring += ", ";
    }
    /*
     * x-axis speed is lat speed
     * x-axis pos is lat dist
     * y-axis speed is long speed
     * y-axis pos is long dist
     * z-axis speed is alt speed
     * z-axis pos is alt dist
     */
  
  /  /logitude dist
  longdist = gpstokm(latdest, longcan, latdest, longdest)*10000; //in dm
  if (longcan < longdest) {
    longdist = -longdist;
  }
  latdist = gpstokm(latcan, longdest, latdest, longdest)*10000; //in dm
  if (latcan < latdest) {
    latdist = -latdist  ;
  }
  altdist = (altcan - altdest) * 10; //in dm
  //sort speed into vectors
  canspeed *= 10; //in dm/s
  canlatspeed = canspeed * cos(cancourse);
  canlongspeed = canspeed * sin(cancourse);
  canaltspeed = altspeed(altdist);
  datastring += String(longdist);
  datastring += ", ";
  datastring += String(latdist);
  datastring += ", ";
  datastring += String(altdist);
  //process data
  data(datastring);
  }
    
  // choose steer  ing algorithm
  if (gpsfailed == false) {  
    
  }
}

void data(String dataToSend) {
  //pass on through i2c
  
  //write to SD
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  dataFile.println(dataToSend);
  dataFile.close();
}

void servoPos(int pos) {
  RightServo.write(90 + (pos/2));
  LeftServo.write(90 - (pos/2));
  currentServo = pos;
}

double gpstokm(double lat1, double lng1, double lat2, double lng2) {
  //This portion converts the current and destination GPS coords from decDegrees to Radians
  double lonR1 = lng1*(PI/180);
  double lonR2 = lng2*(PI/180);
  double latR1 = lat1*(PI/180);
  double latR2 = lat2*(PI/180);
//This portion calculates the differences for the Radian latitudes and longitudes and saves them to variables
  double dlon = lonR2 - lonR1;
  double dlat = latR2 - latR1;
//This portion is the Haversine Formula for distance between two points. Returned value is in KM
  double a = (sq(sin(dlat/2))) + cos(latR1) * cos(latR2) * (sq(sin(dlon/2)));
  double e = 2 * atan2(sqrt(a), sqrt(1-a));
  double d = R * e;
  return d;
}

int altspeed(int alt) {
  if (altarray[5] == 0) {
    for (int i=0; i<6; i++) {
      altarray[i] = alt;
    }
  }
  for (int i = 5; i > 0; i--) {
    altarray[i] = altarray[i-1];
  }
  altarray[0] = alt;
  int startalt = (altarray[0] + altarray[1] + altarray[2])/3;
  int endalt = (altarray[3] + altarray[4] + altarray[5])/3;
  int totaldiff = startalt - endalt;
  if ((nofloops % 3) == 0) {
    ElapsedTime = millis() - CurrentTime;
    int muhsped = (totaldiff / (ElapsedTime*1000)); //dm/s
    CurrentTime = millis();
    backupspd = muhsped;
    return(muhsped);
  }
  else {
    return(backupspd);
  }
}

void DeathSpiral(String dir) {
  if (dir == "L") {
    servoPos(180);
  }
  else if (dir == "R") {
    servoPos(-180);
  }
  else {
    if (currentServo <= 0) {
      servoPos(180);
    }
    else {
      servoPos(-180);
    }
  }
}

