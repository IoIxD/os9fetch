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
    bool name_avaliable();
    void memory();
    void cpu();
    void model();
    void os();
    void rom();
    void battery();
    void gpu();
    void name();
    void line();
    void pprintMemory(float memSize);
    void pprintMemoryMB(float memSize);
    void disk_notice();
    bool is_utf8(const char *string);
    std::vector<short> drive_numbers();

    short disk_num();
    std::function<void()> disk(int listNum, short i);

    // void uptime();
    std::vector<std::function<void()>>
    functions();
}
#endif