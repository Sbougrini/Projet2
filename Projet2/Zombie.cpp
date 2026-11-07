// Sami Bougrini
#include "Zombie.h"

#include <cstdlib>

Vector2 Zombie::getDirection(const Map &, const Vector2 &playerPosition) const
{
    int dx = playerPosition.x - position.x;
    int dy = playerPosition.y - position.y;

    if (dx == 0 && dy == 0)
    {
        return Vector2{};
    }
    if (std::abs(dx) >= std::abs(dy))
    {
        return Utilities::offset(dx > 0 ? Direction::RIGHT : Direction::LEFT);
    }
    return Utilities::offset(dy > 0 ? Direction::DOWN : Direction::UP);
}