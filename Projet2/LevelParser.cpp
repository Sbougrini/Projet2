// Sami Bougrini
#include "LevelParser.h"
#include "HeadlessZombie.h"
#include "Zombie.h"
#include "ZombieSwimmer.h"
#include <cassert>
#include <fstream>
#include <utility>

bool LevelParser::readLines(const std::string &path, Lines &lines, std::string &error)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        error = "Impossible d'ouvrir le fichier " + path;
        return false;
    }
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(std::move(line));
    }
    return true;
}

bool LevelParser::checkLineLengths(const Lines &lines, std::string &error)
{
    if (lines.size() != MAP_HEIGHT)
    {
        error = "Le niveau doit avoir " + std::to_string(MAP_HEIGHT) + " lignes";
        return false;
    }
    for (const std::string &line : lines)
    {
        if (line.size() != MAP_WIDTH)
        {
            error = "Le niveau doit avoir " + std::to_string(MAP_WIDTH) +
                    " caracteres par ligne";
            return false;
        }
    }
    return true;
}

bool LevelParser::isEntitySymbol(char symbol)
{
    return symbol == PLAYER_SYMBOL || symbol == Zombie::SYMBOL ||
           symbol == HeadlessZombie::SYMBOL || symbol == ZombieSwimmer::SYMBOL;
}

int LevelParser::countSymbol(const Lines &lines, char symbol)
{
    int count = 0;
    for (const std::string &line : lines)
    {
        for (char c : line)
        {
            if (c == symbol)
            {
                ++count;
            }
        }
    }
    return count;
}

bool LevelParser::checkUnknownSymbols(const Lines &lines, std::string &error)
{
    CellType type = Ground;
    for (const std::string &line : lines)
    {
        for (char symbol : line)
        {
            if (!isEntitySymbol(symbol) && !Map::symbolToCellType(symbol, type))
            {
                error = std::string("Symbole inconnu : ") + symbol;
                return false;
            }
        }
    }
    return true;
}

bool LevelParser::checkSymbols(const Lines &lines, std::string &error)
{
    if (!checkUnknownSymbols(lines, error))
    {
        return false;
    }
    if (countSymbol(lines, PLAYER_SYMBOL) != 1)
    {
        error = "Le niveau doit avoir un seul depart H";
        return false;
    }
    if (countSymbol(lines, EXIT_SYMBOL) < 1)
    {
        error = "Le niveau doit avoir au moins une sortie E";
        return false;
    }
    return true;
}

EnemyType LevelParser::symbolToEnemyType(char symbol)
{
    switch (symbol)
    {
    case HeadlessZombie::SYMBOL:
        return EnemyType::HEADLESS_ZOMBIE;
    case ZombieSwimmer::SYMBOL:
        return EnemyType::ZOMBIE_SWIMMER;
    default:
        assert(symbol == Zombie::SYMBOL);
        return EnemyType::ZOMBIE;
    }
}

void LevelParser::fillLevelData(const Lines &lines, LevelData &data)
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            Vector2 position{x, y};
            char symbol = lines[y][x];
            CellType type = Ground;
            if (symbol == PLAYER_SYMBOL)
            {
                data.playerStart = position;
            }
            else if (isEntitySymbol(symbol))
            {
                data.enemies.push_back(EnemySpawn{symbolToEnemyType(symbol), position});
            }
            else
            {
                Map::symbolToCellType(symbol, type);
            }
            data.map.setCellType(position, type);
        }
    }
}

bool LevelParser::parse(const std::string &path, LevelData &data, std::string &error)
{
    Lines lines;
    if (!readLines(path, lines, error) || !checkLineLengths(lines, error) ||
        !checkSymbols(lines, error))
    {
        return false;
    }
    data = LevelData{};
    fillLevelData(lines, data);
    return true;
}