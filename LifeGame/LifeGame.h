#ifndef LIFEGAME_LIFEGAME_H
#define LIFEGAME_LIFEGAME_H

#include "Field.h"
#include "InputHandler.h"
#include "GameLogic.h"

class LifeGame
{
private:
    InputHandler m_inputHandler;
    GameLogic m_gameLogic;
public:
    LifeGame() = default;

    void play();
};

#endif //LIFEGAME_LIFEGAME_H
