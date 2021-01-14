#include <queue>
#include <map>
#include "scanMode.h"
#include "../command/moveCommand.h"
#include "../command/scanCommand.h"
#include <thread>
#include <chrono>

using t_elemAndPriority = std::pair<mars::Point, int>;
using std::vector;
using std::queue;
using std::priority_queue;
using std::map;

namespace mars
{
    ScanMode * ScanMode::m_scanMode = nullptr;

    ScanMode * ScanMode::getInstance()
    {
        if (m_scanMode == nullptr)
        {
            m_scanMode = new ScanMode();
        }
        return m_scanMode;
    }

    Point ScanMode::getNeighbour(const LocalMap &localMap, const Point &tile, Direction dir)
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

    struct CustomCompare
    {
        bool operator()(const t_elemAndPriority& lhs, const t_elemAndPriority& rhs)
        {
            return lhs.second > rhs.second;
        }
    };

    void ScanMode::getPathToNearestUnknownTile(vector<Point> &path, Harvester *harv, const bool *walkableTiles) // алгоритм Дийкстры
    {
        Point start = harv->getLocalCoords(); // начинаем искать с координат сборщика
        const LocalMap &localMap = harv->getLocalMap();

        priority_queue<t_elemAndPriority, vector<t_elemAndPriority>, CustomCompare> frontier; // расширяющаяся от сборщика граница
        map<Point, Point> came_from; // нужен для нахождения пути
        map<Point, int32_t> cost_so_far; // стоимость прохода к точке
        frontier.push(std::make_pair(start, 0));
        cost_so_far[start] = 0;
        while (!frontier.empty())
        {
            Point current = frontier.top().first;
            frontier.pop();

            if (!localMap.inBounds(current) || localMap.getTile(current) == TileTypes::UNKNOWN) // если точка не находится в границах карты или неизвестна, то ее нужно исследовать
            {
                std::cout << "Find point of interest: " << current << std::endl;
                for (Point elem = current; elem != start; elem = came_from[elem]) // записываем путь следующим образом: current, came_from[current], ... , start
                {
                    path.push_back(elem);
                }
                path.push_back(start);
                return;
            }
            for (int j = 0; j < 4; ++j) // проходимся по соседям клетки, добавляя их по возможности в границу
            {
                auto neighbour = getNeighbour(localMap, current, static_cast<Direction>(j));
                if (!localMap.inBounds(neighbour) || (neighbour != start && walkableTiles[static_cast<int>(localMap.getTile(neighbour))]))
                {
                    int32_t new_cost = cost_so_far[current] + 1;
                    if (cost_so_far[neighbour] == 0 || new_cost < cost_so_far[neighbour])
                    {
                        cost_so_far[neighbour] = new_cost;
                        int32_t priority = new_cost;
                        frontier.push(std::make_pair(neighbour, priority));
                        came_from[neighbour] = current;
                    }
                }
            }
        }
    }

    void ScanMode::moveAlongPath(vector<Point> &path, Harvester *harvester, Sapper *sapper, WorldMap &worldMap, sf::RenderWindow &window)
    {
        for (int32_t i = path.size() - 2; i > 0; --i) // путь записан следующим образом: current <- ... <- start // определяем в какую сторону нужно двигаться // доходим в клетку перед current
        {
            harvester->move(path[i]);
            std::this_thread::sleep_for(std::chrono::milliseconds(170));
            GraphicView::getInstance()->draw(harvester->getLocalMap(), harvester->getLocalCoords(), (sapper == nullptr) ? Point(-1, -1) : sapper->getLocalCoords(), window);
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::LostFocus)
                {
                    std::cout << "LOST FOCUS" << std::endl;
                }
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
        }
        ScanCommand scanCommand; // встали перед точкой, выполняем сканирование
        scanCommand.execute(harvester, sapper, worldMap);
    }

    void ScanMode::explore(Harvester *harvester, Sapper *sapper, WorldMap &worldMap, sf::RenderWindow &window)
    {
        while (m_stepAmount != 0)
        {
            vector<Point> path;
            bool walkableTiles[256] {false};
            walkableTiles[static_cast<int>(TileTypes::EMPTY)] = true;
            walkableTiles[static_cast<int>(TileTypes::APPLE)] = true;
            walkableTiles[static_cast<int>(TileTypes::UNKNOWN)] = true;
            getPathToNearestUnknownTile(path, harvester, walkableTiles);
            if (path.empty()) // если сборщик не смог найти путь ни к одной неиссследованной клетке
            {
                std::cout << "Every tile was explored, or left only unreachable" << std::endl;
                m_stepAmount = 0;
                return; // если хотя бы один сборщик не смог найти клетку для исследования, значит никто не найдет
            }
            moveAlongPath(path, harvester, sapper, worldMap, window); // если путь есть, то нужно по нему пройти
            m_stepAmount--;
        }
    }

    int32_t ScanMode::getStepAmount() const
    {
        return m_stepAmount;
    }

    void ScanMode::setStepAmount(int32_t stepAmount)
    {
        m_stepAmount = stepAmount;
    }
}
