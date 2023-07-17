#include "food.h"
#include "staticconfig.h"

Food::Food(/* args */)
{
    _servo = nullptr;
}

Food::~Food()
{
    delete _servo;
    _servo = nullptr;
}

void Food::initialization()
{
    Serial.println("[Food::setup] - Info - food setup");
    _state = FOOD_CLOSE;

    _graus_for_close = 10;
    _graus_for_open = 60;

    _turn_to_open = true;

    _weight_for_food = 150;

    _want_to_food_now = false;

    _executed = false;

    _balanca = new Balanca(HX711_DOUT_FOOD, HX711_SCK_FOOD);

    _servo = new Servo();
    Serial.println("[Food::setup] - Info - food setup finished");
}

void Food::startup()
{
    Serial.println("[Food::start] - Info - food start");
    _servo->attach(SERVO_PIN);
    _servo->write(_graus_for_close);
    Serial.println("[Food::start] - Info - food started");
}

void Food::loop()
{
    float peso = _balanca->get_weight();

    switch (_state)
    {
    case FOOD_OPEN: {
        if(_turn_to_open) {
            _servo->write(_graus_for_open);
        } else {
            _servo->write(_graus_for_close);
        }

        Serial.print("peso: ");
        Serial.println(peso);
        
        _turn_to_open = !_turn_to_open;

        if(peso >= _weight_for_food * 0.7) {
            _state = FOOD_CLOSE;
            _executed = true;
        }
        
    } break;

    case FOOD_CLOSE: {
        _servo->write(_graus_for_close);

        if(_want_to_food_now) {
            _state = FOOD_OPEN;
            _want_to_food_now = false;
            _turn_to_open = true;
            _executed = false;
        }
    } break;
    
    default:
        break;
    }    
}

void Food::exec_action()
{
    _want_to_food_now = true;
    Serial.println("Food::exec_action");
}

String Food::name()
{
    return "food";
}

void Food::set_weight_for_food(int new_weight)
{
    _weight_for_food = new_weight;
}

void Food::calibrate()
{
    _balanca->calibration();
    Serial.println("Food::calibrate");
}

void Food::open_door()
{
    _servo->write(_graus_for_open);
}

void Food::close_door()
{
    _servo->write(_graus_for_close);
}

void Food::tare()
{
    _balanca->tare();
    Serial.println("Food::tare");
}

float Food::read_value()
{
    return _balanca->get_weight();
}

bool Food::action_executed()
{
    bool result = _executed;
    _executed = false;
    return result;
}