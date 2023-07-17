#ifndef MODULE_H
#define MODULE_H

#include <Arduino.h>

class Module
{ 

public:
    void setup();
    void start();
    
public:
    virtual void initialization() = 0;
    virtual void startup() = 0;
    virtual void loop() = 0;
    virtual void exec_action() = 0;
    virtual String name() = 0;
    virtual float read_value() = 0;
    virtual bool action_executed() = 0;
};

#endif