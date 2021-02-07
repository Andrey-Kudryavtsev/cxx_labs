#include "grabCommand.h"
#include "../robot/harvester.h"
#include "../point.h"

namespace mars
{
    void GrabCommand::execute(Harvester *harvester, Sapper *sapper, WorldMap & worldMap)
    {
        Point robotGlobalCoords = worldMap.toGlobalCoords(harvester->getLocalCoords());
        if (worldMap.getTile(robotGlobalCoords) == TileTypes::APPLE)                                             // если на глобальной карте робот стоит на яблоке
        {
            std::cout << "Collecting apple... Done!" << std::endl;
            harvester->grab();                                                                                   // сборщик хватает яблоко
            worldMap.setTile(robotGlobalCoords, TileTypes::EMPTY);                                               // очищаем клетку на глобальной карте
        }
    }
}
