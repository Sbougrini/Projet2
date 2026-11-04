// Andy Donero
#include "Player.h"
#include "Utilities.h"
#include <curses.h>

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
