#ifndef Bitmap_H
#define Bitmap_H

#include <Wire.h>
#include <time.h>

// Phát hiện nền tảng (ESP32 hoặc ESP8266)
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

// Phát hiện loại màn hình (SH1106 hoặc SSD1306)
#include <Adafruit_GFX.h>
#ifdef USE_SSD1306
  #include <Adafruit_SSD1306.h>  // Thư viện cho màn hình SSD1306
  extern Adafruit_SSD1306 oled;
#else
  #include <Adafruit_SH110X.h>   // Thư viện cho màn hình SH1106
  extern Adafruit_SH1106G oled;
#endif
#define SCREEN_ADDRESS 0x3C
// ESP32: SCL-22; SDA-21
// ESP8266: SCL-5(D1); SDA-4(D2)

void checkOled();
void drawBitmap(const uint8_t* bitmap, int16_t x, int16_t y, int16_t width, int16_t height);
void displayConnectWifi(const char* ssid);
void displayConnectedWifi();
void connectWifi(const char* ssid, const char* pass);
void connectedWifi();
void displayWifiAP(const char*ssid, const char* ssidAP);
void checkWifi(const char* ssid, const char* pass);
void displayConnectingNTP();
void displayConnectedNTP();
void displayTime();
void displayTimeSerial();
void updateTime();
bool connectNTP();

#endif
