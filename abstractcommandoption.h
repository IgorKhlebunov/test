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

    void setFound(bool found);
    void appendCommandArgument(const std::string &argument);

    inline std::string key() const {
        return m_commandKey;
    }

    inline std::string alternativeKey() const {
        return m_commandAlternativeKey;
    }

    inline std::string description() const {
        return m_description;
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
