#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int TXPin = 3, RXPin = 4;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

struct vec2 {
  double x;
  double y;
};
bool found = false;
  // these will hold the start position
vec2 start={0,0};
int index = 0; // index holds where we are in the array
double data[5000]; // this holds our data
void loop()
{
  
  while(ss.available() > 0){
    if(gps.encode(ss.read())){
      // we have data to work with
      double x = gps.location.lat();
      double y = gps.location.lng();
      // we have position, difference from start and the current index
      Serial.print(x,10);
      Serial.print(" ");
      Serial.print(y,10);
      Serial.print(" ");
      Serial.print(x-start.x,10);
      Serial.print(" ");
      Serial.print(y-start.y,10);
      Serial.print(" ");
      Serial.println(index);

      data[index++] = x;
      data[index++] = y;


      
      if(found!= true && fabs(x)>1 && fabs(y) > 1.000){
        start.x=x;
        start.y=y;
        found = true;
      }
      
      
    }
  }
  