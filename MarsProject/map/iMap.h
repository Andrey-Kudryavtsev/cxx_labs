#ifndef MARS_IMAP_H
#define MARS_IMAP_H

#include <cstdint>
#include <iostream>
#include "../enums.h"
#include "../point.h"

namespace mars
{
    class IMap
    {
    public:
        IMap() = default;
        virtual ~IMap() = default;
        virtual bool inBounds(const Point &) const = 0;
        virtual void setTile(const Point &, TileTypes) = 0;
        virtual TileTypes getTile(const Point &) const = 0;
        virtual int32_t getWidth() const = 0;
        virtual int32_t getHeight() const = 0;
    };
}

#endif //MARS_IMAP_H
