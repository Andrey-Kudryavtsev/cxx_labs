#include "localMap.h"

namespace mars
{
    LocalMap::LocalMap() : m_height(1), m_width(1)                                                                       /// маленькое число для проверки, изменить
    {
        m_map = new TileTypes[m_height * m_width];
        for (int32_t i = 0; i < m_height*m_width; ++i)
        {
            m_map[i] = TileTypes::EMPTY;
        }
    }

    LocalMap::~LocalMap()
    {
        delete[] m_map;
    }

    bool LocalMap::inBounds(const Point &coords) const
    {
        return (coords.m_x >= 0 && coords.m_x < m_width && coords.m_y >= 0 && coords.m_y < m_height);
    }

    void LocalMap::setTile(const Point &coords, TileTypes tile)
    {
        m_map[coords.m_y*m_width + coords.m_x] = tile;
    }

    TileTypes LocalMap::getTile(const Point &coords) const
    {
        return m_map[coords.m_y*m_width + coords.m_x];
    }

    const TileTypes * LocalMap::getMap() const
    {
        return m_map;
    }

    int32_t LocalMap::getWidth() const
    {
        return m_width;
    }

    int32_t LocalMap::getHeight() const
    {
        return m_height;
    }

    Point LocalMap::expand(std::bitset<4> dirs)
    {
        Point XYModifiers(0, 0);
        if (dirs == 0)
        {
            return XYModifiers;
        }
        int32_t add = 2;
        int32_t new_width = m_width;
        int32_t new_height = m_height;

        if (dirs.test(static_cast<int>(Direction::UP)))
        {
            new_height += add;
            XYModifiers.m_y = add;
        }
        if (dirs.test(static_cast<int>(Direction::RIGHT)))
        {
            new_width += add;
        }
        if (dirs.test(static_cast<int>(Direction::DOWN)))
        {
            new_height += add;
        }
        if (dirs.test(static_cast<int>(Direction::LEFT)))
        {
            new_width += add;
            XYModifiers.m_x = add;
        }

        auto *new_map = new TileTypes[new_height * new_width];                                                           /// выделяется динамическая память
        for (int32_t y = 0; y < new_height; ++y)
        {
            for (int32_t x = 0; x < new_width; ++x)
            {
                if (inBounds(Point(x - XYModifiers.m_x, y - XYModifiers.m_y)))
                {
                    new_map[y*new_width + x] = m_map[(y-XYModifiers.m_y)*m_width + (x-XYModifiers.m_x)];
                } else
                {
                    new_map[y*new_width + x] = TileTypes::UNKNOWN;
                }
            }
        }

        delete [] m_map;                                                                                            /// удаляется старая динамическая память
        m_width = new_width;
        m_height = new_height;
        m_map = new_map;                                                                                            /// выделенная динамическая память не теряется
        return XYModifiers;
    }

    std::ostream &operator<<(std::ostream &out, const LocalMap &localMap)
    {
        for (size_t y = 0; y < localMap.m_height; ++y)
        {
            for (size_t x = 0; x < localMap.m_width; ++x)
            {
                out << static_cast<char>(localMap.m_map[y*localMap.m_width + x]) << "  ";
            }
            out << std::endl;
        }

        return out;
    }
}
