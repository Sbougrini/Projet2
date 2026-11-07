// Andy Donero
#include "Mage.h"

#include <cstdlib>

#include <curses.h>

#include "Map.h"

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

void Mage::onCollision(Entity *)
{
    // Le Mage n'inflige aucun dégât au contact.
}

void Mage::castSpell(const std::vector<Entity *> &entities)
{
    showSpellArea();
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

void Mage::showSpellArea() const
{
    attron(A_REVERSE);
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            Vector2 cell = position + Vector2{dx, dy};
            if ((dx != 0 || dy != 0) && Map::isInside(cell))
            {
                mvaddch(cell.y, cell.x, SPELL_SYMBOL);
            }
        }
    }
    attroff(A_REVERSE);
    refresh();
    napms(SPELL_DISPLAY_MS);
}