#include <stdio.h>
#include <OSUtils.h>
#include <string.h>
#include <string>
#include "functions.hpp"
namespace detection
{
    int os_version()
    {

        SysEnvRec rec;
        SysEnvirons(1, &rec);
        return rec.systemVersion;
    }
    void os()
    {
        int sys = os_version();
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