/*
Created by: Muhammad Afdhol Rizaldi
Helpmet 0.2
*/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

int vs = D4; // Vibration sensor

int FSRpin = A0; //FSR pin
int fsrdata = 0;

// repace your wifi username and password
const char* ssid     = "TP-Link_392E";
const char* password = "25807752";
String fsr_str, vib_str, latbuf, lonbuf,latbufb, lonbufb;

unsigned long myChannelNumber = 1421256;
const char * myWriteAPIKey = "SQZSOC8VVKBCKHC1";

// The TinyGPS++ object
TinyGPSPlus gps;
WiFiClient  client;

// The serial connection to the GPS device
SoftwareSerial ss(4, 5);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
}

void loop()
{
  while (ss.available() > 0)
  if (gps.encode(ss.read()));
  
  long measurements =vibration();
  fsrdata = analogRead(FSRpin);
  delay(500);
  Serial.print(F("Vibration: "));
  Serial.println(measurements);
  Serial.print(F("FSR: "));
  Serial.println(fsrdata);
 if (measurements> 1000 || fsrdata>100)
    {
      if (gps.location.isValid())
      {
        double latitude = (gps.location.lat());
        double longitude = (gps.location.lng());
    
    fsr_str = (String(fsrdata));
    Serial.println(fsr_str);
    vib_str = (String(measurements));
    Serial.println(vib_str);
    latbuf = (String(latitude, 6));
    Serial.println(latbuf);
    lonbuf = (String(longitude, 6));
    Serial.println(lonbuf);

    ThingSpeak.setField(1, latbuf);
    ThingSpeak.setField(2, lonbuf);
    ThingSpeak.setField(3, fsr_str);
    ThingSpeak.setField(4, vib_str);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
    delay(5000);
    }
  else{Serial.print(F("INVALID"));}
   
   
   Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
 }
}

long vibration(){
  long measurements=pulseIn (vs, HIGH);  
  return measurements;
}
