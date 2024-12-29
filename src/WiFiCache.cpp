#include "WiFiCache.h"

WiFiCache::WiFiCache() : cachedCount(0) {}

bool WiFiCache::isNetworkCached(const String& bssid) {
    for (int i = 0; i < cachedCount; i++) {
        if (networkCache[i].bssid == bssid) {
            return true; // Network is already cached
        }
    }
    return false; // Network is not cached
}

void WiFiCache::cacheNetwork(const String& ssid, const String& bssid, int channel, int rssi) {
    if (cachedCount < MAX_NETWORKS) {
        networkCache[cachedCount] = {ssid, bssid, channel, rssi};
        cachedCount++;
    }
}

void WiFiCache::displayCachedNetworks() {
    Serial.println("\nCached Networks:");
    for (int i = 0; i < cachedCount; i++) {
        Serial.printf("SSID: %s\n", networkCache[i].ssid.c_str());
        Serial.printf("BSSID: %s\n", networkCache[i].bssid.c_str());
        Serial.printf("Channel: %d\n", networkCache[i].channel);
        Serial.printf("RSSI: %d dBm\n", networkCache[i].rssi);
        Serial.println("-----------------------");
    }
}

void WiFiCache::scanNetworks() {
    int numNetworks = WiFi.scanNetworks();
    if (numNetworks == 0) {
        Serial.println("No networks found.");
    } else {
        for (int i = 0; i < numNetworks; i++) {
            String ssid = WiFi.SSID(i);
            String bssid = WiFi.BSSIDstr(i);
            int channel = WiFi.channel(i);
            int rssi = WiFi.RSSI(i);

            if (!isNetworkCached(bssid)) {
                Serial.printf("New network found: SSID: %s, BSSID: %s, Channel: %d, RSSI: %d dBm\n",
                              ssid.c_str(), bssid.c_str(), channel, rssi);
                cacheNetwork(ssid, bssid, channel, rssi);
            }
        }
    }

    WiFi.scanDelete();
}
