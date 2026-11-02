#include "Map.h"

bool Map::isInside(const Vector2 &position) const
{
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 &&
           position.y < MAP_HEIGHT;
}

int Map::toIndex(const Vector2 &position) const
{
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