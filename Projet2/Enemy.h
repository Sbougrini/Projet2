// Sami Bougrini
#pragma once

#include <vector>

#include "Entity.h"
#include "Utilities.h"

class Map;

class Enemy : public Entity
{
public:
    void onUpdate(const Map &map, const std::vector<Entity *> &entities) override;
    void onCollision(Entity *other) override;
    bool isPlayer() const override;

    virtual Vector2 getDirection(const Map &map, const Vector2 &playerPosition) const = 0;

protected:
    static Vector2 findPlayerPosition(const std::vector<Entity *> &entities);
    static constexpr int DAMAGE = 1;
};

inline bool Enemy::isPlayer() const
{
    return false;
}