#ifndef MARS_IMODE_H
#define MARS_IMODE_H

#include <vector>
#include "../robot/harvester.h"
#include "../command/iCommand.h"
#include "../map/worldMap.h"

namespace mars
{
    class IMode
    {
    public:
        virtual ~IMode() = default;
    };
}

#endif //MARS_IMODE_H
