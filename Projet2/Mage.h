// Andy Donero
#pragma once

#include "Player.h"

#include <vector>

class Map;

class Mage : public virtual Player
{
public:
    static constexpr char SYMBOL = 'M';
    static constexpr int MAX_HEALTH = 1;
    static constexpr char SPELL_KEY = ' ';

    Mage(const Vector2 &startPosition);

    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;

    void castSpell(const std::vector<Entity *> &entities);
};

inline char Mage::getSymbol() const
{
    return SYMBOL;
}