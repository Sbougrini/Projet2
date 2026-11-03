// Sami Bougrini
#pragma once
#include "Utilities.h"

class Entity
{
  public:
    virtual Vector2 getPosition() const = 0;
    virtual char getSymbol() const = 0;
    virtual bool isAlive() const = 0;
    virtual ~Entity();
};