// Andy Donero
#pragma once

#include "Entity.h"
#include <vector>

class Map;

class Player : public Entity
{
public:
    Player(const Vector2 &startPosition, int startingHealth);

    char readPlayerInputs() const;
    Vector2 getDirection(char key) const;

    bool isPlayer() const override;

protected:
    bool tryMove(char key, const Map &map, const std::vector<Entity *> &entities);
};

inline bool Player::isPlayer() const
{
    return true;
}