#ifndef MARS_REPEATER_H
#define MARS_REPEATER_H

#include <vector>
#include "../map/localMap.h"
#include "../point.h"

namespace mars
{
    class Repeater
    {
    private:
        std::vector<Point> m_bombsCoords;
        std::vector<Point> m_defusedBombsCoords;
        bool m_bombDefused;
        const LocalMap &m_map;
    public:
        Repeater(const LocalMap &map);
        ~Repeater() = default;

        Point getNearestBombCoords(const Point &) const;
        bool isBombDefused() const;
        void setBombDefused(bool);
        const std::vector<Point> & getDefusedBombs() const;
        void resetDefusedBombs();
        void addBombCoords(const Point &);
        void eraseBombCoords(const Point &);
        const LocalMap & getLocalMap() const;
        bool allBombsDefused() const;
        void updateBombCoords(const Point &);
        void addDefusedBombCoords(const Point &);

        void printDefusedBombs()
        {
            for (auto &bomb : m_defusedBombsCoords)
            {
                std::cout << bomb << ", ";
            }
            std::cout << std::endl;
        }

        void printBombs()
        {
            for (auto &bomb : m_bombsCoords)
            {
                std::cout << bomb << ", ";
            }
            std::cout << std::endl;
        }
    };
}
// сборщик хранит указатель на передатчик
// передатчик создается в конструкторе игры
// передатчик имеет поле updated, которое каждый ход чекает сапер
// если значение true, то карта сапера обновляется
// сапер разминирует бомбы, указанные в поле m_bombsCoords, а сборщик записывает туда обнаруженные бомбы
// как поступить с картой сапера? Дать ему свою, или пусть хранит указатель на карту в передатчике?

#endif //MARS_REPEATER_H
