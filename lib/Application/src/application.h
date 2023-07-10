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
    void add_schedule(time_t time, String module_name);
    void remove_schedule(time_t time, String module_name);

protected:
    virtual void initialization() = 0;
    virtual void startup() = 0;
    void addModule(Module *module);

private:
    std::vector<Module*> _modules;
    struct timeval _time_now;

    std::vector<std::pair<time_t, Module*>> _schedule_list;

};



#endif
#endif