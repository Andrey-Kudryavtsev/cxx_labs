#ifndef MARS_IGAMEVIEW_H
#define MARS_IGAMEVIEW_H

#include <iostream>
#include "../map/localMap.h"
#include "../point.h"

namespace mars
{
    class IGameView
    {
    public:
        IGameView() = default;
        virtual ~IGameView() = default;
        virtual void draw(const LocalMap &, const Point &, const Point &, sf::RenderWindow &) = 0;
    };
}

#endif //MARS_IGAMEVIEW_H
