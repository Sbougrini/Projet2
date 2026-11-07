// Sami Bougrini | Andy Donero
#pragma once

#include <string>
#include <vector>

#include <curses.h>

#include "Map.h"
#include "StateMachine.h"
#include "Utilities.h"

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

    // États de la partie
    void updateChoosePlayer();
    void updateLoadLevel();
    void updatePlaying();
    void updateGameEnd();
    void goToNextLevel();
    void endGame(const std::string &message);

    // Création des entités et chargement des niveaux
    static Player *createPlayer(char key);
    static Enemy *createEnemy(const EnemySpawn &spawn);
    bool loadLevel(int levelIndex, std::string &error);
    void freeLevel();

    // Tour de jeu
    void playTurn();
    void removeDeadEnemies();
    bool isLevelFinished() const;

    // Affichage
    static void initColors();
    void render() const;
    void renderMap() const;
    void renderEntities() const;
    void renderHUD() const;
    static WINDOW *openMessageWindow();
    static void showMessage(const std::string &message);

    static constexpr int LEVEL_COUNT = 5;
    static constexpr int HUD_WIDTH = 30;
    static constexpr int MESSAGE_WIDTH = 60;
    static constexpr int MESSAGE_HEIGHT = 10;
    static const std::string LEVEL_PATHS[LEVEL_COUNT];
    static const StateFunction STATE_FUNCTIONS[STATE_COUNT];

    State state = CHOOSE_PLAYER;
    std::string endMessage;
    int currentLevel = 0;
    Map map;
    Player *player = nullptr;
    std::vector<Entity *> entities;
    WINDOW *hudWindow = nullptr;
};