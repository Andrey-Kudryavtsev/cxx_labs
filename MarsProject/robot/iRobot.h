#ifndef MARS_IROBOT_H
#define MARS_IROBOT_H

#include "../point.h"

namespace mars
{
    class IRobot
    {
    private:
    public:
        virtual ~IRobot() = default;
        virtual void move(const Point &) = 0;
    };
}

#endif //MARS_IROBOT_H
