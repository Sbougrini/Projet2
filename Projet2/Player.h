// Andy Donero
#pragma once

#include "Entity.h"

class Map;
class Enemy;
class Game;

class Player : public Entity
{
public:
    Player(const Vector2 &startPosition, int startingHealth);

    Vector2 getPosition() const override;
    bool isAlive() const override;

    void move(Direction direction, const Map &map);
    virtual void onEnemyCollision(Enemy &enemy) = 0;
    virtual bool useSpecial(Game &game);

protected:
    Vector2 position;
    int health = 0;
};
