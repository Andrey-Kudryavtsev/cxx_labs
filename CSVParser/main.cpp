#include <iostream>
#include "Parser.h"

int main()
{
    try
    {
        std::ifstream in;
        in.open("in1.csv");
        if (!in.is_open())
        {
            throw std::runtime_error("Cannot open the file!");
        }

        csv::Parser<int, std::string, std::string, std::string, double> parser(in, 0);
        parser.setDelimiters(';', '\n', '"');
        for (std::tuple<int, std::string, std::string, std::string, double> rs : parser)
        {
            std::cout << rs << std::endl;
        }

//        csv::Parser<std::string, int, std::string, std::string, std::string, std::string, std::string, std::string> parser(in, 0);
//        parser.setDelimiters(';', '\n', '"');
//        for (std::tuple<std::string, int, std::string, std::string, std::string, std::string, std::string, std::string> rs : parser)
//        {
//            std::cout << rs << std::endl;
//        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}