#ifndef WIFI_HPP
#define WIFI_HPP

#include <Arduino.h>
#include <WiFi.h>

class Wifi {
public:

    static void connectAsAP();
    static void connectAsSTA();
    static void disconnect();
    static void printStatus();

    enum {
        MODE_STA,
        MODE_AP
    };
};

#endif