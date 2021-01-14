#include <thread>
#include <chrono>
#include <queue>
#include <map>
#include "autoMode.h"
#include "../command/moveCommand.h"
#include "../command/grabCommand.h"

using t_elemAndPriority = std::pair<mars::Point, int>;
using std::vector;
using std::queue;
using std::priority_queue;
using std::map;

namespace mars
{
    AutoMode * AutoMode::m_autoMode = nullptr;

    AutoMode * AutoMode::getInstance()
    {
        if (m_autoMode == nullptr)
        {
            m_autoMode = new AutoMode();
        }
        return m_autoMode;
    }

    Point AutoMode::getNeighbour(const LocalMap &localMap, const Point &tile, Direction dir)
    {
        Point coords;
        if (dir == Direction::UP)
        {
            coords = Point(tile.m_x, tile.m_y - 1);
        }
        if (dir == Direction::RIGHT)
        {
            coords = Point(tile.m_x + 1, tile.m_y);
        }
        if (dir == Direction::DOWN)
        {
            coords = Point(tile.m_x, tile.m_y + 1);
        }
        if (dir == Direction::LEFT)
        {
            coords = Point(tile.m_x - 1, tile.m_y);
        }
        return coords;
    }

    void AutoMode::moveAlongPath(std::vector<Point> &path, IRobot *robot, Point &otherRobotCoords, WorldMap &worldMap, sf::RenderWindow &window)
    {
        if (dynamic_cast<Harvester*>(robot))
        {
            Harvester *harvester = dynamic_cast<Harvester*>(robot);
            for (int32_t i = path.size() - 2; i >= 0; i--)
            {
                harvester->move(path[i]);
                std::this_thread::sleep_for(std::chrono::milliseconds(170));
                GraphicView::getInstance()->draw(harvester->getLocalMap(), harvester->getLocalCoords(), otherRobotCoords, window);
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                }
            }
            GrabCommand grabCommand;
            grabCommand.execute(harvester, nullptr, worldMap);
        } else if (dynamic_cast<Sapper*>(robot))
        {
            Sapper *sapper = dynamic_cast<Sapper*>(robot);
            for (int i = path.size(); i >= 0; i--)
            {
                std::cout << "Sapper moving" << std::endl;
                sapper->move(path[i]);
            }
            std::cout << "Sapper defusing" << std::endl;
            sapper->defuse();
        }
    }

    struct CustomCompare
    {
        bool operator()(const t_elemAndPriority& lhs, const t_elemAndPriority& rhs)
        {
            return lhs.second > rhs.second;
        }
    };

    void AutoMode::pathfinder(std::vector<Point> &path, const LocalMap &localMap, Point &start, Point &goal, Point &otherRobotCoords, const bool *walkableTiles) // алгоритм A*
    {
        priority_queue<t_elemAndPriority, std::vector<t_elemAndPriority>, CustomCompare> frontier;
        std::map<Point, Point> came_from;
        std::map<Point, int32_t> cost_so_far;
        frontier.push({start, 0});
        cost_so_far[start] = 0;
        while (!frontier.empty())
        {
            auto current = frontier.top().first;
            frontier.pop();

            if (current == goal)
            {
                for (auto elem = goal; elem != start; elem = came_from[elem]) // записываем путь следующим образом: goal, came_from[goal], ... , start
                {
                    std::cout << elem << " <- ";
                    path.push_back(elem);
                }
                std::cout << start << std::endl;
                path.push_back(start);
                return;
            }

            for (int j = 0; j < 4; ++j)
            {
                Point neighbour = getNeighbour(localMap, current, static_cast<Direction>(j));
                if  ((localMap.inBounds(neighbour)) && // соседа нужно добавлять только если он клетка в границах, по которой можно проехать, и не занята роботом
                     (neighbour != otherRobotCoords) &&
                     (walkableTiles[static_cast<int>(localMap.getTile(neighbour))])
                    )
                {
                    int32_t new_cost = cost_so_far[current] + 1;
                    if (cost_so_far[neighbour] == 0 || new_cost < cost_so_far[neighbour])
                    {
                        cost_so_far[neighbour] = new_cost;
                        int32_t priority = new_cost + Point::manhattanDistance(goal, neighbour);
                        frontier.push(std::make_pair(neighbour, priority));
                        came_from[neighbour] = current;
                    }
                }
            }
        }
    }

    void AutoMode::collectResources(Harvester *harvester, Sapper *sapper, WorldMap &worldMap, sf::RenderWindow &window)
    {
        while (!(harvester->allApplesCollected()))
        {
            harvester->printApple();
            Point start_harv = harvester->getLocalCoords();
            Point goal_harv = harvester->getNearestAppleCoords();
            std::vector<Point> path_harv;
            Point coords_sap = (sapper == nullptr) ? Point(-1, -1) : sapper->getLocalCoords();
            bool walkableTiles[256] {false};
            walkableTiles[static_cast<int>(TileTypes::EMPTY)] = true;
            walkableTiles[static_cast<int>(TileTypes::APPLE)] = true;
            pathfinder(path_harv, harvester->getLocalMap(), start_harv, goal_harv, coords_sap, walkableTiles);
            if (path_harv.empty())
            {
                std::cout << "Can't find a way to the apple" << std::endl;
                harvester->eraseAppleCoords(goal_harv);
            } else
            {
                moveAlongPath(path_harv, harvester, coords_sap, worldMap, window);
            }
        }
        while (sapper != nullptr && !(sapper->allBombsDefused()))
        {
            sapper->printBomb();
            Point start_sap = sapper->getLocalCoords();
            Point goal_sap = sapper->getNearestBombCoords(start_sap);
            std::vector<Point> path_sap;
            Point coords_harv = harvester->getLocalCoords();
            bool walkableTiles[256] {false};
            walkableTiles[static_cast<int>(TileTypes::EMPTY)] = true;
            walkableTiles[static_cast<int>(TileTypes::APPLE)] = true;
            walkableTiles[static_cast<int>(TileTypes::BOMB)] = true;
            pathfinder(path_sap, harvester->getLocalMap(), start_sap, goal_sap, coords_harv, walkableTiles);
            if (path_sap.empty())
            {
                std::cout << "Can't find a way to the bomb" << std::endl;
                sapper->eraseBombCoords(goal_sap);
            } else
            {
                moveAlongPath(path_sap, sapper, coords_harv, worldMap, window);
            }
        }
        Repeater *repeater = harvester->getRepeater();
        if (repeater->isBombDefused())                                                                                  // если хоть одна бомба обезврежена
        {
            std::cout << "Bomb has been defused" << std::endl;
            const std::vector<Point> &defusedBombs = repeater->getDefusedBombs();
            repeater->printDefusedBombs();
            for (const Point &bomb : defusedBombs)
            {
                std::cout << "bomb was erased" << std::endl;
                worldMap.setTile(worldMap.toGlobalCoords(bomb), TileTypes::EMPTY);                                     // удаляем бомбу с глобальной карты
                harvester->updateLocalMap(bomb, TileTypes::EMPTY);                                                      // удаляем бомбу с локальной карты
            }
            repeater->resetDefusedBombs();
        }
        GraphicView::getInstance()->draw(harvester->getLocalMap(), harvester->getLocalCoords(), (sapper == nullptr) ? Point(-1, -1) : sapper->getLocalCoords(), window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        std::cout << "Every reachable apple was collected and bomb defused" << std::endl;
    }
}
