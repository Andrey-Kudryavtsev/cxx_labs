#ifndef LIFEGAME_GAMELOGIC_H
#define LIFEGAME_GAMELOGIC_H

#include <iostream>
#include "Field.h"

#include <thread>
#include <chrono>

using namespace std;

class GameLogic
{
private:
    Field m_field;
    size_t m_turnCounter = 0;
    bool m_isOver = false;
    bool m_backFlag = false; // флаг определяет возможность использования команды back: true - можно, false - нельзя
public:
    GameLogic() = default;
    bool isOver() const;
    void printStatus() const;
    void reset();
    void set(const string &);
    void clear(const string &);
    void step(const string &);
    void back();
    void save(const string &) const;
    void load(const string &);
};

#endif //LIFEGAME_GAMELOGIC_H
