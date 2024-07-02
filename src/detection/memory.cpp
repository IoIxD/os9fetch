
#include <string>
#include <MacMemory.h>
#include "functions.hpp"
#include "Processes.h"
namespace detection
{
    void pprintMemory(long memsize)
    {
        if (memsize < 1024)
        {
            printf("%luB", memsize);
        }
        else if (memsize < 1000000)
        {
            printf("%luKB", memsize / 1024);
        }
        else if (memsize < 1000000000)
        {
            printf("%luMB", memsize / 1048576);
        }
        else if (memsize < 1000000000000)
        {
            printf("%luGB", memsize / 1073741824);
        }
        else if (memsize < 1000000000000000)
        {
            printf("%luTB", memsize / 1099511627776);
        }
        else if (memsize < 1000000000000000000)
        {
            printf("%luPB", memsize / 1125899906842624);
        }
    }
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
