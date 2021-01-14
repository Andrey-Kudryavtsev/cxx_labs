#include "scanCommand.h"
#include "../point.h"

namespace mars
{
    ScanCommand::ScanCommand()
    {

    }

    std::bitset<4> ScanCommand::checkCoords(Harvester *harvester) const
    {
        std::bitset<4> dirs(15);                                                                                         // abcd, где a - LEFT, b - DOWN, c - RIGHT, d - UP. Выставляем все флаги в 1
        Point localCoords = harvester->getLocalCoords();

        if (harvester->inBounds(Point(localCoords.m_x, localCoords.m_y - 1)))                           // проверяем верхнюю клетку
        {
            dirs.reset(static_cast<int>(Direction::UP));
        }
        if (harvester->inBounds(Point(localCoords.m_x + 1, localCoords.m_y)))                           // проверяем правую клетку
        {
            dirs.reset(static_cast<int>(Direction::RIGHT));
        }
        if (harvester->inBounds(Point(localCoords.m_x, localCoords.m_y + 1)))                           // проверяем нижнюю клетку
        {
            dirs.reset(static_cast<int>(Direction::DOWN));
        }
        if (harvester->inBounds(Point(localCoords.m_x - 1, localCoords.m_y)))                           // проверяем левую клетку
        {
            dirs.reset(static_cast<int>(Direction::LEFT));
        }

        return dirs;
    }

    void ScanCommand::exploreTile(Harvester *harvester, WorldMap &worldMap) const
    {
        Point robotLocalCoords = harvester->getLocalCoords();
        Point tileCoords;
        for (int32_t i = 0; i < 4; ++i)
        {
            switch (i)
            {
                case 0:
                    tileCoords = Point(robotLocalCoords.m_x, robotLocalCoords.m_y - 1); // клетка сверху от робота
                    break;
                case 1:
                    tileCoords = Point(robotLocalCoords.m_x + 1, robotLocalCoords.m_y); // клетка справа от робота
                    break;
                case 2:
                    tileCoords = Point(robotLocalCoords.m_x, robotLocalCoords.m_y + 1); // клетка снизу от робота
                    break;
                case 3:
                    tileCoords = Point(robotLocalCoords.m_x - 1, robotLocalCoords.m_y); // клетка слева от робота
                    break;
            }

            if (!(worldMap.inBounds(worldMap.toGlobalCoords(tileCoords))))
            {
                harvester->updateLocalMap(tileCoords, TileTypes::OUT_OF_BOUNDS);
            } else
            {
                TileTypes tile = worldMap.getTile(worldMap.toGlobalCoords(tileCoords));
                if (tile == TileTypes::APPLE)
                {
                    harvester->addAppleCoords(tileCoords);
                } else if (tile == TileTypes::BOMB)
                {
                    harvester->addBombCoords(tileCoords);
                }
                harvester->updateLocalMap(tileCoords, tile);
            }
        }
    }

    void ScanCommand::execute(Harvester *harvester, Sapper *sapper, WorldMap & worldMap)
    {
        std::bitset<4> dirs = checkCoords(harvester);                                                                   // проверяем, существуют ли клетки вокруг робота на его локальной карте
        Point modifiers = harvester->expandLocalMap(dirs);                                                              // расширяем локальную карту робота (перевыделяем под нее место)
        Point oldShift = worldMap.getShift();
        worldMap.setShift(Point(oldShift.m_x - modifiers.m_x, oldShift.m_y - modifiers.m_y));                     // меняем сдвиг робота относительно глобальной карты
        if (sapper != nullptr)
        {
            Point oldSapperCoords = sapper->getLocalCoords();
            sapper->setLocalCoords(Point(oldSapperCoords.m_x + modifiers.m_x, oldSapperCoords.m_y + modifiers.m_y));  // меняем локальные координаты сапера
        }
        exploreTile(harvester, worldMap);                                                                            // обновляем клетки на локальной карте, основываясь на глобальной
        std::cout << "Exploring.. Done!" << std::endl;
    }
}
