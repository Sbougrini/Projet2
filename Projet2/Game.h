// Sami Bougrini | Andy Donero
#pragma once
#include <string>
#include <vector>

#include "Map.h"
#include "Utilities.h"

class Entity;
class Player;
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

    bool loadLevel(int levelIndex, std::string &error);
    void playTurn();
    bool isLevelFinished() const;
    void removeDeadEnemies();
    void render() const;
    void renderMap() const;
    void renderEntities() const;
    void renderHUD() const;
    void freeLevel();

    Map map;
    std::vector<Entity *> entities;
    int currentLevel = 0;   
    Player *player = nullptr;
};