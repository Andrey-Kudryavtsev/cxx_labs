#include <algorithm>
#include "repeater.h"

namespace mars
{
    Repeater::Repeater(const LocalMap &map) : m_map(map), m_bombDefused(false)
    {

    }

    Point Repeater::getNearestBombCoords(const Point &start) const
    {
        Point nearest = *(m_bombsCoords.begin());
        int32_t minDist = Point::manhattanDistance(start, nearest);
        for (const Point &elem : m_bombsCoords)
        {
            int32_t dist = Point::manhattanDistance(start, elem);
            if (dist < minDist)
            {
                minDist = dist;
                nearest = elem;
            }
        }
        return nearest;
    }

    bool Repeater::isBombDefused() const
    {
        return m_bombDefused;
    }

    const std::vector<Point> & Repeater::getDefusedBombs() const
    {
        return m_defusedBombsCoords;
    }

    void Repeater::resetDefusedBombs()
    {
        m_defusedBombsCoords.clear();
        m_bombDefused = false;
    }

    void Repeater::setBombDefused(bool b)
    {
        m_bombDefused = b;
    }

    void Repeater::addBombCoords(const Point &coords)
    {
        if (std::find(m_bombsCoords.begin(), m_bombsCoords.end(), coords) == m_bombsCoords.end())
        {
            m_bombsCoords.emplace_back(coords);
        }
    }

    void Repeater::eraseBombCoords(const Point &coords)
    {
        m_bombsCoords.erase(std::remove(m_bombsCoords.begin(), m_bombsCoords.end(), coords), m_bombsCoords.end());
    }

    const LocalMap & Repeater::getLocalMap() const
    {
        return m_map;
    }

    bool Repeater::allBombsDefused() const
    {
        return m_bombsCoords.empty();
    }

    void Repeater::updateBombCoords(const Point &modifiers)
    {
        for (Point &coords : m_bombsCoords)
        {
            coords.m_x += modifiers.m_x;
            coords.m_y += modifiers.m_y;
        }
    }

    void Repeater::addDefusedBombCoords(const Point &coords)
    {
        if (std::find(m_defusedBombsCoords.begin(), m_defusedBombsCoords.end(), coords) == m_defusedBombsCoords.end())
        {
            m_defusedBombsCoords.emplace_back(coords);
        }
    }
}
