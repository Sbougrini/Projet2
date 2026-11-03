// Sami Bougrini
#include "Enemy.h"
#include "Entity.h"
#include "Utilities.h"

void Enemy::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    Vector2 playerPosition = findPlayerPosition(entities);
    Vector2 direction = getDirection(map, playerPosition);
    move(direction, map, entities);
}

bool Enemy::isPlayer() const
{
    return false;
}

void Enemy::onCollision(Entity *other)
{
    other->applyDamage(DAMAGE);
}

Vector2 Enemy::findPlayerPosition(const std::vector<Entity *> &entities)
{
    for (Entity *entity : entities)
    {
        if (entity->isPlayer())
        {
            return entity->getPosition();
        }
    }
    return Vector2{};
}