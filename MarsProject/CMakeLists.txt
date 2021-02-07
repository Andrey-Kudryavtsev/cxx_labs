cmake_minimum_required(VERSION 3.17)
project(mars)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/SFML/install/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio window REQUIRED)

add_executable(mars main.cpp map/worldMap.cpp map/worldMap.h robot/iRobot.h robot/harvester.cpp robot/harvester.h parser/optionparser.h enums.h mode/iMode.h map/iMap.h map/localMap.cpp map/localMap.h view/iGameView.h view/graphicView.cpp view/graphicView.h mode/manualMode.cpp mode/manualMode.h command/iCommand.h command/manualModeCommand.h command/moveCommand.cpp command/moveCommand.h command/scanCommand.cpp command/scanCommand.h command/grabCommand.cpp command/grabCommand.h parser/parser.cpp parser/parser.h command/changeModeCommand.cpp command/changeModeCommand.h game.cpp game.h mode/scanMode.cpp mode/scanMode.h mode/autoMode.cpp mode/autoMode.h robot/sapper.cpp robot/sapper.h point.cpp point.h command/sapperOnCommand.cpp command/sapperOnCommand.h repeater/repeater.cpp repeater/repeater.h command/sapperOffCommand.cpp command/sapperOffCommand.h)

target_link_libraries(mars sfml-graphics sfml-audio sfml-window)