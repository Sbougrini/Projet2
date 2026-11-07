// Andy Donero
#include "WarriorMage.h"

WarriorMage::WarriorMage(const Vector2 &startPosition)
    : Player(startPosition, Warrior::MAX_HEALTH), Warrior(startPosition),
      Mage(startPosition)
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

bool WarriorMage::canCastSpell() const
{
    return Mage::canCastSpell();
}