// Sami Bougrini
#pragma once
#include "Zombie.h"
#include "Swimmer.h"

class ZombieSwimmer : public Zombie, public Swimmer
{
public:
    ZombieSwimmer();
    char getSymbol() const override;
    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
};
