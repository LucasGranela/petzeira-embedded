#ifndef FOOD_H
#define FOOD_H

#include "Servo.h"
#include "balanca.h"

#include "module.h"

class Food : public Module
{
public:
    Food(/* args */);
    ~Food();
    void setup();
    void start();
    void loop();
    void exec_action();
    String name();
    void set_weight_for_food(int new_weight);
    void calibrate();
    void open_door();
    void close_door();
    void tare();
    float read_value();
    bool action_executed();

private:
    Servo* _servo;
    Balanca* _balanca;

    int _graus_for_open;
    int _graus_for_close;
    double _weight_for_food; //gramas
    int _state;
    bool _executed;

    bool _want_to_food_now;
    bool _turn_to_open;

    enum Food_State {
        FOOD_OPEN,
        FOOD_CLOSE
    };

};


#endif