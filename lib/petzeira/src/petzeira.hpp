#ifndef PETZEIRA_HPP
#define PETZEIRA_HPP

#include <Arduino.h>
#include "wifi.hpp"

class Petzeira {
public:
    Petzeira();
    ~Petzeira();
    void setup();
    void start();
    void loop();
};

#endif