#include <Quickdraw.h>
#include <string>

namespace detection
{
    void screen()
    {
        short hortizontal;
        short vertical;

        ScreenRes(&hortizontal, &vertical);
        printf("Resolution: %dx%d", hortizontal, vertical);
    }
}