#include "water.h"
#include "staticconfig.h"

Water::Water()
{

}

Water::~Water()
{

}

void Water::initialization()
{
    Serial.println("[Water::setup] - Info - Water setup");
    _state = WATER_CLOSED;

    _want_to_water_now = false;
    _executed = false;

    pinMode(TRANSISTOR_PIN, OUTPUT);
    Serial.println("[Water::setup] - Info - Water setup fineshed");
}

void Water::startup()
{
    Serial.println("[Water::start] - Info - Water start");
    digitalWrite(TRANSISTOR_PIN, LOW);
    Serial.println("[Water::start] - Info - Water start fineshed");
}

void Water::loop()
{
    switch (_state)
    {
    case WATER_OPEN: {
        digitalWrite(TRANSISTOR_PIN, HIGH);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        digitalWrite(TRANSISTOR_PIN, LOW);
        _state = WATER_CLOSED;
        _executed = true;
    } break;

    case WATER_CLOSED: {
        digitalWrite(TRANSISTOR_PIN, LOW);

        if(_want_to_water_now) {
            _state = WATER_OPEN;
            _want_to_water_now = false;
            _executed = false;
        }
    } break;
    
    default:
        break;
    }    
}

void Water::exec_action()
{
    _want_to_water_now = true;
    Serial.println("Water::exec_action");
}

String Water::name()
{
    return "water";
}

void Water::set_weight_for_water(int new_weight)
{
    _weight_for_water = new_weight;
}

void Water::open_water()
{
    Serial.println("[Water::open_water] - Info - Water open");
    digitalWrite(TRANSISTOR_PIN, HIGH);
}

void Water::close_water()
{
    Serial.println("[Water::close_water] - Info - Water closed");
    digitalWrite(TRANSISTOR_PIN, LOW);
}

float Water::read_value()
{
    Serial.println("Water::read_value");
    return 0.0;
}

bool Water::action_executed()
{
    bool result = _executed;
    _executed = false;
    return result;
}