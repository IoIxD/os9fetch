#include <Gestalt.h>
#include <string>
#include "functions.hpp"

namespace detection
{
    void rom()
    {
        long sys = detection::gestalt(gestaltROMVersion);
        if (sys != NULL)
        {
            static char buf[100];
            std::string version;
            const int len = std::snprintf(buf, sizeof(buf), "%lu", sys);
            printf("ROM Version: %s", buf);
        }
    }
}