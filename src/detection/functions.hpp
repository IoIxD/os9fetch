#ifndef FUNCTIONS
#define FUNCTIONS
#include <vector>
#include <functional>
#include <string>
#include <Gestalt.h>

namespace detection
{
    long gestalt(OSType l);
    bool has_battery();
    void memory();
    void cpu();
    void model();
    void os();
    void rom();
    void battery();
    void gpu();

    // void uptime();
    std::vector<std::function<void()>> functions();
}
#endif