#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Vector2 getPosition() const override;
    bool isAlive() const override;

protected:
    Vector2 position; 
    int health = 0;
};