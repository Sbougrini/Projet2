// Sami Bougrini | Andy Donero
#pragma once
#include "Map.h"
#include "StateMachine.h"
#include "Utilities.h"
#include <string>
#include <vector>

class Entity;
class Player;
class Enemy;
struct EnemySpawn;

class Game : public StateMachine
{
public:
    static Game &getInstance();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    void run();
    void changeState(int newState) override;
    void updateState() override;

private:
    enum State
    {
        CHOOSE_PLAYER = 0,
        LOAD_LEVEL,
        PLAYING,
        GAME_END,
        EXIT,
        STATE_COUNT
    };
    using StateFunction = void (Game::*)();

    Game() = default;
    ~Game();

    void updateChoosePlayer();
    void updateLoadLevel();
    void updatePlaying();
    void updateGameEnd();
    void goToNextLevel();
    void endGame(const std::string &message);

    static Enemy *createEnemy(const EnemySpawn &spawn);
    static Player *createPlayer(char key);
    bool loadLevel(int levelIndex, std::string &error);
    void playTurn();
    bool isLevelFinished() const;
    static void showMessage(const std::string &message);
    void removeDeadEnemies();
    void render() const;
    void renderMap() const;
    void renderEntities() const;
    void renderHUD() const;
    void freeLevel();

    static constexpr int LEVEL_COUNT = 5;
    static const std::string LEVEL_PATHS[LEVEL_COUNT];
    static const StateFunction STATE_FUNCTIONS[STATE_COUNT];
    State state = CHOOSE_PLAYER;
    std::string endMessage;
    Map map;
    std::vector<Entity *> entities;
    int currentLevel = 0;
    Player *player = nullptr;
};