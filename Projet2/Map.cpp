// Sami Bougrini
#include "Map.h"
#include <cassert>

int Map::toIndex(const Vector2 &position) const
{
    assert(isInside(position));
    return position.y * MAP_WIDTH + position.x;
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
    return cells[toIndex(position)] == CellType::Exit;
}

char Map::getSymbol(const Vector2 &position) const
{
    if (!isInside(position))
    {
        return ' ';
    }
    return CELL_INFOS[cells[toIndex(position)]].symbol;
}

bool Map::symbolToCellType(char symbol, CellType &type)
{
    for (int i = 0; i < CellTypeCount; ++i)
    {
        if (CELL_INFOS[i].symbol == symbol)
        {
            type = static_cast<CellType>(i);
            return true;
        }
    }
    return false;
}

void Map::setCellType(const Vector2 &position, CellType type)
{
    if (!isInside(position))
    {
        return;
    }
    cells[toIndex(position)] = type;
}

const CellInfo Map::CELL_INFOS[CellTypeCount] = {
    {'.', true, false},  // Ground
    {'~', false, true},  // Water
    {'A', false, false}, // Mountain
    {'E', true, false}   // Exit
};