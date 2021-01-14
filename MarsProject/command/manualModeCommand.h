#ifndef MARS_MANUALMODECOMMAND_H
#define MARS_MANUALMODECOMMAND_H

#include "iCommand.h"

namespace mars
{
    class ManualModeCommand : public ICommand
    {
    public:
        virtual ~ManualModeCommand() = default;
        virtual void execute(Harvester *, Sapper *, WorldMap &) = 0;
    };
}

#endif //MARS_MANUALMODECOMMAND_H
