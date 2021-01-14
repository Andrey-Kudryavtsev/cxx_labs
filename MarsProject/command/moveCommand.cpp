#include "moveCommand.h"

namespace mars
{
    MoveCommand::MoveCommand(Direction direction) : m_direction(direction)
    {

    }

    Point MoveCommand::getMoveCoords(Harvester *harvester) const
    {
        Point moveCoords;
        auto robotLocalCoords = harvester->getLocalCoords();
        if (m_direction == Direction::UP)
        {
            moveCoords = Point(robotLocalCoords.m_x, robotLocalCoords.m_y - 1);
        } else if (m_direction == Direction::RIGHT)
        {
            moveCoords = Point(robotLocalCoords.m_x + 1, robotLocalCoords.m_y);
        } else if (m_direction == Direction::DOWN)
        {
            moveCoords = Point(robotLocalCoords.m_x, robotLocalCoords.m_y + 1);
        } else if (m_direction == Direction::LEFT)
        {
            moveCoords = Point(robotLocalCoords.m_x - 1, robotLocalCoords.m_y);
        }
        return moveCoords;
    }

    void MoveCommand::execute(Harvester *harvester, Sapper *sapper, WorldMap &worldMap)
    {
        Point moveCoords = getMoveCoords(harvester);
        if (!(harvester->inBounds(moveCoords)) || harvester->getTile(moveCoords) == TileTypes::UNKNOWN)
        {
            std::cout << "unknown destination, scan first" << std::endl;
            return;
        }

        auto destinationTile = harvester->getTile(moveCoords);
        if (destinationTile == TileTypes::BOMB)
        {
            std::cout << "BOOM! Your robot was exploded!" << std::endl;
            harvester->destroy();
        } else if (destinationTile == TileTypes::OUT_OF_BOUNDS)
        {
            std::cout << "Destination out of bounds" << std::endl;
        } else if (destinationTile == TileTypes::ROCK)
        {
            std:: cout << "Rock on the way" << std::endl;
        } else if ((sapper != nullptr) && (moveCoords == sapper->getLocalCoords()))
        {
            std::cout << "Sapper is blocking the way" << std::endl;
        } else if (destinationTile == TileTypes::EMPTY || destinationTile == TileTypes::APPLE)
        {
            std::cout << "Moving... Done!" << std::endl;
            harvester->move(moveCoords);
//            harvester->setLocalCoords(moveCoords); // убрать в move() у сборщика
        } else
        {
            std::cout << "Unknown landscape" << std::endl;
        }
    }
}
