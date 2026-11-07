// Andy Donero
#pragma once

#include <vector>

#include "Mage.h"
#include "Warrior.h"

class Map;

class WarriorMage : public Warrior, public Mage
{
public:
    WarriorMage(const Vector2 &startPosition);

    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;
    bool canCastSpell() const override;
};

inline char WarriorMage::getSymbol() const
{
    static constexpr char SYMBOL = 'B';
    return SYMBOL;
}
