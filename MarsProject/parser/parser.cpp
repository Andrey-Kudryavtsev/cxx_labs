#include <iostream>
#include "optionparser.h"
#include "parser.h"
#include "../enums.h"

namespace mars
{
    struct Arg : public option::Arg
    {
        static void printError(const char *msg1, const option::Option &opt, const char *msg2)
        {
            std::cerr << msg1 << " " << opt.name << " " << msg2 << std::endl;
        }

        static option::ArgStatus Unknown(const option::Option &option, bool msg)
        {
            if (msg)
                printError("Unknown option '", option, "'\n");
            return option::ARG_ILLEGAL;
        }

        static option::ArgStatus NonEmpty(const option::Option &option, bool msg)
        {
            if (option.arg != 0 && option.arg[0] != 0)
                return option::ARG_OK;
            if (msg)
                printError("Option '", option, "' requires a non-empty argument\n");
            return option::ARG_ILLEGAL;
        }
    };

    const option::Descriptor usage[] =
            {
                    {static_cast<int>(OptionIndex::UNKNOWN),0,"","", Arg::Unknown,
                                                                               "USAGE: example [options]\n\n""Options:"},
                    {static_cast<int>(OptionIndex::FILE),0,"","file", Arg::NonEmpty,
                                                                               "  --file=FILENAME      Specify the .txt file, which is used to load a world map"},
                    {0,0,0,0,0,0}
            };

    bool Parser::parseCommandLine(int argc, char **argv, std::string *filename)
    {
        argc -= (argc > 0);
        argv += (argc > 0);
        option::Stats stats(usage, argc, argv);
        option::Option options[stats.options_max], buffer[stats.buffer_max];
        option::Parser parse(usage, argc, argv, options, buffer);
        if (parse.error())
            return false;
        if (argc == 0)
        {
            option::printUsage(std::cout, usage);
            return false;
        }
        if (options[static_cast<int>(OptionIndex::FILE)] != nullptr)
            *filename = static_cast<std::string>(options[static_cast<int>(OptionIndex::FILE)].first()->arg) + ".txt";
        return true;
    }

    ICommand * Parser::parseConsoleCommand(const std::string &input) /// ВЫДЕЛЯЕТ ДИНАМИЧЕСКУЮ ПАМЯТЬ!!!
    {
        ICommand * command = nullptr;
        if (input.substr(0, 5) == "MOVE ")
        {
            if (input[5] == 'U')
            {
                command = new MoveCommand(Direction::UP);
            } else if (input[5] == 'R')
            {
                command = new MoveCommand(Direction::RIGHT);
            } else if (input[5] == 'D')
            {
                command = new MoveCommand(Direction::DOWN);
            } else if (input[5] == 'L')
            {
                command = new MoveCommand(Direction::LEFT);
            }

        } else if (input == "SCAN")
        {
            command = new ScanCommand();
        } else if (input == "GRAB")
        {
            command = new GrabCommand();
        } else if (input == "SAPPER ON")
        {
            command = new SapperOnCommand();
        } else if (input == "SAPPER OFF")
        {
            command = new SapperOffCommand();
        } else if (input.substr(0, 9) == "SET_MODE ")
        {
            if (input.substr(9, 6) == "manual")
            {
                command = new ChangeModeCommand(Mode::MANUAL);
            } else if (input.substr(9, 5) == "scan ")
            {
                try
                {
                    size_t stepAmount = std::stoi(input.substr(14));
                    if (stepAmount < 1 || stepAmount > INT_MAX)
                    {
                        throw std::invalid_argument("out of bounds");
                    }
                    command = new ChangeModeCommand(Mode::SCAN, stepAmount);
                } catch (std::invalid_argument &e)
                {
                    command = nullptr;
                }
            } else if (input.substr(9, 4) == "auto")
            {
                command = new ChangeModeCommand(Mode::AUTO);
            }
        }
        return command;
    }
}
