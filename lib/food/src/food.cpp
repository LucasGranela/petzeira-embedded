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

void Food::setup()
{
    _state = FOOD_CLOSE;

    _graus_for_close = 0;
    _graus_for_open = 90;

    _weight_for_food = 0;

    _want_to_food_now = false;

    _balanca = new Balanca(HX711_DOUT_FOOD, HX711_SCK_FOOD);

    _servo = new Servo();
}

void Food::start()
{
    _servo->attach(SERVO_PIN);
    _servo->write(_graus_for_close);
}

void Food::loop()
{
    switch (_state)
    {
    case FOOD_OPEN: {
        float peso = _balanca->get_weight();
        _servo->write(_graus_for_open);

        if(peso >= _weight_for_food * 0.8) {
            _state = FOOD_CLOSE;
        }
        
    } break;

    case FOOD_CLOSE: {
        _servo->write(_graus_for_close);

        if(_want_to_food_now) {
            _state = FOOD_OPEN;
            _want_to_food_now = false;
        }
    } break;
    
    default:
        break;
    }    
}

void Food::exec_action()
{
    _want_to_food_now = true;
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
}