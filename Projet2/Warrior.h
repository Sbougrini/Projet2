// Andy Donero
#pragma once

#include "Player.h"

#include <vector>

class Map;

class Warrior : public virtual Player
{
public:
    Warrior(const Vector2 &startPosition);

    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;
};
