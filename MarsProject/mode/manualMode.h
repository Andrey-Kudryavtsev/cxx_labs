#ifndef MARS_MANUALMODE_H
#define MARS_MANUALMODE_H

#include "iMode.h"

namespace mars
{
    class ManualMode : public IMode
    {
    private:
        static ManualMode * m_manualMode;

        ManualMode() = default;
    public:
        ManualMode(ManualMode &) = delete;
        ~ManualMode() override = default;
        void operator=(const ManualMode &) = delete;
        static ManualMode * getInstance();

        void executeCommand(Harvester *, Sapper *, WorldMap &, ICommand *);
    };
}

#endif //MARS_MANUALMODE_H
