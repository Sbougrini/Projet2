// Sami Bougrini
#include "Utilities.h"

const Vector2 Utilities::DIRECTION_OFFSETS[4] = {
    {0, -1}, // UP
    {0, 1},  // DOWN
    {-1, 0}, // LEFT
    {1, 0}   // RIGHT
};

Vector2 Utilities::offset(Direction direction)
{
    if (direction == Direction::NONE)
    {
        return Vector2{};
    }
    return DIRECTION_OFFSETS[static_cast<int>(direction)];
}

Direction Utilities::inputToDirection(int key)
{
    switch (key)
    {
    case 'z':
    case 'Z':
        return Direction::UP;
    case 's':
    case 'S':
        return Direction::DOWN;
    case 'q':
    case 'Q':
        return Direction::LEFT;
    case 'd':
    case 'D':
        return Direction::RIGHT;
    }
    return Direction::NONE;
}