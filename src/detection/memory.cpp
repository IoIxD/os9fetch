
#include <string>
#include <MacMemory.h>
#include "functions.hpp"
#include "Processes.h"
namespace detection
{
    void memory()
    {

        // failed attempt to get accumulated ram usage
        /*OSErr err = 0;
        ProcessSerialNumber ptr;
        unsigned long usedMem;
        while (err != -600)
        {
            err = GetNextProcess(&ptr);

            ProcessInfoRecPtr info;
            OSErr err2 = GetProcessInformation(&ptr, info);
            if (err2 != 50)
            {
                usedMem += (info->processSize - (long)info->processLocation) - info->processFreeMem;
            }
        }*/
        auto memsize = detection::gestalt(gestaltLogicalRAMSize);
        if (memsize != NULL)
        {
            printf("Memory: ");
            pprintMemory(memsize);
        }

        return;
    }
}
