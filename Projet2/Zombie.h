// Sami Bougrini
#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
public:
    static constexpr char SYMBOL = 'Z';
    char getSymbol() const override;
    Vector2 getDirection(const Map &map, const Vector2 &playerPosition) const override;
};

inline char Zombie::getSymbol() const
{
    return SYMBOL;
}