#include <Arduino.h>
#include "application.h"
#include "food.h"
#include <ArduinoJson.h>

void Application::setup() {
    this->initialization();
    _calibrate_module = false;
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

    read_commands();
    
    for(auto schedule : _schedule_list) {
        if(schedule.first.tv_sec == _time_now.tv_sec) {
            Serial.println("execution action on schedule");
            schedule.second->exec_action();
        }
    }

    for(Module *module : _modules) {
        if(_calibrate_module && module->name().compareTo("food") == 0) {
            Food* food = (Food*)module;
            food->calibrate();
            _calibrate_module = false;
        }
        module->loop();
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);
}

void Application::addModule(Module *module) 
{
    _modules.push_back(module);
}

void Application::add_schedule(timeval time, String module_name)
{
    Serial.println("Add schedule:");
    Serial.print("time: ");
    Serial.println(time.tv_sec);
    Serial.print("module_name : ");
    Serial.println(module_name);

    for(Module *module : _modules) {
        if(module->name() == module_name) {
            _schedule_list.push_back(std::pair<timeval, Module*>(time, module));
        }
    }
}

void Application::remove_schedule(timeval time, String module_name)
{
    for(int i = 0; i < _schedule_list.size(); ++i) {
        if(_schedule_list.at(i).first.tv_sec == time.tv_sec && _schedule_list.at(i).second->name() == module_name) {
            _schedule_list.erase(_schedule_list.begin()+i);
        }
    }
}

void Application::act_module(String module_name)
{
    for(Module* module : _modules) {
        if(module->name().compareTo(module_name) == 0) {
            module->exec_action();
        }
    }
}

void Application::calibre_module()
{
    _calibrate_module = true;
}

float Application::read_module(String module_name)
{
    for(Module* module : _modules) {
        if(module->name().compareTo(module_name) == 0) {
            return module->read_value();
        }
    }

    return -1;
}


std::pair<bool, String> Application::check_some_executed()
{
    for(Module* module : _modules) {
        if(module->action_executed()) {
            return std::pair<bool, String>(true, module->name());
        }
    }
    return std::pair<bool, String>(false, "");
}