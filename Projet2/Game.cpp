// Sami Bougrini | Andy Donero
#include "Game.h"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <utility>

#include <curses.h>

#include "Entity.h"
#include "HeadlessZombie.h"
#include "LevelParser.h"
#include "Mage.h"
#include "Player.h"
#include "Warrior.h"
#include "WarriorMage.h"
#include "Zombie.h"
#include "ZombieSwimmer.h"

const std::string Game::LEVEL_PATHS[LEVEL_COUNT] = {
    "maps/Tuto.txt", "maps/level01.txt", "maps/level02.txt", "maps/level03.txt",
    "maps/levelFinal.txt"};

const Game::StateFunction Game::STATE_FUNCTIONS[STATE_COUNT] = {
    &Game::updateChoosePlayer, &Game::updateLoadLevel, &Game::updatePlaying,
    &Game::updateGameEnd, nullptr};

Game &Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::~Game()
{
    freeLevel();
    delete player;
}

void Game::run()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    initColors();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    hudWindow = newwin(MAP_HEIGHT, HUD_WIDTH, 0, MAP_WIDTH + 2);
    while (state != EXIT)
    {
        updateState();
    }
    delwin(hudWindow);
    endwin();
}

void Game::changeState(int newState)
{
    assert(newState >= 0 && newState < STATE_COUNT);
    state = static_cast<State>(newState);
}

void Game::updateState()
{
    StateFunction function = STATE_FUNCTIONS[state];
    assert(function != nullptr);
    (this->*function)();
}

// États de la partie
void Game::updateChoosePlayer()
{
    WINDOW *window = openMessageWindow();
    mvwprintw(window, 1, 2, "Choisis un personnage :");
    mvwprintw(window, 3, 2, "1 : Warrior");
    mvwprintw(window, 4, 2, "2 : Mage");
    mvwprintw(window, 5, 2, "3 : WarriorMage");
    wrefresh(window);
    player = createPlayer(static_cast<char>(wgetch(window)));
    delwin(window);
    if (player != nullptr)
    {
        changeState(LOAD_LEVEL);
    }
}

void Game::updateLoadLevel()
{
    std::string error;
    if (loadLevel(currentLevel, error))
    {
        changeState(PLAYING);
    }
    else
    {
        endGame(error);
    }
}

void Game::updatePlaying()
{
    render();
    playTurn();
    if (player->hasQuit())
    {
        endGame("Vous avez quitte la partie...");
    }
    else if (!player->isAlive())
    {
        endGame("Game Over !");
    }
    else if (isLevelFinished())
    {
        goToNextLevel();
    }
}

void Game::updateGameEnd()
{
    showMessage(endMessage);
    changeState(EXIT);
}

void Game::goToNextLevel()
{
    ++currentLevel;
    if (currentLevel == LEVEL_COUNT)
    {
        endGame("VICTOIRE !");
    }
    else
    {
        changeState(LOAD_LEVEL);
    }
}

void Game::endGame(const std::string &message)
{
    endMessage = message;
    changeState(GAME_END);
}

// Création des entités et chargement des niveaux
Player *Game::createPlayer(char key)
{
    switch (key)
    {
    case '1':
        return new Warrior(Vector2{});
    case '2':
        return new Mage(Vector2{});
    case '3':
        return new WarriorMage(Vector2{});
    default:
        return nullptr;
    }
}

Enemy *Game::createEnemy(const EnemySpawn &spawn)
{
    Enemy *enemy = nullptr;
    switch (spawn.type)
    {
    case EnemyType::ZOMBIE:
        enemy = new Zombie();
        break;
    case EnemyType::HEADLESS_ZOMBIE:
        enemy = new HeadlessZombie();
        break;
    case EnemyType::ZOMBIE_SWIMMER:
        enemy = new ZombieSwimmer();
        break;
    }
    assert(enemy != nullptr);
    enemy->setPosition(spawn.position);
    return enemy;
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

// Tour de jeu
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

bool Game::isLevelFinished() const
{
    return player->isAlive() && map.isExit(player->getPosition());
}

// Affichage
void Game::initColors()
{
    if (!has_colors())
    {
        return;
    }
    start_color();
    init_pair(GROUND_COLOR, COLOR_WHITE, COLOR_GREEN);
    init_pair(WATER_COLOR, COLOR_BLUE, COLOR_BLUE);
    init_pair(MOUNTAIN_COLOR, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(EXIT_COLOR, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(PLAYER_COLOR, COLOR_CYAN, COLOR_BLACK);
    init_pair(ENEMY_COLOR, COLOR_RED, COLOR_RED);
}

void Game::render() const
{
    erase();
    renderMap();
    renderEntities();
    refresh();
    renderHUD();
}

void Game::renderMap() const
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            Vector2 position{x, y};
            int color = map.getColor(position);
            attron(COLOR_PAIR(color));
            mvaddch(y, x, map.getSymbol(position));
            attroff(COLOR_PAIR(color));
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
            int color = entity->isPlayer() ? PLAYER_COLOR : ENEMY_COLOR;
            attron(COLOR_PAIR(color) | A_BOLD);
            mvaddch(position.y, position.x, entity->getSymbol());
            attroff(COLOR_PAIR(color) | A_BOLD);
        }
    }
}

void Game::renderHUD() const
{
    werase(hudWindow);
    box(hudWindow, 0, 0);
    mvwprintw(hudWindow, 1, 2, "PV : %d", player->getHealth());
    mvwprintw(hudWindow, 2, 2, "Niveau : %d / %d", currentLevel + 1, LEVEL_COUNT);
    mvwprintw(hudWindow, 4, 2, "z, q, s, d : Deplacement");
    mvwprintw(hudWindow, 5, 2, "Retour : quitter");
    if (player->canCastSpell())
    {
        mvwprintw(hudWindow, 6, 2, "Espace : Sort");
    }
    wrefresh(hudWindow);
}

WINDOW *Game::openMessageWindow()
{
    clear();
    refresh();
    int startY = (LINES - MESSAGE_HEIGHT) / 2;
    int startX = (COLS - MESSAGE_WIDTH) / 2;
    WINDOW *window = newwin(MESSAGE_HEIGHT, MESSAGE_WIDTH, startY, startX);
    box(window, 0, 0);
    return window;
}

void Game::showMessage(const std::string &message)
{
    WINDOW *window = openMessageWindow();
    mvwprintw(window, 1, 2, "%s", message.c_str());
    mvwprintw(window, 3, 2, "Appuie sur une touche pour quitter");
    wrefresh(window);
    wgetch(window);
    delwin(window);
}