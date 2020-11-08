#ifndef LIFEGAME_INPUTHANDLER_H
#define LIFEGAME_INPUTHANDLER_H

#include <string>
using namespace std;

enum class Command
{
    RESET,
    SET,
    CLEAR,
    STEP,
    BACK,
    SAVE,
    LOAD,
    WRONG_COMMAND,
    WRONG_COORDS,
    WRONG_TURN_AMOUNT,
};

class InputHandler
{
private:
    bool inBounds(size_t);
public:
    Command getCommand(const std::string &);
};

#endif //LIFEGAME_INPUTHANDLER_H
