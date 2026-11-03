// Sami Bougrini
#pragma once
#include "Enemy.h"
class HeadlessZombie : public Enemy
{
public:
    char getSymbol() const override;
    Vector2 getDirection(const Map &map,
                         const Vector2 &playerPosition) const override;
};
