#ifndef MARS_SAPPER_H
#define MARS_SAPPER_H

#include "iRobot.h"
#include "../repeater/repeater.h"

namespace mars
{
    class Sapper : public IRobot
    {
    private:
        Point m_localCoords;
        Repeater *m_repeater;
    public:
        Sapper();
        ~Sapper() override = default;

        Point getNearestBombCoords(const Point &) const;
        Point getLocalCoords() const;
        void setLocalCoords(const Point &);
        void bindRepeater(Repeater *);
        void move(const Point &) override;
        void defuse();
        Repeater * getRepeater();
        bool allBombsDefused() const;
        void eraseBombCoords(const Point &);
    };
}

#endif //MARS_SAPPER_H
