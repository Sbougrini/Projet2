// Sami Bougrini
#pragma once
#include "Swimmer.h"
#include "Zombie.h"

class ZombieSwimmer : public Zombie, public Swimmer
{
public:
    ZombieSwimmer();
    static constexpr char SYMBOL = 'S';
    char getSymbol() const override;
    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
};

inline char ZombieSwimmer::getSymbol() const
{
    return SYMBOL;
}