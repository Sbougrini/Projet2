// Sami Bougrini | Andy Donero
#pragma once

struct Vector2
{
    int x = 0;
    int y = 0;
    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2{x + other.x, y + other.y};
    }

    bool operator==(const Vector2 &other) const
    {
        return x == other.x && y == other.y;
    }
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
    static Vector2 offset(Direction direction);
    static Direction inputToDirection(int key);

private:
    static constexpr int DIRECTION_COUNT = 4;
    static const Vector2 DIRECTION_OFFSETS[DIRECTION_COUNT];
};