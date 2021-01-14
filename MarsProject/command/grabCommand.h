#ifndef MARS_GRABCOMMAND_H
#define MARS_GRABCOMMAND_H

#include "manualModeCommand.h"

namespace mars
{
    class GrabCommand : public ManualModeCommand
    {
    public:
        GrabCommand() = default;
        ~GrabCommand() override = default;
        void execute(Harvester *, Sapper *, WorldMap &) override;
    };
}

#endif //MARS_GRABCOMMAND_H
