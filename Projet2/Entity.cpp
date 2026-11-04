// Sami Bougrini
#include "Entity.h"
#include "Map.h"
#include "Utilities.h"
#include <cassert>

Vector2 Entity::getPosition() const
{
    return position;
}

void Entity::setPosition(const Vector2 &newPosition)
{
    position = newPosition;
}

bool Entity::isAlive() const
{
    return health > 0;
}

void Entity::applyDamage(int damage)
{
    assert(damage >= 0);
    health -= damage;
    if (health < 0)
    {
        health = 0;
    }
}

bool Entity::canEnter(const Map &map, const Vector2 &target) const
{
    return map.isWalkable(target) || (canSwim && map.isWater(target));
}

Entity *Entity::findEntityAt(const Vector2 &target,
                             const std::vector<Entity *> &entities) const
{
    for (Entity *entity : entities)
    {
        if (entity != this && entity->isAlive() && entity->getPosition() == target)
        {
            return entity;
        }
    }
    return nullptr;
}

bool Entity::move(const Vector2 &direction, const Map &map,
                  const std::vector<Entity *> &entities)
{
    Vector2 target = position + direction;
    if (!canEnter(map, target))
    {
        return false;
    }

    Entity *other = findEntityAt(target, entities);
    if (other != nullptr && !handleContact(other))
    {
        return false;
    }

    position = target;
    return true;
}

bool Entity::handleContact(Entity *other)
{
    assert(other != nullptr);
    if (other->isPlayer() == isPlayer())
    {
        return false;
    }
    onCollision(other);
    other->onCollision(this);
    return isAlive() && !other->isAlive();
}