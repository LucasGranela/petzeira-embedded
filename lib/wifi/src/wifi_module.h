#ifndef WIFI_MODULE_ESP32_H
#define WIFI_MODULE_ESP32_H

#include "module.h"
#include "application.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Wifi_Module : public Module
{
public:
    Wifi_Module(Application* app);
    ~Wifi_Module();
    void setup();
    void start();
    void loop();
    void exec_action();
    String name();
    float read_value();
    bool action_executed();

private:
    uint8_t* _mac_address;
};

#endif