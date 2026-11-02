#pragma once
#include "Map.h"
#include "Utilities.h"
#include <string>
#include <vector>

class Player;
class Enemy;

class Game
{
public:
    static Game &getInstance();

    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    void run();
    std::vector<Enemy *> getEnemiesAround(const Vector2 &position) const;

private:
    Game() = default;
    ~Game();

    bool loadLevel(int levelIndex, std::string &error);
    void playTurn(int input);
    void moveEnemies();
    void handleCollisions();
    void removeDeadEnemies();
    void render() const;
    void freeLevel();

    Map map;
    Player *player = nullptr;
    std::vector<Enemy *> enemies;
    int currentLevel = 0;
};