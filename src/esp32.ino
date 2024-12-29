/*#include "WiFiCache.h"

WiFiCache wifiCache;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting WiFi Cache Example...");

    WiFi.mode(WIFI_STA);   // Set WiFi to Station mode
    WiFi.disconnect();     // Ensure WiFi is not connected before scanning
}

void loop() {
    wifiCache.scanNetworks(); // Scan for WiFi networks
    delay(10000);             // Wait for 10 seconds before rescanning
}
*/
/*
#include "CaptivePortal.h"

// Set Wi-Fi credentials
const char *ssid = "CapPortalTest";
const char *password = "";

// Create CaptivePortal instance
CaptivePortal captivePortal(ssid, password);

void setup() {
    Serial.begin(115200);
    captivePortal.begin();
}

void loop() {
    captivePortal.handleClient();
}
*/
/*
#include "WiFiDeauth.h"

WiFiDeauth deauth_obj;

void setup() {
  uint8_t newSourceMAC[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFA};
  uint8_t newBSSID[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFB};

  // Set up the deauth
  deauth_obj.setup();

  // Set the new Source MAC and BSSID
  deauth_obj.setTarget(newSourceMAC, newBSSID);
}

void loop() {
  deauth_obj.attack();
}
*/

#include "BLESpammer.h"

BLESpammer spammer_obj;

void setup() {
  spammer_obj.begin();
}

void loop() {
  spammer_obj.startAdvertising();
}
