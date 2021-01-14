#ifndef MARS_LOCALMAP_H
#define MARS_LOCALMAP_H

#include <bitset>
#include "iMap.h"
#include "../point.h"

namespace mars
{
    class LocalMap : public IMap
    {
    private:
        int32_t m_height;
        int32_t m_width;
        TileTypes *m_map;
    public:
        LocalMap();
        ~LocalMap() override;

        bool inBounds(const Point &) const override;
        void setTile(const Point &, TileTypes) override;
        TileTypes getTile(const Point &) const override;
        const TileTypes * getMap() const;
        int32_t getWidth() const override;
        int32_t getHeight() const override;
        Point expand(std::bitset<4>);

        friend std::ostream & operator<<(std::ostream &, const LocalMap &);
    };
}

#endif //MARS_LOCALMAP_H
