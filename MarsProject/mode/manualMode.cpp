#include "manualMode.h"

namespace mars
{
    ManualMode * ManualMode::m_manualMode = nullptr;

    ManualMode * ManualMode::getInstance()
    {
        if (m_manualMode == nullptr)
        {
            m_manualMode = new ManualMode();
        }
        return m_manualMode;
    }
    void ManualMode::executeCommand(Harvester *harvester, Sapper *sapper, WorldMap & worldMap, ICommand * command)
    {
        command->execute(harvester, sapper, worldMap);
    }
}
