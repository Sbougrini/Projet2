// Sami Bougrini
#include "ZombieSwimmer.h"
#include "Map.h"

ZombieSwimmer::ZombieSwimmer()
{
    canSwim = true;
}

void ZombieSwimmer::onUpdate(const Map &map, const std::vector<Entity *> &entities)
{
    Zombie::onUpdate(map, entities);
    updateOxygen(map.isWater(position));
    if (!hasOxygen())
    {
        kill();
    }
}