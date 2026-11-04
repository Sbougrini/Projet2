// Andy Donero
#include "Mage.h"
#include "Map.h"
#include <cstdlib>

Mage::Mage(const Vector2 &startPosition) : Player(startPosition, MAX_HEALTH)
{
}

void Mage::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    while (isAlive())
    {
        const char key = readPlayerInputs();
        if (key == SPELL_KEY)
        {
            castSpell(entities);
            return;
        }
        if (tryMove(key, map, entities))
        {
            return;
        }
    }
}

void Mage::onCollision(Entity *other)
{
    (void)other;
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
            entity->kill();
        }
    }
}
