#include <Arduino.h>
#include "application.h"


void Application::setup() {
    this->initialization();
    for(Module *module : _modules) {
        module->setup();
    }
}

void Application::start() {
    this->startup();
    for(Module *module : _modules) {
        module->start();
    }
}

void Application::loop() {
    gettimeofday(&_time_now, NULL);
    
    for(auto schedule : _schedule_list) {
        if(schedule.first == _time_now.tv_sec) {
            schedule.second->exec_action();
        }
    }

    for(Module *module : _modules) {
        module->loop();
    }

    vTaskDelay(10/portTICK_PERIOD_MS);
}

void Application::addModule(Module *module) 
{
    _modules.push_back(module);
}

void Application::add_schedule(time_t time, String module_name)
{
    for(Module *module : _modules) {
        if(module->name() == module_name) {
            _schedule_list.push_back(std::pair<time_t, Module*>(time, module));
        }
    }
}

void Application::remove_schedule(time_t time, String module_name)
{
    for(int i = 0; i < _schedule_list.size(); ++i) {
        if(_schedule_list.at(i).first == time && _schedule_list.at(i).second->name() == module_name) {
            _schedule_list.erase(_schedule_list.begin()+i);
        }
    }
}