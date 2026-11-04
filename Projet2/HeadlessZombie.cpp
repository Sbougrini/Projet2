// Sami Bougrini
#include "HeadlessZombie.h"

#include <cstdlib>

Vector2 HeadlessZombie::getDirection(const Map &, const Vector2 &) const
{
    return Utilities::offset(static_cast<Direction>(std::rand() % 4));
}