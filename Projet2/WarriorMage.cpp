// Andy Donero
#include "WarriorMage.h"

WarriorMage::WarriorMage(const Vector2 &startPosition)
    : Player(startPosition, 3), Warrior(startPosition), Mage(startPosition)
{
}

void WarriorMage::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    Mage::onUpdate(map, entities);
}

void WarriorMage::onCollision(Entity *other)
{
    Warrior::onCollision(other);
}

char WarriorMage::getSymbol() const
{
    return 'B';
}
