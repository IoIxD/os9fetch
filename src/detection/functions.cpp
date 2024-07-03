

#include <vector>
#include <functional>
#include "functions.hpp"

namespace detection
{
    std::vector<std::function<void()>> functions()
    {
        auto vec = std::vector<std::function<void()>>();

        if (detection::name_avaliable())
        {
            vec.push_back(std::function<void()>(detection::name));
            vec.push_back(std::function<void()>(detection::line));
        }
        vec.push_back(std::function<void()>(detection::os));
        vec.push_back(std::function<void()>(detection::rom));
        // vec.push_back(std::function<void()>(detection::uptime));
        vec.push_back(std::function<void()>(detection::cpu));
        vec.push_back(std::function<void()>(detection::model));
        vec.push_back(std::function<void()>(detection::memory));
        if (detection::has_battery())
        {
            vec.push_back(std::function<void()>(detection::battery));
        }
        return vec;
    }
}