#include "Header.h"

// Thông tin wifi
const char* ssid = "YOUR_SSID";
const char* pass = "YOUR_PASS";

void setup() {
  Serial.begin(115200);
  checkOled();
  connectWifi(ssid, pass);
  displayConnectingNTP();
  if (connectNTP()) {
    displayConnectedNTP();
  } else {
    Serial.println("Failed to connect to NTP server");
  }
}

void loop() {
  checkWifi(ssid, pass);
  displayTime();
  //displayTimeSerial();
}
