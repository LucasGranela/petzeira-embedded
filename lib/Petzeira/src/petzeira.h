#ifdef EMBEDDED
#ifndef UI_H
#define UI_H

#include "application.h"
#include "food.h"
#include "water.h"
#include "wifi_module.h"

class Petzeira : public Application {
public:
    Petzeira();
    void initialization();
    void startup();
    void read_commands();

private:
    Food* _food;
    Water* _water;
    Wifi_Module* _wifi_module;
};

#endif
#endif