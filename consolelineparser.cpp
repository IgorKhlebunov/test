#include "consolelineparser.h"

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
    appendOption<bool>("-h", "--help", "Print usage on screen");
}

bool ConsoleLineParser::process()
{
    if (m_arguments.empty())
        return false;

    AbstractCommandOption *command = nullptr;

    for (const std::string &arg : m_arguments) {
        if (arg.empty())
            continue;

        if ((arg.at(0)) == '-') {
            command = find(arg);

            if (nullptr == command) {
                // TODO: print bad command message
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
            // TODO: print bad parse command message
            return false;
        }
    }

    return true;
}

AbstractCommandOption *ConsoleLineParser::find(const std::string &command)
{
    for(const auto & c : m_commands) {
        if (c->isSet(command))
            return c.get();
    }

    return nullptr;
}
