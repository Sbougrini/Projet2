#pragma once
#include "Entity.h"
#include "Utilities.h"

class Map;

class Enemy : public Entity
{
public:
    Vector2 getPosition() const override;
    bool isAlive() const override;
    virtual void update(const Map &map, const Vector2 &playerPosition);
    virtual Direction chooseDirection(const Map &map, const Vector2 &playerPosition) const = 0;
    virtual bool canEnter(const Map &map, const Vector2 &cellTarget) const;
    void kill();

protected:
    Vector2 position;
    bool alive = true;
};
