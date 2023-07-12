#ifdef EMBEDDED
#ifndef APPLICATION_H
#define APPLICATION_H

#include "module.h"
#include "esp_sntp.h"
#include <vector>

class Application
{
public:
    void setup();
    void loop();
    void start();
    void add_schedule(timeval time, String module_name);
    void remove_schedule(timeval time, String module_name);
    void act_module(String module_name);
    void calibre_module();
    float read_module(String module_name);
    std::pair<bool, String> check_some_executed();
    
protected:
    virtual void initialization() = 0;
    virtual void startup() = 0;
    virtual void read_commands() = 0;
    void addModule(Module *module);

private:
    std::vector<Module*> _modules;
    struct timeval _time_now;

    std::vector<std::pair<timeval, Module*>> _schedule_list;
    bool _calibrate_module;
};



#endif
#endif