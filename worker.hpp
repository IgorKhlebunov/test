#pragma once

#include <vector>
#include <fstream>
#include <functional>
#include <iostream>
#include <exception>

class Worker final
{
public:
    Worker()
    {
    }

    bool parse(const std::string &fileName) {

        try {
            std::ifstream file(fileName, std::ios::in | std::ios::binary);

            if (!file.is_open())
                throw std::runtime_error("Failed to open file " + fileName);

            file.seekg(0, std::ios::end);
            const auto size = file.tellg();
            file.seekg(0, std::ios::beg);

            m_buffer.resize(size);

            file.read(&m_buffer[0], size);
            file.close();
        }
        catch (const std::exception & e) {
            std::cout << e.what() << std::endl;

            return false;
        }

        return true;
    }

    template <typename T>
    void exec(std::function<T(const std::vector<char>&)> &function) {
        std::cout << function(m_buffer) << std::endl;
    }

    template <typename T, typename U>
    void exec(std::function<T(const std::vector<char>&, const U&)> &function, const U &value) {
        std::cout << function(m_buffer, value) << std::endl;
    }

    template <typename T, typename ...Args>
    void exec(std::function<T(const std::vector<char>&, Args...)> &function, Args... args) {
        std::cout << function(m_buffer, args...) << std::endl;
    }

private:
    std::vector<char> m_buffer = {};
};
