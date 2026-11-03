// Sami Bougrini
#include "HeadlessZombie.h"
#include <cstdlib>

char HeadlessZombie::getSymbol() const
{
    return SYMBOL;
}

Vector2 HeadlessZombie::getDirection(const Map &map, const Vector2 &playerPosition) const
{
    return Utilities::offset(static_cast<Direction>(std::rand() % 4));
}