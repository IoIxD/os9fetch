#include "functions.hpp"
namespace detection
{
    bool is_utf8(const char *string)
    {
        if (!string)
            return true;

        const unsigned char *bytes = (const unsigned char *)string;
        int num;

        while (*bytes != 0x00)
        {
            if ((*bytes & 0x80) == 0x00)
            {
                // U+0000 to U+007F
                num = 1;
            }
            else if ((*bytes & 0xE0) == 0xC0)
            {
                // U+0080 to U+07FF
                num = 2;
            }
            else if ((*bytes & 0xF0) == 0xE0)
            {
                // U+0800 to U+FFFF
                num = 3;
            }
            else if ((*bytes & 0xF8) == 0xF0)
            {
                // U+10000 to U+10FFFF
                num = 4;
            }
            else
                return false;

            bytes += 1;
            for (int i = 1; i < num; ++i)
            {
                if ((*bytes & 0xC0) != 0x80)
                    return false;
                bytes += 1;
            }
        }

        return true;
    }

    void pprintMemory(float memsize)
    {
        if (memsize < 1024.0f)
        {
            printf("%0.2fB", memsize);
        }
        else if (memsize < 1048576.0f)
        {
            printf("%0.2fKB", memsize / 1024.0f);
        }
        else if (memsize < 1073741824.0f)
        {
            printf("%0.2fMB", memsize / 1048576.0f);
        }
        else if (memsize < 1099511627776.0f)
        {
            printf("%0.2fGB", memsize / 1073741824.0f);
        }
        else if (memsize < 1125899906842624.0f)
        {
            printf("%0.2fTB", memsize / 1099511627776.0f);
        }
        else
        {
            printf("%0.2fPB", memsize / 1125899906842624.0f);
        }
    }

    void pprintMemoryMB(float memsize)
    {
        if (memsize < 1000.0f)
        {
            printf("%0.2fB", memsize);
        }
        else if (memsize < 1000000.0f)
        {
            printf("%0.2fKB", memsize / 1000.0f);
        }
        else if (memsize < 1000000000.0f)
        {
            printf("%0.2fMB", memsize / 1000000.0f);
        }
        else if (memsize < 1000000000000.0f)
        {
            printf("%0.2fGB", memsize / 1000000000.0f);
        }
        else if (memsize < 1000000000000000.0f)
        {
            printf("%0.2fTB", memsize / 1000000000000.0f);
        }
        else if (memsize < 1000000000000000000.0f)
        {
            printf("%0.2fPB", memsize / 1000000000000000);
        }
    }
}