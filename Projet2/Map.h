// Sami Bougrini
#pragma once
#include "Utilities.h"

constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 10;

enum CellType
{
    Ground = 0,
    Water,
    Mountain,
    Exit,
    CellTypeCount
};

struct CellInfo
{
    char symbol = ' ';
    bool isWalkable = false;
    bool isWater = false;
};

class Map
{
public:
    static bool symbolToCellType(char symbol, CellType &type);
    static bool isInside(const Vector2 &position);
    bool isWalkable(const Vector2 &position) const;
    bool isWater(const Vector2 &position) const;
    bool isExit(const Vector2 &position) const;
    char getSymbol(const Vector2 &position) const;
    void setCellType(const Vector2 &position, CellType type);

private:
    int toIndex(const Vector2 &position) const;
    CellType cells[MAP_WIDTH * MAP_HEIGHT] = {};
    static const CellInfo CELL_INFOS[CellTypeCount];
};

inline bool Map::isInside(const Vector2 &position)
{
    return position.x >= 0 && position.x < MAP_WIDTH && position.y >= 0 &&
           position.y < MAP_HEIGHT;
}