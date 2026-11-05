// Andy Donero
#pragma once

#include "Entity.h"
#include <vector>

class Map;

class Player : public Entity
{
public:
    Player(const Vector2 &startPosition, int startingHealth);

    char readPlayerInputs() const;
    Vector2 getDirection(char key) const;

    bool isPlayer() const override;
    bool hasQuit() const;
    virtual bool canCastSpell() const;

protected:
    bool tryMove(char key, const Map &map, const std::vector<Entity *> &entities);

private:
    static constexpr char QUIT_KEY = '\b';
    bool quit = false;
};

inline bool Player::isPlayer() const
{
    return true;
}

inline bool Player::hasQuit() const
{
    return quit;
}

inline bool Player::canCastSpell() const
{
    return false;
}