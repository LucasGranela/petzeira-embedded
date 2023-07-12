#ifndef MODULE_H
#define MODULE_H

#include <Arduino.h>

class Module
{ 

public:
    virtual void setup() = 0;
    virtual void start() = 0;
    virtual void loop() = 0;
    virtual void exec_action() = 0;
    virtual String name() = 0;
    virtual float read_value() = 0;
    virtual bool action_executed() = 0;
};

#endif