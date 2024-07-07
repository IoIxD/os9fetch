

#include <vector>
#include <functional>
#include "functions.hpp"

namespace detection
{
    std::vector<std::function<void()>> functions()
    {
        int ver = os_version();

        auto vec = std::vector<std::function<void()>>();

        if (detection::name_avaliable())
        {
            vec.push_back(std::function<void()>(detection::name));
            vec.push_back(std::function<void()>(detection::line));
        }

        vec.push_back(std::function<void()>(detection::os));
        if (ver >= 0x600)
        {
            vec.push_back(std::function<void()>(detection::rom));
        }
        vec.push_back(std::function<void()>(detection::cpu));
        vec.push_back(std::function<void()>(detection::model));
        if (ver >= 0x600)
        {
            vec.push_back(std::function<void()>(detection::memory));
        }
        else
        {

            vec.push_back(std::function<void()>(detection::fpu));
            vec.push_back(std::function<void()>(detection::color));
            vec.push_back(std::function<void()>(detection::keyboard));
        }
        // As far as I know there was only one non-PPC laptop and it has a lead-acid battery that nobody even has working, so we'll be lazy and remove it. Feel free to correct me.
#ifdef FOR_PPC
        if (detection::has_battery())
        {
            vec.push_back(std::function<void()>(detection::battery));
        }
#endif

#ifdef FOR_PPC
        // Disk support.
        if (ver < 0x810)
        {
            short disks = detection::disk_num();
            auto numbers = detection::drive_numbers();
            for (int i = 0; i < disks; i++)
            {
                vec.push_back(std::function<void()>(detection::disk(i + 1, numbers[i])));
            }
        }
#endif
        return vec;
    }
}