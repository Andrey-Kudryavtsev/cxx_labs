#ifndef MARS_SCANCOMMAND_H
#define MARS_SCANCOMMAND_H

#include <bitset>
#include "manualModeCommand.h"
#include "../robot/harvester.h"

namespace mars
{
    class ScanCommand : public ManualModeCommand
    {
    private:
        std::bitset<4> checkCoords(Harvester *) const;
        void exploreTile(Harvester *, WorldMap &) const;
    public:
        ScanCommand();
        void execute(Harvester *, Sapper *, WorldMap & worldMap) override;
    };
}

#endif //MARS_SCANCOMMAND_H
