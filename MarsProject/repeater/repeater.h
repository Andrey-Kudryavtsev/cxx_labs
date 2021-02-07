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
    };
}

#endif //MARS_REPEATER_H
