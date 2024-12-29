#include "CaptivePortal.h"

// Constructor
CaptivePortal::CaptivePortal(const char *ssid, const char *password)
    : ap_ssid(ssid), ap_password(password), server(80) {}

// Start the captive portal
void CaptivePortal::begin() {
    // Start Wi-Fi in AP mode
    WiFi.softAP(ap_ssid, ap_password);
    Serial.println("Access Point started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Start DNS Server
    dnsServer.start(53, "*", WiFi.softAPIP());

    // Configure web server routes
    server.on("/", HTTP_GET, [this]() { handleRoot(); });

    // Handle OS probe requests (redirect to root page)
    server.on("/generate_204", HTTP_GET, [this]() { handleRoot(); }); // Android
    server.on("/fwlink", HTTP_GET, [this]() { handleRoot(); });      // Windows
    server.on("/hotspot-detect.html", HTTP_GET, [this]() { handleRoot(); }); // iOS

    // Redirect all other requests to the root page
    server.onNotFound([this]() { handleNotFound(); });

    // Start the web server
    server.begin();
    Serial.println("Web Server started");
}

// Handle client requests
void CaptivePortal::handleClient() {
    dnsServer.processNextRequest();
    server.handleClient();
}

// Serve the root page
void CaptivePortal::handleRoot() {
    const char html[] PROGMEM = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
          <title>Captive Portal</title>
        </head>
        <body>
          <h1>Welcome to the ESP32 Captive Portal!</h1>
          <p>This is a demonstration of a reusable library.</p>
        </body>
        </html>
    )rawliteral";
    server.send(200, "text/html", html);
}

// Redirect all other requests to the root
void CaptivePortal::handleNotFound() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
}
