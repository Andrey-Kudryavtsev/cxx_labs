#ifndef MARS_SAPPEROFFCOMMAND_H
#define MARS_SAPPEROFFCOMMAND_H

#include "manualModeCommand.h"
#include "../robot/sapper.h"
#include "../repeater/repeater.h"

namespace mars
{
    class SapperOffCommand : public ICommand
    {
    private:
    public:
        SapperOffCommand() = default;
        ~SapperOffCommand() override = default;

        void execute(Harvester*, Sapper *, WorldMap &) override;
    };
}

#endif //MARS_SAPPEROFFCOMMAND_H
