#include "consolelineparser.h"

#include <sstream>
#include <iostream>
#include <algorithm>

ConsoleLineParser::ConsoleLineParser(int argc, const char **argv)
    : m_applicationName(argv[ARG_VALUES::ApplicationName])
{
    for (int i = ARG_VALUES::FirstArgument; i < argc; ++i)
        m_arguments.push_back(argv[i]);
}

ConsoleLineParser::ConsoleLineParser(int argc, char **argv)
    : m_applicationName(argv[ARG_VALUES::ApplicationName])
{
    for (int i = ARG_VALUES::FirstArgument; i < argc; ++i)
        m_arguments.push_back(argv[i]);
}

void ConsoleLineParser::enableHelpOption()
{
    appendOption<bool>("-h", "--help", "Print help.");
}

bool ConsoleLineParser::process()
{
    if (m_arguments.empty() ||
            std::find_if(m_arguments.begin(), m_arguments.end(), [](const std::string &s) -> bool {
                         return ("-h" == s) || ("--help" == s); }) != m_arguments.end()) {
        std::cout << this->usage() << std::endl;
        return false;
    }

    AbstractCommandOption *command = nullptr;

    for (const std::string &arg : m_arguments) {
        if (arg.empty())
            continue;

        if ((arg.at(0)) == '-') {
            command = find(arg);

            if (nullptr == command) {
                std::cout << howToUse(arg) << std::endl;
                return false;
            }

            command->setFound(true);
        }
        else if (command && command->isFound()) {
            command->appendCommandArgument(arg);
        }
    }

    for (const auto & c : m_commands) {
        if (c->isFound() && !c->parseArguments()) {
            std::cout << this->howToUse(c.get());
            return false;
        }
    }

    return true;
}

std::string ConsoleLineParser::howToUse(const std::string &command)
{
    const auto cmd = this->find(command);

    return cmd ? this->howToUse(cmd) : "Unknown " + command + " parameter.";
}

std::string ConsoleLineParser::usage()
{
    if (nullptr == this->find("-h"))
        return "Help option is not available.";

    std::stringstream stream { };
    stream << "\nUsage:\n";

    for (const auto &c : m_commands)
        stream << "  " << c->key() << "   " << c->alternativeKey() <<
                  "\t\t  " << c->description() << "\n";

    return stream.str();
}

AbstractCommandOption *ConsoleLineParser::find(const std::string &command)
{
    for (const auto & c : m_commands) {
        if (c->isSet(command))
            return c.get();
    }

    return nullptr;
}

std::string ConsoleLineParser::howToUse(AbstractCommandOption *command)
{
    if (nullptr == command)
        return "Unknown command line parameter.";

    std::stringstream stream { };
    stream << "The parameter " << command->key() << " or "<< command->alternativeKey() <<
              " has invalid arguments.\n" << "Use -h or --help option for more help.\n";

    return stream.str();
}
