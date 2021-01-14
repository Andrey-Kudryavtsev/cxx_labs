#include <ctime>
#include <set>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "point.h"

namespace mars
{
    Game::Game(const size_t width, const size_t height, WorldMap & map) :
        m_worldMap(map)
    {
        srand(time(nullptr));
        Point harvCoords(rand() % width, rand() % height);
        m_harvester = new Harvester();
        m_repeater = new Repeater(m_harvester->getLocalMap());
        m_harvester->bindRepeater(m_repeater);
        m_sapper = nullptr;
        m_worldMap.setTile(harvCoords, TileTypes::EMPTY); // высаживаем сборщика на поверхность. Все, что было на месте высадки, уничтожается
        m_worldMap.setShift(harvCoords);
        m_mode = ManualMode::getInstance();               // начинаем с ручного режима
    }

    Game::~Game()
    {
        delete m_mode;
        delete m_harvester;
        delete m_sapper;
        delete m_repeater;

    }

    void Game::changeMode(ChangeModeCommand &command)
    {
        switch (command.getMode())
        {
            case Mode::MANUAL   :
                m_mode = ManualMode::getInstance();
                break;
            case Mode::SCAN     :
                m_mode = ScanMode::getInstance();
                ScanMode::getInstance()->setStepAmount(command.getStepAmount());
                break;
            case Mode::AUTO     :
                m_mode = AutoMode::getInstance();
                break;
        }
    }

    void Game::spawnSapper()
    {
        int32_t upBorderX = m_harvester->getLocalMap().getWidth();
        int32_t upBorderY = m_harvester->getLocalMap().getHeight();
        std::set<Point> emptyTiles;
        for (int32_t y = 0; y < upBorderY; ++y)
        {
            for (int32_t x = 0; x < upBorderX; ++x)
            {
                Point p(x, y);
                if ((m_harvester->getTile(p) == TileTypes::EMPTY) && (m_harvester->getLocalCoords() != p))
                {
                    emptyTiles.insert(p);
                }
            }
        }

        if (emptyTiles.empty())
        {
            std::cout << "No free space for sapper" << std::endl;
        } else
        {
            std::cout << "Sapper spawned" << std::endl;
            Point sapperCords = *(std::next(emptyTiles.begin(), rand() % emptyTiles.size()));
            delete m_sapper;
            m_sapper = new Sapper();
            m_sapper->setLocalCoords(sapperCords);
            m_sapper->bindRepeater(m_repeater);
        }
    }

    void Game::deleteSapper()
    {
        std::cout << "Sapper deleted" << std::endl;
        delete m_sapper;
        m_sapper = nullptr;
    }

    void Game::play()
    {
        sf::RenderWindow window(sf::VideoMode(750, 750), "M.A.R.S.", sf::Style::Close);
        GraphicView *graphicView = GraphicView::getInstance(); // синглтон
        bool focusOnWindow = true;
        while(window.isOpen())
        {
            graphicView->draw(m_harvester->getLocalMap(), m_harvester->getLocalCoords(), (m_sapper == nullptr) ? Point(-1, -1) : m_sapper->getLocalCoords(), window);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::LostFocus)
                {
                    std::cout << "CHANGE FOCUS" << std::endl;
                    focusOnWindow = !focusOnWindow;
                }
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            if (!focusOnWindow && dynamic_cast<ManualMode*>(m_mode))
            {
                std::string input;
                std::getline(std::cin, input);                                                                   // выполняем считывание команды с консоли
                ICommand *command = mars::Parser::parseConsoleCommand(input);                                           /// выделяет динамическую память под command, НЕОБХОДИМ delete command!
                if (dynamic_cast<ManualModeCommand*>(command) != nullptr)                                               // если команда является ManualModeCommand
                {
                    dynamic_cast<ManualMode*>(m_mode)->executeCommand(m_harvester, m_sapper, m_worldMap, command);   // выполнение команды
                } else if (dynamic_cast<SapperOnCommand*>(command) != nullptr)
                {
                    spawnSapper();
                } else if (dynamic_cast<SapperOffCommand*>(command) != nullptr)
                {
                    deleteSapper();
                } else if (dynamic_cast<ChangeModeCommand*>(command) != nullptr)                                        // если команда является ChangeModeCommand
                {
                    changeMode(*(dynamic_cast<ChangeModeCommand*>(command)));                                        // смена режима
                } else                                                                                                  // если некорректная команда
                {
                    std::cout << "wrong command" << std::endl;
                    continue;
                }
                delete command;                                                                                         /// а вот и он
            }
            if (dynamic_cast<ScanMode*>(m_mode))
            {
                auto scanMode = dynamic_cast<ScanMode*>(m_mode);
                scanMode->explore(m_harvester, m_sapper, m_worldMap, window);

                ChangeModeCommand toManual(Mode::MANUAL);
                changeMode(toManual);
            }
            if (dynamic_cast<AutoMode*>(m_mode))
            {
                auto autoMode = dynamic_cast<AutoMode*>(m_mode);
                autoMode->collectResources(m_harvester, m_sapper, m_worldMap, window);

                ChangeModeCommand toManual(Mode::MANUAL);
                changeMode(toManual);
            }
            if (m_harvester->isDestroyed())
            {
                std::cout << "You've lost all your harvesters! Mars good at keeping secrets..." << std::endl;
                window.close();
            }
        }
    }
}
