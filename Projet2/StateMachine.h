// Sami Bougrini
#pragma once

class StateMachine
{
public:
    virtual ~StateMachine() = default;
    virtual void changeState(int newState) = 0;
    virtual void updateState(int input) = 0;
};