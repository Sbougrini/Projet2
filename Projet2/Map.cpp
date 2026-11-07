// Sami Bougrini
#include "Map.h"

#include <cassert>

const CellInfo Map::CELL_INFOS[CELL_TYPE_COUNT] = {
    {'.', true, false, GROUND_COLOR},   
    {'~', false, true, WATER_COLOR},     
    {'A', false, false, MOUNTAIN_COLOR}, 
    {'E', true, false, EXIT_COLOR}       
};

bool Map::symbolToCellType(char symbol, CellType &type)
{
    for (int i = 0; i < CELL_TYPE_COUNT; ++i)
    {
        if (CELL_INFOS[i].symbol == symbol)
        {
            type = static_cast<CellType>(i);
            return true;
        }
    }
    return false;
}

bool Map::isWalkable(const Vector2 &position) const
{
    if (!isInside(position))
    {
        return false;
    }
    return CELL_INFOS[cells[toIndex(position)]].isWalkable;
}

bool Map::isWater(const Vector2 &position) const
{
    if (!isInside(position))
    {
        return false;
    }
    return CELL_INFOS[cells[toIndex(position)]].isWater;
}

bool Map::isExit(const Vector2 &position) const
{
    if (!isInside(position))
    {
        return false;
    }
    return cells[toIndex(position)] == CellType::EXIT;
}

char Map::getSymbol(const Vector2 &position) const
{
    if (!isInside(position))
    {
        return ' ';
    }
    return CELL_INFOS[cells[toIndex(position)]].symbol;
}

ColorPair Map::getColor(const Vector2 &position) const
{
    if (!isInside(position))
    {
        return DEFAULT_COLOR;
    }
    return CELL_INFOS[cells[toIndex(position)]].color;
}

void Map::setCellType(const Vector2 &position, CellType type)
{
    if (!isInside(position))
    {
        return;
    }
    cells[toIndex(position)] = type;
}

int Map::toIndex(const Vector2 &position) const
{
    assert(isInside(position));
    return position.y * MAP_WIDTH + position.x;
}