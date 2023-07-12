#ifdef EMBEDDED

#include "petzeira.h"

Petzeira::Petzeira() 
{
}

void Petzeira::initialization() 
{
    _food = new Food();
    addModule(_food);
    Serial.println("[Petzeira::initialization] - Info - food created");
    
    _water = new Water();
    addModule(_water);
    Serial.println("[Petzeira::initialization] - Info - water created");
    
    _wifi_module = new Wifi_Module(this);
    addModule(_wifi_module);
    Serial.println("[Petzeira::initialization] - Info - wifi created");
}

void Petzeira::startup() 
{

}

void Petzeira::read_commands()
{
    uint8_t char_command = Serial.read();

    if(char_command == 'a') {
        _food->calibrate();
    } else if (char_command == 't') {
        _food->tare();
    } else if (char_command == 'b') {
        _food->set_weight_for_food(150);
    } else if (char_command == 'c') {
        _food->exec_action();
    } else if (char_command == 'd') {
        _food->open_door();
    } else if (char_command == 'e') {
        _food->close_door();
    } else if (char_command == 'f') {
        _water->open_water();
    } else if (char_command == 'g') {
        _water->close_water();
    } else if (char_command == 'h') {
        _water->exec_action();
    }

}

#endif