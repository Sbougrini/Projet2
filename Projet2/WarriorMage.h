// Andy Donero
#pragma once

#include "Mage.h"
#include "Warrior.h"

#include <vector>

class Map;

class WarriorMage : public Warrior, public Mage
{
public:
    WarriorMage(const Vector2 &startPosition);

    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;
};

inline char WarriorMage::getSymbol() const
{
    return 'B';
}
