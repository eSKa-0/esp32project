#ifndef CAPTIVE_PORTAL_H
#define CAPTIVE_PORTAL_H

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

class CaptivePortal {
public:
    CaptivePortal(const char *ssid, const char *password);
    void begin();
    void handleClient();

private:
    const char *ap_ssid;
    const char *ap_password;

    DNSServer dnsServer;
    WebServer server;

    void handleRoot();
    void handleNotFound();
};

#endif // CAPTIVE_PORTAL_H
