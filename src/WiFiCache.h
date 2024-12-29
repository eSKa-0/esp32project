#ifndef WIFICACHE_H
#define WIFICACHE_H

#include <WiFi.h>

#define MAX_NETWORKS 20

struct NetworkInfo {
    String ssid;
    String bssid;
    int channel;
    int rssi;
};

class WiFiCache {
public:
    WiFiCache();

    void scanNetworks();
    void displayCachedNetworks();
    bool isNetworkCached(const String& bssid);
    void cacheNetwork(const String& ssid, const String& bssid, int channel, int rssi);

private:
    NetworkInfo networkCache[MAX_NETWORKS];
    int cachedCount;
};

#endif
