#include "abstractcommandoption.h"

AbstractCommandOption::AbstractCommandOption(const std::string &key,
                                             const std::string &alternativeKey,
                                             const std::string &description)
    : m_commandKey(key)
    , m_commandAlternativeKey(alternativeKey)
    , m_description(description)
{
}

AbstractCommandOption::~AbstractCommandOption()
{
}

bool AbstractCommandOption::parseArguments()
{
    return tryParse();
}


bool AbstractCommandOption::isSet(const std::string &command) const
{
    return ((command == m_commandKey) ||
            (command == m_commandAlternativeKey));
}

void AbstractCommandOption::setFound(bool found)
{
    m_isFound = found;
}

void AbstractCommandOption::appendCommandArgument(const std::string &argument)
{
    m_commandArguments.push_back(argument);
}

bool AbstractCommandOption::tryParse()
{
    return false;
}
