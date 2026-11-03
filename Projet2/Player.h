// Andy Donero
#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Player(const Vector2 &startPosition, int startingHealth);

    int readPlayerInputs() const;
    Vector2 getDirection(int key) const;

    bool isPlayer() const override;
};