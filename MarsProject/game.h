#ifndef MARS_GAME_H
#define MARS_GAME_H

#include "map/worldMap.h"
#include "mode/manualMode.h"
#include "mode/scanMode.h"
#include "mode/autoMode.h"
#include "view/graphicView.h"
#include "robot/harvester.h"
#include "robot/sapper.h"
#include "repeater/repeater.h"
#include "parser/parser.h"

namespace mars
{
    class Game
    {
    private:
        WorldMap m_worldMap;
        IMode *m_mode;
        Repeater *m_repeater; // TODO: сделать без указателей (если можно)
        Harvester *m_harvester;
        Sapper *m_sapper; // TODO: сделать поле isDestroyed как замену nullptr

        void changeMode(ChangeModeCommand &);
        void spawnSapper();
        void deleteSapper();
    public:
        Game(const size_t, const size_t, WorldMap &);
        ~Game();
        void play();


//        void printMode()                                 // TODO: удалить
//        {
//            if (dynamic_cast<ManualMode*>(m_mode))
//            {
//                std::cout << "manual" << std::endl;
//            } else if (dynamic_cast<ScanMode*>(m_mode))
//            {
//                std::cout << "scan" << std::endl;
//            } else if (dynamic_cast<AutoMode*>(m_mode))
//            {
//                std::cout << "auto" << std::endl;
//            }
//        }
    };
}

#endif //MARS_GAME_H
