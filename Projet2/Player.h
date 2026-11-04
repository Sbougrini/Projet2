// Andy Donero
#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Player(const Vector2 &startPosition, int startingHealth);

    char readPlayerInputs() const;
    Vector2 getDirection(char key) const;

    bool isPlayer() const override;
};

inline bool Player::isPlayer() const
{
    return true;
}