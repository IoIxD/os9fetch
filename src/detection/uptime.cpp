#include <DriverServices.h>
#include <string>
#include <Gestalt.h>
#include "functions.hpp"

namespace detection
{
    /*void uptime()
    {
        auto time = UpTime();

        auto minutes = time.hi;

        double cycles = (time.hi + UINT32_MAX) + time.lo;
        double speed = (double)detection::gestalt(gestaltProcClkSpeed);
        if (speed != NULL)
        {
            printf("Uptime: %f", cycles / speed);
        }
    }*/
}