#ifndef MARS_SCANMODE_H
#define MARS_SCANMODE_H

#include "iMode.h"
#include "../view/graphicView.h"
#include "../point.h"

namespace mars
{
    class ScanMode : public IMode
    {
    private:
        static ScanMode * m_scanMode;
        int32_t m_stepAmount = 0;

        ScanMode() = default;
    public:
        ScanMode(ScanMode &) = delete;
        ~ScanMode() override = default;
        void operator=(const ScanMode &) = delete;
        static ScanMode * getInstance();

        void explore(Harvester *, Sapper *, WorldMap &, sf::RenderWindow &);
        Point getNeighbour(const LocalMap &, const Point &, Direction);
        void moveAlongPath(std::vector<Point> &, Harvester *, Sapper *, WorldMap &, sf::RenderWindow &);
        void getPathToNearestUnknownTile(std::vector<Point> &, Harvester *, const bool *);
        int32_t getStepAmount() const;
        void setStepAmount(int32_t);
    };
}

#endif //MARS_SCANMODE_H
