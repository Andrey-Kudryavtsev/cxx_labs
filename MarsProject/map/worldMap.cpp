#include "ctime"
#include "worldMap.h"

namespace mars
{
    WorldMap::WorldMap(const int32_t width,
                       const int32_t height,
                       const std::string &map)
                       :
                       m_width(width),
                       m_height(height),
                       m_shift(0, 0)
    {
        m_worldMap = new TileTypes[m_height*m_width];
        for (int32_t i = 0; i < m_height*m_width; ++i)
        {
            m_worldMap[i] = static_cast<TileTypes>(map[i]);
        }
    }

    WorldMap::WorldMap(const int32_t width, const int32_t height) : m_width(width), m_height(height)
    {
        srand(std::time(nullptr));
        m_worldMap = new TileTypes[m_height*m_width];
        for (int32_t i = 0; i < m_height*m_width; ++i)
        {
            int32_t n = rand() % 100;
            if (n>=0 && n<80)
            {
                m_worldMap[i] = TileTypes::EMPTY;
            } else if (n>=80 && n<85)
            {
                m_worldMap[i] = TileTypes::APPLE;
            } else if (n>=85 && n<95)
            {
                m_worldMap[i] = TileTypes::ROCK;
            } else if (n>=95 && n<100)
            {
                m_worldMap[i] = TileTypes::BOMB;
            }
        }
    }

    WorldMap::~WorldMap()
    {
        delete[] m_worldMap;
    }

    bool WorldMap::inBounds(const Point &coords) const
    {
        return (coords.m_x >= 0 && coords.m_x < m_width && coords.m_y >= 0 && coords.m_y < m_height);
    }

    void WorldMap::setTile(const Point &coords, TileTypes tile)
    {
        m_worldMap[coords.m_y*m_width + coords.m_x] = tile;
    }

    TileTypes WorldMap::getTile(const Point &coords) const
    {
        return m_worldMap[coords.m_y*m_width + coords.m_x];
    }

    void WorldMap::setShift(const Point &shift)
    {
        m_shift = shift;
    }

    Point WorldMap::getShift() const
    {
        return m_shift;
    }

    int32_t WorldMap::getWidth() const
    {
        return m_width;
    }

    int32_t WorldMap::getHeight() const
    {
        return m_height;
    }

    Point WorldMap::toGlobalCoords(const Point &localCoords) const
    {
        Point res(localCoords.m_x + m_shift.m_x, localCoords.m_y + m_shift.m_y);
        return res;
    }

    std::ostream &operator<<(std::ostream &out, const WorldMap &worldMap)
    {
        for (size_t y = 0; y < worldMap.m_height; ++y)
        {
            for (size_t x = 0; x < worldMap.m_width; ++x)
            {
                out << static_cast<char>(worldMap.m_worldMap[y*worldMap.m_width + x]) << "  ";
            }
            out << std::endl;
        }

        return out;
    }
}
