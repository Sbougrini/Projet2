// Andy Donero
#include "Player.h"

#include <curses.h>

#include "Utilities.h"

Player::Player(const Vector2 &startPosition, int startingHealth)
{
    setPosition(startPosition);
    health = startingHealth;
}

char Player::readPlayerInputs() const
{
    return static_cast<char>(getch());
}

Vector2 Player::getDirection(char key) const
{
    return Utilities::offset(Utilities::inputToDirection(key));
}

bool Player::tryMove(char key, const Map &map, const std::vector<Entity *> &entities)
{
    if (key == QUIT_KEY)
    {
        quit = true;
        return true;
    }
    Vector2 direction = getDirection(key);
    if (direction == Vector2{})
    {
        return false;
    }
    return move(direction, map, entities);
}
