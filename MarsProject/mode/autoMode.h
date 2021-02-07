#ifndef MARS_AUTOMODE_H
#define MARS_AUTOMODE_H

#include "iMode.h"
#include "../robot/sapper.h"
#include "../view/graphicView.h"

namespace mars
{
    class AutoMode : public IMode
    {
    private:
        static AutoMode * m_autoMode;

        AutoMode() = default;
    public:
        AutoMode(AutoMode &) = delete;
        ~AutoMode() override = default;
        void operator=(const AutoMode &) = delete;
        static AutoMode * getInstance();

        Point getNeighbour(const LocalMap &, const Point &, Direction);
        void pathfinder(std::vector<Point> &, const LocalMap &, Point &, Point &, Point &, const bool *);
        void moveAlongPath(std::vector<Point> &, IRobot *, Point &, WorldMap &, sf::RenderWindow &);
        void collectResources(Harvester *, Sapper *, WorldMap &, sf::RenderWindow &);
    };
}

#endif //MARS_AUTOMODE_H
