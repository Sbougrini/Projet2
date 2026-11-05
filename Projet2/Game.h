// Sami Bougrini | Andy Donero
#pragma once
#include "Map.h"
#include "Utilities.h"
#include <string>
#include <vector>

class Entity;
class Player;
class Enemy;
struct EnemySpawn;

class Game
{
public:
    static Game &getInstance();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    void run();

private:
    Game() = default;
    ~Game();

    static Enemy *createEnemy(const EnemySpawn &spawn);
    void choosePlayer();
    static Player *createPlayer(char key);
    bool loadLevel(int levelIndex, std::string &error);
    void playTurn();
    bool isLevelFinished() const;
    std::string playLevels();
    void playLevel();
    static void showMessage(const std::string &message);
    void removeDeadEnemies();
    void render() const;
    void renderMap() const;
    void renderEntities() const;
    void renderHUD() const;
    void freeLevel();

    static constexpr int LEVEL_COUNT = 5;
    static const std::string LEVEL_PATHS[LEVEL_COUNT];
    Map map;
    std::vector<Entity *> entities;
    int currentLevel = 4;
    Player *player = nullptr;
};