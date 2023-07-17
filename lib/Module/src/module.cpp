#include "module.h"

void module_LoopTask(void *pvParameters) 
{
    Module* self = (Module*) pvParameters;

    while(true) {
        self->loop();
        vTaskDelay(10/ portTICK_PERIOD_MS);
    }

    vTaskDelete(nullptr);
}


void Module::setup()
{
    initialization();
}

void Module::start()
{
    startup();
    xTaskCreate(module_LoopTask, name().c_str(), 10 * 1024, this, 3, nullptr);
}