#include "wifi.hpp"


int mode;
bool connected;

char* ssidAP = "petzeiraWifi";
char* passwordAP = "petzeiraWifi";

char* ssid = "dudu";
char* password = "duduedudu";


void Wifi::connectAsAP()
{
    Serial.println("Connecting as AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssidAP, passwordAP);
    Serial.println("ssid: " + String(ssidAP));
    Serial.println("password: " + String(passwordAP));
    Serial.print("AP Created with IP Gateway ");
    Serial.println(WiFi.softAPIP());
}

void Wifi::connectAsSTA()
{

}

void Wifi::disconnect()
{

}

void Wifi::printStatus()
{

}
