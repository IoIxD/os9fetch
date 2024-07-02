#include <stdio.h>
#include <Gestalt.h>
#include <string.h>
#include <string>
#include "functions.hpp"
namespace detection
{
    void os()
    {
        long sys = detection::gestalt(gestaltSystemVersion);
        if (sys != NULL)
        {
            static char buf[100];
            std::string version;
            const int len = std::snprintf(buf, sizeof(buf), "%lx", sys);
            version = std::string(buf, len);
            std::string version_final = std::string();

            for (int i = 0; i < version.length(); i++)
            {
                version_final += version[i];
                if (i <= version.length() - 2)
                {
                    version_final += ".";
                }
            }
            printf("OS Version: %s", version_final.c_str());
        }
    }
}