#ifndef MARS_MOVECOMMAND_H
#define MARS_MOVECOMMAND_H

#include <algorithm>
#include "manualModeCommand.h"
#include "../enums.h"
#include "../robot/harvester.h"
#include "../point.h"

namespace mars
{
    class MoveCommand : public ManualModeCommand
    {
        Direction m_direction;
    public:
        MoveCommand(Direction);
        void execute(Harvester *, Sapper *, WorldMap &) override;
        Point getMoveCoords(Harvester *) const;
    };
}

#endif //MARS_MOVECOMMAND_H
