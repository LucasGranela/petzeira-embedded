#ifndef BALANCA_H
#define BALANCA_H

#include "HX711.h"

class Balanca 
{
public:
    Balanca (int data_out_pin, int clock_pin);
    ~Balanca ();
    void calibration();
    float get_weight();
    void tare();

private:
    HX711* _balanca;
    int _calibration_value;

};
#endif