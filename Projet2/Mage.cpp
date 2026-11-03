// Andy Donero
#include "Mage.h"
#include "Map.h"
#include <cstdlib>
#include <limits>

Mage::Mage(const Vector2 &startPosition) : Player(startPosition, 1)
{
}

void Mage::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    while (isAlive())
    {
        const int key = readPlayerInputs();

        if (key == ' ')
        {
            castSpell(entities);
            return;
        }

        const Vector2 direction = getDirection(key);

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

void Mage::onCollision(Entity *other)
{
    (void)other;
}

char Mage::getSymbol() const
{
    return 'M';
}

void Mage::castSpell(const std::vector<Entity *> &entities)
{
    for (Entity *entity : entities)
    {
        if (entity == nullptr || !entity->isAlive() || entity->isPlayer())
        {
            continue;
        }

        const Vector2 target = entity->getPosition();
        const int dx = std::abs(target.x - position.x);
        const int dy = std::abs(target.y - position.y);

        if (dx <= 1 && dy <= 1 && (dx != 0 || dy != 0))
        {
            entity->applyDamage(std::numeric_limits<int>::max());
        }
    }
}
