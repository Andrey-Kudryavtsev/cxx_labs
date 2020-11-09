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
public:
    GameLogic(Field & field) : m_field(field){}

    Field m_field;
    size_t m_turnCounter = 0;
    bool m_isOver = false;
    bool m_backFlag = false; // флаг определяет возможность использования команды back: true - можно, false - нельзя

    void reset();
    void set(string &);
    void clear(string &);
    void step(string &);
    void back();
    void save(string &);
    void load(string &);
};

#endif //LIFEGAME_GAMELOGIC_H
