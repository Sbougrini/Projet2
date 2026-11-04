// Sami Bougrini
#include "Utilities.h"
#include <cassert>

const Vector2 Utilities::DIRECTION_OFFSETS[DIRECTION_COUNT] = {
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
    int index = static_cast<int>(direction);
    assert(index >= 0 && index < DIRECTION_COUNT);
    return DIRECTION_OFFSETS[index];
}

Direction Utilities::inputToDirection(char key)
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