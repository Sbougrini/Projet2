// Sami Bougrini
#pragma once
#include "Zombie.h"
#include "Swimmer.h"

class ZombieSwimmer : public Zombie, public Swimmer
{
public:
    char getSymbol() const override;
    bool canEnter(const Map &map, const Vector2 &cellTarget) const override;
    void update(const Map &map, const Vector2 &playerPosition) override;
};
