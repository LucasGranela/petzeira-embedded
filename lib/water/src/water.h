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
    void open_water();
    void close_water();
    float read_value();
    bool action_executed();

private:
    double _weight_for_water; //gramas
    int _state;
    bool _executed;

    bool _want_to_water_now;

    enum Water_State {
        WATER_OPEN,
        WATER_CLOSED
    };

};


#endif