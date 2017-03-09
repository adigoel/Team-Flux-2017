#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial gps(10, 11); // RX, TX

char line[80]; // received gps line

void setup()
{
  // init console and gps serials
  Serial.begin(38400);
  gps.begin(38400);
}

void loop()
{
   int count = 0; // count the received chars
   char c;
   // at least one char received
   if (gps.available())  
   {
      delay(100);  
      memset(line,0,sizeof(line)); // reset line buffer
      count=0;
      while (gps.available())
      {
  
  c=gps.read(); // Zeichen von Schnittstelle einlesen
  // only ASCII chars are relevant
  if ( c >= 32 && count < sizeof(line)-1) 
  {
    line[count] = c;
    count++;
  }
  else 
  {
    break; // end of line
  }
      }
    }  
    
    // let see what we receive from NL-652ETTL Gps
    Serial.println(line);
}
