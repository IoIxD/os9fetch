#include <OSUtils.h>
#include <stdio.h>

namespace detection
{

    void
    fpu()
    {
        SysEnvRec rec;
        SysEnvirons(1, &rec);
        if (rec.hasFPU)
        {
            printf("FPU: Yes");
        }
        else
        {
            printf("FPU: No");
        }
    }

    void color()
    {
        SysEnvRec rec;
        SysEnvirons(1, &rec);
        if (rec.hasColorQD)
        {
            printf("Color: Yes");
        }
        else
        {
            printf("Color: No");
        }
    }

    void keyboard()
    {
        SysEnvRec rec;
        SysEnvirons(1, &rec);
        switch (rec.keyBoardType)
        {
        case 0:
            printf("Keyboard: Unknown");
            break;
        case 1:
            printf("Keyboard: Macintosh Keyboard");
            break;
        case 2:
            printf("Keyboard: Macintosh Keyboard (w/ Keypad)");
            break;
        case 3:
            printf("Keyboard: Macintosh Plus Keyboard (w/ Keypad)");
            break;
        case 4:
            printf("Keyboard: Apple Extended Keyboard");
            break;
        case 5:
            printf("Keyboard: Standard ADB Keyboard");
            break;
        case 6:
            printf("Keyboard: Portable ADB Keyboard");
            break;
        case 7:
            printf("Keyboard: Portable ISO Keyboard");
            break;
        case 8:
            printf("Keyboard: Standard ISO ADB");
            break;
        case 9:
            printf("Keyboard: Extended ISO ADB");
            break;
        }
    }
}