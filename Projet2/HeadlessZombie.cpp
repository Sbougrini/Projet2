// Sami Bougrini
#include "HeadlessZombie.h"

Vector2 HeadlessZombie::getDirection(const Map &, const Vector2 &) const
{
    return Utilities::offset(Utilities::randomDirection());
}