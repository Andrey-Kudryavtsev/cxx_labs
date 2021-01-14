#ifndef MARS_HARVESTER_H
#define MARS_HARVESTER_H

#include <iostream>
#include <bitset>
#include <vector>
#include "iRobot.h"
#include "../map/localMap.h"
#include "../point.h"
#include "../repeater/repeater.h"

namespace mars
{
    class Harvester : public IRobot
    {
    private:
        bool m_destroyed;
        LocalMap m_localMap;
        Point m_localCoords;
        int32_t m_apples;
        std::vector<Point> m_applesCoords;
        Repeater *m_repeater;
    public:

        Harvester();
        ~Harvester() override = default;

        void bindRepeater(Repeater *);
        bool isDestroyed() const;
        void destroy();
        void move(const Point &) override;
        void scan();
        void grab();
        void updateLocalMap(const Point &, TileTypes);
        TileTypes getTile(const Point &) const;
        int32_t getApples() const;
        Point getNearestAppleCoords() const;
        void addAppleCoords(const Point &);
        void eraseAppleCoords(const Point &);
        void addBombCoords(const Point &);
        bool allApplesCollected() const;
        const LocalMap & getLocalMap() const;
        Point expandLocalMap(std::bitset<4>);
        bool inBounds(const Point &) const;
        Point getLocalCoords() const;
        void setLocalCoords(const Point &);
        Repeater * getRepeater();
    };
}

#endif //MARS_HARVESTER_H
