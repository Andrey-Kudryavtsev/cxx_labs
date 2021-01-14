#ifndef MARS_PARSER_H
#define MARS_PARSER_H

#include "../command/moveCommand.h"
#include "../command/scanCommand.h"
#include "../command/grabCommand.h"
#include "../command/changeModeCommand.h"
#include "../command/sapperOnCommand.h"
#include "../command/sapperOffCommand.h"

namespace mars
{
    class Parser
    {
    public:
        static bool parseCommandLine(int, char **, std::string *);
        static ICommand * parseConsoleCommand(const std::string &);
    };
}

#endif //MARS_PARSER_H
