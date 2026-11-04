// Andy Donero
#include "Player.h"
#include "Utilities.h"
#include <curses.h>

Player::Player(const Vector2 &startPosition, int startingHealth)
{
    setPosition(startPosition);
    health = startingHealth;
}

int Player::readPlayerInputs() const
{
    return getch();
}

Vector2 Player::getDirection(int key) const
{
    return Utilities::offset(Utilities::inputToDirection(key));
}
