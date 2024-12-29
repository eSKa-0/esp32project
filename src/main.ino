#include "BLESpammer.h"
#include "WiFiCache.h"
#include "CaptivePortal.h"
#include "WiFiDeauth.h"

const char *ssid = "CapPortalTest";
const char *password = "";

WiFiCache wifiCache;
WiFiDeauth deauth;
BLESpammer spammer;
CaptivePortal captivePortal(ssid, password);

bool run = true;

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1') {
      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      while (run) {
        wifiCache.scanNetworks();
        delay(10000);
      }
    }
  }
}