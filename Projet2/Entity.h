// Sami Bougrini | Andy Donero
#pragma once
#include "Utilities.h"
#include <vector>

class Map;

class Entity
{
public:
    virtual ~Entity() = default;
    Vector2 getPosition() const;
    void setPosition(const Vector2 &newPosition);
    int getHealth() const;
    void applyDamage(int damage);
    bool isAlive() const;
    void kill();
    bool move(const Vector2 &direction, const Map &map,
              const std::vector<Entity *> &entities);

    virtual void onUpdate(const Map &map, const std::vector<Entity *> &entities) = 0;
    virtual void onCollision(Entity *other) = 0;
    virtual bool isPlayer() const = 0;
    virtual char getSymbol() const = 0;

protected:
    Vector2 position;
    int health = 1;
    bool canSwim = false;

private:
    bool canEnter(const Map &map, const Vector2 &target) const;
    Entity *findEntityAt(const Vector2 &target,
                         const std::vector<Entity *> &entities) const;
    bool handleContact(Entity *other);
};

inline bool Entity::isAlive() const
{
    return health > 0;
}

inline Vector2 Entity::getPosition() const
{
    return position;
}

inline void Entity::kill()
{
    health = 0;
}

inline int Entity::getHealth() const
{
    return health;
}