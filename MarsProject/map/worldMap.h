#ifndef MARS_FIELD_H
#define MARS_FIELD_H

#include <iostream>
#include "iMap.h"
#include "../point.h"

namespace mars
{
    class WorldMap : public IMap
    {
    private:
        const int32_t m_width;
        const int32_t m_height;
        TileTypes *m_worldMap;
        Point m_shift;
    public:
        WorldMap(int32_t, int32_t, const std::string &);
        WorldMap(int32_t, int32_t);
        ~WorldMap() override;

        bool inBounds(const Point &) const override;
        void setTile(const Point &, TileTypes) override;
        TileTypes getTile(const Point &) const override;
        void setShift(const Point &);
        Point getShift() const;
        int32_t getWidth() const override;
        int32_t getHeight() const override;
        Point toGlobalCoords(const Point &) const;

        friend std::ostream &operator<<(std::ostream &, const WorldMap &);
    };
}

#endif //MARS_FIELD_H
