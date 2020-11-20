#include <string>
#include <stdexcept>
#include "InputHandler.h"

bool InputHandler::inBounds(size_t x) const
{
    return (x >= 0 && x <=9);
}

Command InputHandler::getCommand(const std::string & command) const
{
    if (command == "reset") { return Command::RESET; }
    else if (command == "back") { return Command::BACK; }
    else if (command == "step")
    {
        return Command::STEP;
    }
    else if (command.substr(0, 5) == "step ")
    {
        try
        {
            size_t turnAmount = stoi(command.substr(5));
            if (turnAmount < 1 || turnAmount > INT_MAX) throw std::invalid_argument("out of bounds");
        } catch (std::invalid_argument& e)
        {
            return Command::WRONG_TURN_AMOUNT;
        }
        return Command::STEP;
    }
    else if (command.length() == 6 && command.substr(0, 4) == "set ")
    {
        try
        {
            size_t x = command[4] - 'A';
            size_t y = command[5] - '0';
            if (!inBounds(x) || !inBounds(y)) { throw std::invalid_argument("out of bounds"); }
        } catch (std::invalid_argument& e)
        {
            return Command::WRONG_COORDS;
        }
        return Command::SET;
    }
    else if (command.length() == 8 && command.substr(0, 6) == "clear ")
    {
        try
        {
            size_t x = command[6] - 'A';
            size_t y = command[7] - '0';
            if (!inBounds(x) || !inBounds(y)) { throw std::invalid_argument("out of bounds"); }
        } catch (std::invalid_argument& e)
        {
            return Command::WRONG_COORDS;
        }
        return Command::CLEAR;
    }
    else if (command.substr(0, 5) == "save ")
    {
        return Command::SAVE;
    }
    else if (command.substr(0, 5) == "load ")
    {
        return Command::LOAD;
    }
    else { return Command::WRONG_COMMAND; }
}
