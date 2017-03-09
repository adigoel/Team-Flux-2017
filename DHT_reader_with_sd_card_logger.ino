//humidity
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
//sd card
#include <SD.h>
#include <SPI.h>
//humidity
#define DHTPIN            54         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

const int chipSelect = BUILTIN_SDCARD;

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  Serial.begin(9600); 
  SD.begin(chipSelect);
  // Initialize device.
  dht.begin();
  delayMS = 200;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  
  String dataString ="";
  
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  Serial.print("Temperature: ");
  Serial.print(event.temperature);
  Serial.println(" *C");
  dataString+=String(event.temperature);
  dataString+=",";
  
  dht.humidity().getEvent(&event);
  Serial.print("Humidity: ");
  Serial.print(event.relative_humidity);
  Serial.println("%");
  dataString+=String(event.relative_humidity);
  

  Serial.println(dataString);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (! dataFile){Serial.println("can't open a file");}
  dataFile.println(dataString);
  dataFile.close();
   
}


