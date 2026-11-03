// Sami Bougrini
#pragma once

struct Vector2
{
    int x = 0;
    int y = 0;
};

enum class Direction
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Utilities
{
public:
    Utilities() = delete;
    static Vector2 add(const Vector2& position, const Vector2& delta);
    static Vector2 offset(Direction direction);
    static Direction inputToDirection(int key);

private:
    static const Vector2 DIRECTION_OFFSETS[4];
};