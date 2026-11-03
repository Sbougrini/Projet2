// Andy Donero
#pragma once

#include "Player.h"

#include <vector>

class Map;

class Mage : public virtual Player
{
public:
    Mage(const Vector2 &startPosition);

    void onUpdate(const Map &map, std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    char getSymbol() const override;

    void castSpell(std::vector<Entity *> &entities);
};