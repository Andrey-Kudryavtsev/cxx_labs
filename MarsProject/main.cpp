#include <fstream>
#include "SFML/Graphics.hpp"
#include "view/graphicView.h"
#include "game.h"

int main(int argc, char **argv) {
    std::string filename;
    if (!mars::Parser::parseCommandLine(argc, argv, &filename)) // парсинг командной строки
    {
        return 1;
    }

    std::ifstream fin;                                            // открытие файла с картой местности
    fin.open(filename);
    if (!fin.is_open())
    {
        std::cerr << "Can't open the file" << std::endl;
        return 1;
    }

    std::string map;
    std::string str;
    fin >> str;
    int32_t width = std::stoi(str);
    fin >> str;
    int32_t height = std::stoi(str);
    while (fin >> str)
    {
        map += str;
    }
    fin.close();

    mars::WorldMap worldMap(width, height, map);
    mars::Game game(width, height, worldMap);
    game.play();

    return 0;
}
