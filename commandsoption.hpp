#pragma once

#include "abstractcommandoption.h"

template <typename T>
class CommandsOption final : public AbstractCommandOption
{
public:
    explicit CommandsOption(const std::string &key,
                            const std::string &alternativeKey,
                            const std::string &description)
        : AbstractCommandOption(key, alternativeKey, description)
    {
    }

    T getValue() const {
        return m_value;
    }

    std::string toString() {
        return (typeid(m_value) == typeid(std::string)) ? m_value : std::to_string(m_value);
    }

protected:
    bool tryParse() override {
        try {
            m_value = parse(m_commandArguments, m_value);
        }
        catch (...) {
            return false;
        }

        return true;
    }

    static int parse(const std::vector<std::string> &args, const int &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return std::stoi(args.at(first));
    }

    static bool parse(const std::vector<std::string> &args, const bool &b = true) {
        if (args.size() != 0)
            throw std::runtime_error("A boolean command line parameter cannot have any arguments.");

        return b;
    }

    static double parse(const std::vector<std::string> &args, const double &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return std::stod(args.at(first));
    }

    static float parse(const std::vector<std::string> &args, const float &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return std::stof(args.at(first));
    }

    static long double parse(const std::vector<std::string> &args, const long double &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return std::stold(args.at(first));
    }

    static unsigned int parse(const std::vector<std::string> &args, const unsigned int &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return static_cast<unsigned int>(std::stoul(args.at(first)));
    }

    static unsigned long parse(const std::vector<std::string> &args, const unsigned long &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return std::stoul(args.at(first));
    }

    static long parse(const std::vector<std::string> &args, const long &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return std::stol(args.at(first));
    }

    static std::string parse(const std::vector<std::string> &args, const std::string &) {
        if (args.size() != 1)
            throw std::bad_cast();

        return args.at(first);
    }

private:
    T m_value;

    enum {
        first = 0,
    };
};
