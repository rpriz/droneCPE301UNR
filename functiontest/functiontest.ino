#include "gps.h"


//Global variables and definitions
//Adafruit_GPS GPS(&Wire);
//SoftwareSerial APC220(10, 11);
//#define GPSECHO false

//Required Libraries
//#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>


void setup() {
  // Setup GPS module
  setupGPS();
}

void loop() {
  // Read and parse GPS data
  readGPS();
}
