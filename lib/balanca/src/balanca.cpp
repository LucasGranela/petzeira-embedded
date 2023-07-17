#include "balanca.h"

Balanca::Balanca (int data_out_pin, int clock_pin)
{
    _balanca = new HX711();

    _balanca->begin(data_out_pin, clock_pin);

    this->tare();
}

Balanca::~Balanca ()
{

}

void Balanca::calibration()
{    
    // Faz a leitura e calcula a escala
    long leitura = _balanca->read_average(50);
    float escala = (leitura - _balanca->get_offset())/1000.00f;
    
    // Usa a escala calculada
    _balanca->set_scale(escala);

    _calibration_value = escala;
}

float Balanca::get_weight()
{
    return _balanca->get_units(5);
}

void Balanca::tare()
{
    _balanca->tare(50);
}