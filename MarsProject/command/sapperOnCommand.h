#ifndef MARS_SAPPERONCOMMAND_H
#define MARS_SAPPERONCOMMAND_H

#include "manualModeCommand.h"
#include "../robot/sapper.h"
#include "../repeater/repeater.h"

namespace mars
{
    class SapperOnCommand : public ICommand
    {
    private:
    public:
        SapperOnCommand() = default;
        ~SapperOnCommand() override = default;

        void execute(Harvester*, Sapper *, WorldMap &) override;
    };
}

#endif //MARS_SAPPERONCOMMAND_H
