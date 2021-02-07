#include <algorithm>
#include "harvester.h"

namespace mars
{
    Harvester::Harvester() : m_apples(0), m_localCoords(0, 0), m_destroyed(false)
    {

    }

    void Harvester::bindRepeater(Repeater *repeater)
    {
        m_repeater = repeater;
    }

    bool Harvester::isDestroyed() const
    {
        return m_destroyed;
    }

    void Harvester::destroy()
    {
        m_destroyed = true;
    }

    void Harvester::move(const Point &moveCoords)
    {
        m_localCoords = moveCoords;
    }

    void Harvester::scan()
    {

    }

    void Harvester::grab()
    {
        m_apples++;
        m_localMap.setTile(m_localCoords, TileTypes::EMPTY);
        eraseAppleCoords(m_localCoords);
        std::cout << "Collected " << m_apples << " apples! Keep looking around..." << std::endl;
    }

    void Harvester::updateLocalMap(const Point &coords, TileTypes tile)
    {
        m_localMap.setTile(coords, tile);
    }

    TileTypes Harvester::getTile(const Point &coords) const
    {
        return m_localMap.getTile(coords);
    }

    int32_t Harvester::getApples() const
    {
        return m_apples;
    }

    Point Harvester::getNearestAppleCoords() const
    {
        Point nearest = *(m_applesCoords.begin());
        int32_t minDist = Point::manhattanDistance(m_localCoords, nearest);
        for (const Point &elem : m_applesCoords)
        {
            int32_t dist = Point::manhattanDistance(m_localCoords, elem);
            if (dist < minDist)
            {
                minDist = dist;
                nearest = elem;
            }
        }
        return nearest;
    }

    void Harvester::addAppleCoords(const Point &coords)
    {
        if (std::find(m_applesCoords.begin(), m_applesCoords.end(), coords) == m_applesCoords.end())
        {
            m_applesCoords.emplace_back(coords);
        }
    }

    void Harvester::eraseAppleCoords(const Point &coords)
    {
        m_applesCoords.erase(std::remove(m_applesCoords.begin(), m_applesCoords.end(), coords), m_applesCoords.end());
    }

    void Harvester::addBombCoords(const Point &coords)
    {
        m_repeater->addBombCoords(coords);
    }

    bool Harvester::allApplesCollected() const
    {
        return m_applesCoords.empty();
    }

    const LocalMap & Harvester::getLocalMap() const
    {
        return m_localMap;
    }

    Point Harvester::expandLocalMap(std::bitset<4> dirs)
    {
        Point localCoordsModifiers = m_localMap.expand(dirs);                                                            /// выделенная динамическая память не теряется
        m_localCoords.m_x += localCoordsModifiers.m_x;
        m_localCoords.m_y += localCoordsModifiers.m_y;
        int i = 0;
        for (Point &coords : m_applesCoords)
        {
            ++i;
            coords.m_x += localCoordsModifiers.m_x;;
            coords.m_y += localCoordsModifiers.m_y;
        }
        m_repeater->updateBombCoords(localCoordsModifiers);
        return localCoordsModifiers;
    }

    bool Harvester::inBounds(const Point &coords) const
    {
        return m_localMap.inBounds(coords);
    }

    Point Harvester::getLocalCoords() const
    {
        return m_localCoords;
    }

    void Harvester::setLocalCoords(const Point &newCoords)
    {
        m_localCoords = newCoords;
    }

    Repeater * Harvester::getRepeater()
    {
        return m_repeater;
    }
}
