// Andy Donero
#include "Warrior.h"
#include "Map.h"
#include <limits>

Warrior::Warrior(const Vector2 &startPosition) : Player(startPosition, 3)
{
}

void Warrior::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    while (isAlive())
    {
        const Vector2 direction = getDirection(readPlayerInputs());

        if (direction == Vector2{})
        {
            continue;
        }

        if (move(direction, map, entities) || !isAlive())
        {
            return;
        }
    }
}

void Warrior::onCollision(Entity *other)
{
    if (other != nullptr)
    {
        other->applyDamage(std::numeric_limits<int>::max());
    }
}
