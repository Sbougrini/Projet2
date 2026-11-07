// Andy Donero
#pragma once

#include <vector>

#include "Player.h"

class Map;

class Warrior : public virtual Player
{
public:
    static constexpr char SYMBOL = 'W';
    static constexpr int MAX_HEALTH = 3;

    Warrior(const Vector2 &startPosition);

    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;
};

inline char Warrior::getSymbol() const
{
    return SYMBOL;
}
