#include <Gestalt.h>
#include <string>

namespace detection
{
    long gestalt(OSType l)
    {
        long res = NULL;
        auto err = Gestalt(l, &res);
        if (err != 0)
        {
            switch (err)
            {
            case -5500:
                printf("_SysEnvirons trap not present");
                break;
            case -5501:
                printf("negative number used in verReqNo");
                break;
            case -5502:
                printf("verReqNo version not handled by this system.");
                break;
            }
        }
        return res;
    };

}