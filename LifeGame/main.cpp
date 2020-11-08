#include <iostream>
#include "LifeGame.h"

using namespace std;

int main() {
    InputHandler inputHandler;
    Field field;
    GameLogic gameLogic(field);
    LifeGame game(inputHandler, gameLogic);
    game.play();

    return 0;
}
