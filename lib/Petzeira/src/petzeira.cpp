#ifdef EMBEDDED

#include "petzeira.h"
#include "food.h"
#include "water.h"

Petzeira::Petzeira() 
{
}

void Petzeira::initialization() 
{
    Food* food = new Food();
    addModule(food);
    Water* water = new Water();
    addModule(water);
}

void Petzeira::startup() 
{

}

#endif