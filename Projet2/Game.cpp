// Sami Bougrini
#include "Game.h"
#include "Entity.h"
#include "HeadlessZombie.h"
#include "LevelParser.h"
#include "Player.h"
#include "Zombie.h"
#include "ZombieSwimmer.h"
/*#include "Warrior.h"*/ //Test
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <utility>

const std::string Game::LEVEL_PATHS[LEVEL_COUNT] = {
    "maps/Tuto.txt", "maps/level01.txt", "maps/level02.txt", "maps/level03.txt",
    "maps/levelFinal.txt"};

Enemy *Game::createEnemy(const EnemySpawn &spawn)
{
    Enemy *enemy = nullptr;
    switch (spawn.type) {
    case EnemyType::ZOMBIE:
        enemy = new Zombie();
        break;
    case EnemyType::HEADLESS_ZOMBIE:
        enemy = new HeadlessZombie();
        break;
    case EnemyType::ZOMBIE_SWIMMER:
        enemy = new ZombieSwimmer;
        break;
    }
    assert(enemy != nullptr);
    enemy->setPosition(spawn.position);
    return enemy;
}

Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

void Game::renderMap() const
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            mvaddch(y, x, map.getSymbol(Vector2{x, y}));
        }
    }
}

void Game::renderEntities() const
{
    for (Entity *entity : entities)
    {
        if (entity->isAlive())
        {
            Vector2 position = entity->getPosition();
            mvaddch(position.y, position.x, entity->getSymbol());
        }
    }
}

void Game::renderHUD() const
{
    mvprintw(MAP_HEIGHT + 1, 0, "PV : %d", player->getHealth());
}

void Game::render() const
{
    clear();
    renderMap();
    renderEntities();
    renderHUD();
    refresh();
}

void Game::run()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    std::srand(std::time(nullptr));

    // Pour tester :
    //player = new Warrior(Vector2{0, 0});
    //std::string error;
    //if (!loadLevel(currentLevel, error))
    //{
    //    printw("%s", error.c_str());
    //}
    //else
    //{
    //    while (player->isAlive())
    //    {
    //        render();
    //        playTurn();
    //    }
    //}
    getch();
    endwin();
}

Game::~Game()
{
    freeLevel();
    delete player;
}

bool Game::loadLevel(int levelIndex, std::string &error)
{
    assert(levelIndex >= 0 && levelIndex < LEVEL_COUNT);
    LevelData data;
    if (!LevelParser::parse(LEVEL_PATHS[levelIndex], data, error))
    {
        return false;
    }
    freeLevel();
    map = data.map;
    player->setPosition(data.playerStart);
    entities.push_back(player);
    for (const EnemySpawn &spawn : data.enemies)
    {
        entities.push_back(createEnemy(spawn));
    }
    return true;
}

void Game::freeLevel()
{
    for (Entity *entity : entities)
    {
        if (entity != player)
        {
            delete entity;
        }
    }
    entities.clear();
}

void Game::playTurn()
{
    for (Entity *entity : entities)
    {
        if (entity->isAlive())
        {
            entity->onUpdate(map, entities);
        }
    }
    removeDeadEnemies();
}

void Game::removeDeadEnemies()
{
    std::vector<Entity *> survivors;
    for (Entity *entity : entities)
    {
        if (entity == player || entity->isAlive())
        {
            survivors.push_back(entity);
        }
        else
        {
            delete entity;
        }
    }
    entities = std::move(survivors);
}