// Sami Bougrini
#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <curses.h>

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
    printw("Hello, World !");
    getch();
    endwin();
}

Game::~Game()
{
}