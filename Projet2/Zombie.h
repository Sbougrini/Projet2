#pragma once
#include "Enemy.h"
class Zombie : public Enemy
{
public:
    char getSymbol() const override;
    Direction chooseDirection(const Map &map,
                              const Vector2 &playerPosition) const override;
};
