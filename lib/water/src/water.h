#ifndef WATER_H
#define WATER_H

#include "balanca.h"

#include "module.h"

class Water : public Module
{
public:
    Water(/* args */);
    ~Water();
    void setup();
    void start();
    void loop();
    void exec_action();
    String name();
    void set_weight_for_water(int new_weight);
    void calibrate();

private:
    Balanca* _balanca;

    double _weight_for_water; //gramas
    int _state;

    bool _want_to_water_now;

    enum Water_State {
        WATER_OPEN,
        WATER_CLOSED
    };

};


#endif