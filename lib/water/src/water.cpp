#include "water.h"
#include "staticconfig.h"

Water::Water(/* args */)
{
    _balanca = nullptr;
}

Water::~Water()
{
    delete _balanca;
    _balanca = nullptr;
}

void Water::setup()
{
    _state = WATER_CLOSED;

    _weight_for_water = 0;

    _want_to_water_now = false;

    _balanca = new Balanca(HX711_DOUT_WATER, HX711_SCK_WATER);

    pinMode(TRANSISTOR_PIN, OUTPUT);
}

void Water::start()
{
    digitalWrite(TRANSISTOR_PIN, LOW);
}

void Water::loop()
{
    switch (_state)
    {
    case WATER_OPEN: {
        float peso = _balanca->get_weight();
        digitalWrite(TRANSISTOR_PIN, HIGH);

        if(peso >= _weight_for_water * 0.8) {
            _state = WATER_CLOSED;
        }
        
    } break;

    case WATER_CLOSED: {
        digitalWrite(TRANSISTOR_PIN, LOW);

        if(_want_to_water_now) {
            _state = WATER_OPEN;
            _want_to_water_now = false;
        }
    } break;
    
    default:
        break;
    }    
}

void Water::exec_action()
{
    _want_to_water_now = true;
}

String Water::name()
{
    return "water";
}

void Water::set_weight_for_water(int new_weight)
{
    _weight_for_water = new_weight;
}

void Water::calibrate()
{
    _balanca->calibration();
}