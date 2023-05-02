#ifndef GPS_H
#define GPS_H

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// GPS module object
Adafruit_GPS GPS(&Wire);
// Serial object for APC220 communication
SoftwareSerial APC220(10, 11);

// Define GPSECHO to false to turn off echoing of GPS data to APC220
#define GPSECHO false

// Function to setup GPS module
void setupGPS()
{
  // Connect to APC220
  APC220.begin(9600);
  // Connect to serial monitor for debugging
  Serial.begin(115200);
  // Connect to GPS module on the hardware I2C port
  GPS.begin(0x10);
  // Set NMEA output to recommended minimum RMC and GGA sentences only
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Set update rate to 1Hz
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  // Turn on antenna
  GPS.sendCommand(PGCMD_ANTENNA);
  // Release query mode
  GPS.println(PMTK_Q_RELEASE);
}

// Function to read and parse GPS data
void readGPS()
{
  // Read data from GPS in the main loop
  char c = GPS.read();
  // Send GPS data to APC220 if GPSECHO is true
  if (GPSECHO)
    if (c) APC220.print(c);
  // Parse NMEA sentences
  if (GPS.newNMEAreceived()) {
    // Send GPS data to APC220
    APC220.println(GPS.lastNMEA());
    // If the sentence is successfully parsed, the newNMEAreceived() flag is set to false
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  // Print date
  APC220.print("Date: ");
  APC220.print(GPS.day, DEC);
  APC220.print('/');
  APC220.print(GPS.month, DEC);
  APC220.print("/20");
  APC220.println(GPS.year, DEC);

  // If there is a GPS fix, print location and number of satellites
  if (GPS.fix) {
    APC220.print("Location: ");
    APC220.print(GPS.latitude / 100, 4);
    APC220.print(GPS.lat);
    APC220.print(", ");
    APC220.print(GPS.longitude / 100, 4);
    APC220.println(GPS.lon);
    APC220.print("Satellites: ");
    APC220.println((int)GPS.satellites);
  }
}

#endif // GPS_H
