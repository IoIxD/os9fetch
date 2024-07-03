#include <functional>
#include <Disks.h>
#include <Files.h>
#include <stdio.h>
#include <string>
#include "functions.hpp"

namespace detection
{
    std::vector<short> driveNumbers;
    std::vector<short> drive_numbers()
    {
        return driveNumbers;
    };
    short disk_num()
    {
        OSErr err = 0;
        for (short i = 3; i < 31; i++)
        {
            unsigned char *volName;
            short vRefNum;
            long freeBytes;
            err = GetVInfo(i, volName, &vRefNum, &freeBytes);
            if (err == 0)
            {
                driveNumbers.push_back(i);
            }
        }

        return driveNumbers.size();
    }
    std::function<void()> disk(int listNum, short i)
    {
        return [listNum, i]
        {
            OSErr err;
            unsigned char *volName;
            short vRefNum;
            long freeBytes;

            err = GetVInfo(i, volName, &vRefNum, &freeBytes);
            if (err != 0)
            {
                printf("Error getting disk %d's name: %d", i, err);
                return;
            }

            HParamBlockRec sts = {
                .volumeParam = {
                    .ioCompletion = NULL,
                    .ioVolIndex = listNum,
                }};
            err = PBHGetVInfo(&sts, false);
            if (err != 0)
            {
                return;
            }
            auto io = sts.volumeParam;

            auto n = volName;
            auto len = n[0];
            auto str = std::string();
            for (int j = 1; j < len + 1; j++)
            {
                str += n[j];
            };

            float allBlocks = ((float)(unsigned short)io.ioVNmAlBlks * (float)(unsigned long)io.ioVAlBlkSiz);
            float freeBlocks = (float)(unsigned long)freeBytes;
            printf("Disk %d: %s, ", listNum, str.c_str());
            pprintMemory(allBlocks - freeBlocks);
            printf("/");
            pprintMemory(allBlocks);
            printf(" (");
            pprintMemory(freeBlocks);
            printf(" free) (ID: %d)", i);
        };
    }
}