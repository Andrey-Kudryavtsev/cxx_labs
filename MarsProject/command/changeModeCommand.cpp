#include "changeModeCommand.h"

namespace mars
{
    ChangeModeCommand::ChangeModeCommand(Mode mode, uint32_t stepAmount) : m_mode(mode), m_stepAmount(stepAmount)
    {

    }

    void ChangeModeCommand::execute(Harvester *harvester, Sapper *sapper, WorldMap & worldMap) // зочем?
    {

    }

    Mode ChangeModeCommand::getMode() const
    {
        return m_mode;
    }

    int32_t ChangeModeCommand::getStepAmount() const
    {
        return m_stepAmount;
    }
}
