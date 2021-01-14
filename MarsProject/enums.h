#ifndef MARS_ENUMS_H
#define MARS_ENUMS_H

namespace mars
{
    enum class TileTypes : char
    {
        UNKNOWN = 'U',       // робот не исследовал это клетку
        OUT_OF_BOUNDS = 'X', // клетка за границами глобальной карты
        EMPTY = '.',         // робот исследовал эту клетку и она пуста
        ROCK = 'R',          // клетка с камнем
        BOMB = 'B',          // клетка с бомбой
        APPLE = 'A',         // клетка с яблоком
        HARVESTER = 'H',     // клетка со сборщиком
        SAPPER = 'S',        // клетка с сапером
    };

    enum class Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT,
    };

    enum class OptionIndex
    {
        UNKNOWN,
        FILE,
    };

    enum class Mode
    {
        MANUAL,
        SCAN,
        AUTO,
    };
}

#endif //MARS_ENUMS_H
