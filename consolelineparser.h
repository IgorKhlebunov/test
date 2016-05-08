#pragma once

#include <string>
#include <vector>
#include <memory>

#include "abstractcommandoption.h"
#include "commandsoption.hpp"

class ConsoleLineParser final
{
public:
    explicit ConsoleLineParser(int argc, char **argv);
    explicit ConsoleLineParser(int argc, const char **argv);

    inline std::string getApplicationName() const {
        return m_applicationName;
    }

    void enableHelpOption();

    template <typename T>
    void appendOption(const std::string &key,
                      const std::string &alternativeKey,
                      const std::string &description) {

        m_commands.push_back( std::shared_ptr<AbstractCommandOption> (
                                  new CommandsOption<T>(key,alternativeKey, description)));
    }

    bool process();

    std::string howToUse(const std::string &command);
    std::string usage();

    template <typename T>
    T value(const std::string &key) {
        for (const auto &c : m_commands) {
            if (c->isSet(key)) {
                const auto command = dynamic_cast<CommandsOption<T> *>(c.get());

                if (nullptr == command)
                    throw std::runtime_error("Invalid usage of the parameter " + key + " detected.");

                return command->getValue();
            }
        }

        throw std::runtime_error("The parameter " + key + " could not be found.");
    }

private:
    AbstractCommandOption* find(const std::string &command);
    std::string howToUse(AbstractCommandOption * command);

private:
    std::string m_applicationName;
    std::vector<std::string> m_arguments = {};
    std::vector<std::shared_ptr<AbstractCommandOption>> m_commands = {};

    enum ARG_VALUES {
        ApplicationName = 0,
        FirstArgument = 1
    };
};
