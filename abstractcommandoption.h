#pragma once

#include <string>
#include <vector>

class AbstractCommandOption
{
public:
    explicit AbstractCommandOption(const std::string &key, const std::string &alternativeKey, const std::string &description);

    virtual ~AbstractCommandOption();

    bool parseArguments();

    bool isSet(const std::string &command) const;

    inline bool isFound() const { return m_isFound; }
    inline std::vector<std::string> getArguments() const { return m_commandArguments; }

    void setFound(bool found);
    void appendCommandArgument(const std::string &argument);

    bool equal(const AbstractCommandOption &rhs) {
        return this->m_commandKey == rhs.m_commandKey &&
                this->m_commandAlternativeKey ==rhs.m_commandAlternativeKey;
    }

protected:
    virtual bool tryParse() = 0;

protected:
    std::string m_commandKey;
    std::string m_commandAlternativeKey;
    std::string m_description;

    bool m_isFound = false;
    std::vector<std::string> m_commandArguments = {};
};
