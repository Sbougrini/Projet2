// Sami Bougrini
#include "Swimmer.h"

Swimmer::~Swimmer()
{
}

void Swimmer::updateOxygen(bool isInWater)
{
    if (isInWater)
    {
        --oxygen;
        if (oxygen < 0)
        {
            oxygen = 0;
        }
    }
    else
    {
        ++oxygen;
        if (oxygen > MAX_OXYGEN)
        {
            oxygen = MAX_OXYGEN;
        }
    }
}