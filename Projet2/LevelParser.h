#pragma once
#include "Map.h"
#include "Utilities.h"
#include <string>
#include <vector>

struct EnemySpawn
{
    char symbol = ' ';
    Vector2 position;
};

struct LevelData
{
    Map map;
    Vector2 playerStart;
    std::vector<EnemySpawn> enemies;
};

class LevelParser
{
public:
    LevelParser() = delete;
    static bool parse(const std::string &path, LevelData &data, std::string &error);

private:
    using Lines = std::vector<std::string>;
    static bool readLines(const std::string &path, Lines &lines, std::string &error);
    static bool checkLineLengths(const Lines &lines, std::string &error);
    static bool checkSymbols(const Lines &lines, std::string &error);
    static bool isEntitySymbol(char symbol);
    static int countSymbol(const Lines &lines, char symbol);
    static void fillLevelData(const Lines &lines, LevelData &data);
};