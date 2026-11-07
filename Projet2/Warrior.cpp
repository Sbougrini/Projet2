// Andy Donero
#include "Warrior.h"

#include <cassert>

#include "Map.h"

Warrior::Warrior(const Vector2 &startPosition) : Player(startPosition, MAX_HEALTH)
{
}

void Warrior::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    while (isAlive())
    {
        if (tryMove(readPlayerInputs(), map, entities))
        {
            return;
        }
    }
}

void Warrior::onCollision(Entity *other)
{
    assert(other != nullptr);
    other->kill();
}
