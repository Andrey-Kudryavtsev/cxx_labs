#ifndef MARS_ICOMMAND_H
#define MARS_ICOMMAND_H

#include <iostream>
#include "../robot/harvester.h"
#include "../robot/sapper.h"
#include "../map/worldMap.h"

namespace mars
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void execute(Harvester *, Sapper *, WorldMap &) = 0;
    };
}

#endif //MARS_ICOMMAND_H
