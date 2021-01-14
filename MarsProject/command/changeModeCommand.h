#ifndef MARS_CHANGEMODECOMMAND_H
#define MARS_CHANGEMODECOMMAND_H

#include <cstdint>
#include "iCommand.h"
#include "../enums.h"

namespace mars
{
    class ChangeModeCommand : public ICommand
    {
    private:
        Mode m_mode;
        uint32_t m_stepAmount;
    public:
        ChangeModeCommand(Mode, uint32_t = 0);
        void execute(Harvester *, Sapper *, WorldMap &) override;
        Mode getMode() const;
        int32_t getStepAmount() const;
    };

}
#endif //MARS_CHANGEMODECOMMAND_H
