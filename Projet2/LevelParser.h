// Sami Bougrini
#pragma once

#include <string>
#include <vector>

#include "Map.h"
#include "Utilities.h"

enum class EnemyType
{
    ZOMBIE = 0,
    HEADLESS_ZOMBIE,
    ZOMBIE_SWIMMER
};

struct EnemySpawn
{
    EnemyType type = EnemyType::ZOMBIE;
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
    static bool checkUnknownSymbols(const Lines &lines, std::string &error);
    static bool isEntitySymbol(char symbol);
    static int countSymbol(const Lines &lines, char symbol);
    static void fillLevelData(const Lines &lines, LevelData &data);
    static EnemyType symbolToEnemyType(char symbol);

    static constexpr char PLAYER_SYMBOL = 'H';
    static constexpr char EXIT_SYMBOL = 'E';
};