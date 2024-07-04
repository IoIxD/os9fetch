#include <functional>
#include <Disks.h>
#include <Files.h>
#include <stdio.h>
#include <string>
#include "functions.hpp"

#define _FSDispatch 0xA060

namespace detection
{
    pascal OSErr __PBXGetVolInfoSync(XVolumeParamPtr paramBlock)
    {
        enum
        {
            kXGetVolInfoSelector = 0x0012, /* Selector for XGetVolInfo */

            uppFSDispatchProcInfo = kRegisterBased | REGISTER_RESULT_LOCATION(kRegisterD0) | RESULT_SIZE(SIZE_CODE(sizeof(OSErr))) | REGISTER_ROUTINE_PARAMETER(1, kRegisterD1, SIZE_CODE(sizeof(long))) /* trap word */
                                    | REGISTER_ROUTINE_PARAMETER(2, kRegisterD0, SIZE_CODE(sizeof(long)))                                                                                                /* selector */
                                    | REGISTER_ROUTINE_PARAMETER(3, kRegisterA0, SIZE_CODE(sizeof(XVolumeParamPtr)))
        };

        return (CallOSTrapUniversalProc(NGetTrapAddress(_FSDispatch, OSTrap),
                                        uppFSDispatchProcInfo,
                                        _FSDispatch,
                                        kXGetVolInfoSelector,
                                        paramBlock));
    }
    OSErr HGetVInfo(short volReference,
                    StringPtr volName,
                    short *vRefNum,
                    unsigned long *freeBytes,
                    unsigned long *totalBytes)
    {
        HParamBlockRec pb;
        unsigned long allocationBlockSize;
        unsigned short numAllocationBlocks;
        unsigned short numFreeBlocks;
        VCB *theVCB;
        Boolean vcbFound;
        OSErr result;

        pb.volumeParam.ioVRefNum = volReference;
        pb.volumeParam.ioNamePtr = volName;
        pb.volumeParam.ioVolIndex = 0;
        result = PBHGetVInfoSync(&pb);

        if (result == noErr)
        {

            *vRefNum = pb.volumeParam.ioVRefNum;
            allocationBlockSize = (unsigned long)pb.volumeParam.ioVAlBlkSiz;

            vcbFound = false;
            theVCB = (VCB *)(GetVCBQHdr()->qHead);
            while ((theVCB != NULL) && !vcbFound)
            {

                if (theVCB->vcbSigWord == 0x4244)
                {
                    if (theVCB->vcbVRefNum == *vRefNum)
                    {
                        vcbFound = true;
                    }
                }

                if (!vcbFound)
                {
                    theVCB = (VCB *)(theVCB->qLink);
                }
            }

            if (theVCB != NULL)
            {

                numAllocationBlocks = (unsigned short)theVCB->vcbNmAlBlks;
                numFreeBlocks = (unsigned short)theVCB->vcbFreeBks;
            }
            else
            {

                numAllocationBlocks = (unsigned short)pb.volumeParam.ioVNmAlBlks;
                numFreeBlocks = (unsigned short)pb.volumeParam.ioVFrBlk;
            }

            *freeBytes = numFreeBlocks * allocationBlockSize;
            *totalBytes = numAllocationBlocks * allocationBlockSize;
        }

        return (result);
    }
    OSErr XGetVInfo(short volReference,
                    StringPtr volName,
                    short *vRefNum,
                    UnsignedWide *freeBytes,
                    UnsignedWide *totalBytes)
    {
        OSErr result;
        long response;
        XVolumeParam pb;

        if ((Gestalt(gestaltFSAttr, &response) == noErr) && ((response & (1L << gestaltFSSupports2TBVols)) != 0))
        {

            pb.ioVRefNum = volReference;
            pb.ioNamePtr = volName;
            pb.ioXVersion = 0;
            pb.ioVolIndex = 0;
            result = __PBXGetVolInfoSync(&pb);
            if (result == noErr)
            {

                *vRefNum = pb.ioVRefNum;

                *totalBytes = (UnsignedWide)pb.ioVTotalBytes;
                *freeBytes = (UnsignedWide)pb.ioVFreeBytes;
            }
        }
        else
        {

            result = HGetVInfo(volReference, volName, vRefNum, &freeBytes->lo, &totalBytes->lo);
            if (result == noErr)
            {

                totalBytes->hi = 0;
                freeBytes->hi = 0;
            }
        }
        return (result);
    }
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

    OSErr get_name(short i, std::string *res, HVolumeParam *io)
    {
        OSErr err;
        unsigned char *volName;
        short vRefNum;
        long freeBytes;

        err = GetVInfo(i, volName, &vRefNum, &freeBytes);
        if (err != 0)
        {
            return err;
        }

        HParamBlockRec sts = {
            .volumeParam = {
                .ioCompletion = NULL,
                .ioVolIndex = vRefNum,
            }};
        err = PBHGetVInfo(&sts, false);
        if (err != 0)
        {
            return err;
        }
        *io = sts.volumeParam;

        auto n = volName;
        auto len = n[0];
        auto str = std::string();
        for (int j = 1; j < len + 1; j++)
        {
            str += n[j];
        };
        *res = str;
        return 0;
    }
    OSErr get_info(short i, unsigned char *volName, float *freeBytes, float *totalBytes)
    {
        short vRefNum;
        UnsignedWide freeBytes_;
        UnsignedWide totalBytes_;
        OSErr err = XGetVInfo(i, volName, &vRefNum, &freeBytes_, &totalBytes_);
        *freeBytes = (float)freeBytes_.hi + (float)freeBytes_.lo;
        *totalBytes = (float)totalBytes_.hi + (float)totalBytes_.lo;
        return err;
    }
    std::function<void()> disk_below_91(int listNum, short i)
    {
        return [listNum, i]
        {
            HVolumeParam io;
            OSErr err;

            float freeBytes = -1.0f;
            float totalBytes = -1.0f;
            unsigned char *volName_;
            volName_ = (unsigned char *)"\0";
            short vRefNum;
            UnsignedWide freeBytes_;
            UnsignedWide totalBytes_;
            err = XGetVInfo(i, volName_, &vRefNum, &freeBytes_, &totalBytes_);
            freeBytes = (float)freeBytes_.hi + (float)freeBytes_.lo;
            totalBytes = (float)totalBytes_.hi + (float)totalBytes_.lo;

            std::string volName;
            for (int i = 1; i < volName_[0] + 1; i++)
            {
                volName += volName_[i];
            }
            if (err != 0)
            {
                printf("Error getting disk %d's size: %d", i, err);
                return;
            }
            else
            {
                printf("Disk %d: %s, ", listNum, volName.c_str());
                pprintMemory(totalBytes - freeBytes);
                printf("/");
                pprintMemory(totalBytes);
                printf(" (");
                pprintMemory(freeBytes);
                printf(" free) (ID: %d)", i);
            }
        };
    }
    std::function<void()> disk_above_91(int listNum, short i)
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
            printf("* (");
            pprintMemory(freeBlocks);
            printf(" free) (ID: %d)", i);
        };
    }
    std::function<void()> disk(int listNum, short i)
    {
        long sys = detection::gestalt(gestaltSystemVersion);
        if (sys == NULL)
        {
            return [listNum, i] {};
        }
        if (sys >= 0x910)
        {
            return disk_above_91(listNum, i);
        }
        else
        {
            return disk_below_91(listNum, i);
        }
    }

    void disk_notice()
    {
        printf("* HFS+ disks not read properly on computers running 9.1+.");
    }
}

/*

#include <functional>
#include <Disks.h>
#include <Files.h>
#include <stdio.h>
#include <string>
#include "functions.hpp"

namespace detection
{
    OSErr HGetVInfo(short volReference,
                    StringPtr volName,
                    short *vRefNum,
                    unsigned long *freeBytes,
                    unsigned long *totalBytes)
    {
        HParamBlockRec pb;
        unsigned long allocationBlockSize;
        unsigned short numAllocationBlocks;
        unsigned short numFreeBlocks;
        VCB *theVCB;
        Boolean vcbFound;
        OSErr result;


pb.volumeParam.ioVRefNum = volReference;
pb.volumeParam.ioNamePtr = volName;
pb.volumeParam.ioVolIndex = 0;
result = PBHGetVInfoSync(&pb);

if (result == noErr)
{


    *vRefNum = pb.volumeParam.ioVRefNum;
    allocationBlockSize = (unsigned long)pb.volumeParam.ioVAlBlkSiz;











    vcbFound = false;
    theVCB = (VCB *)(GetVCBQHdr()->qHead);
    while ((theVCB != NULL) && !vcbFound)
    {


        if (theVCB->vcbSigWord == 0x4244)
        {
            if (theVCB->vcbVRefNum == *vRefNum)
            {
                vcbFound = true;
            }
        }

        if (!vcbFound)
        {
            theVCB = (VCB *)(theVCB->qLink);
        }
    }

    if (theVCB != NULL)
    {


        numAllocationBlocks = (unsigned short)theVCB->vcbNmAlBlks;
        numFreeBlocks = (unsigned short)theVCB->vcbFreeBks;
    }
    else
    {


        numAllocationBlocks = (unsigned short)pb.volumeParam.ioVNmAlBlks;
        numFreeBlocks = (unsigned short)pb.volumeParam.ioVFrBlk;
    }


    *freeBytes = numFreeBlocks * allocationBlockSize;
    *totalBytes = numAllocationBlocks * allocationBlockSize;
}

return (result);
}
OSErr XGetVInfo(short volReference,
                StringPtr volName,
                short *vRefNum,
                UnsignedWide *freeBytes,
                UnsignedWide *totalBytes)
{
    OSErr result;
    long response;
    XVolumeParam pb;


    if ((Gestalt(gestaltFSAttr, &response) == noErr) && ((response & (1L << gestaltFSSupports2TBVols)) != 0))
    {

        pb.ioVRefNum = volReference;
        pb.ioNamePtr = volName;
        pb.ioXVersion = 0;
        pb.ioVolIndex = 0;
        result = PBXGetVolInfoSync(&pb);
        if (result == noErr)
        {


            *vRefNum = pb.ioVRefNum;


            *totalBytes = (UnsignedWide)pb.ioVTotalBytes;
            *freeBytes = (UnsignedWide)pb.ioVFreeBytes;
        }
    }
    else
    {



        result = HGetVInfo(volReference, volName, vRefNum, &freeBytes->lo, &totalBytes->lo);
        if (result == noErr)
        {

            totalBytes->hi = 0;
            freeBytes->hi = 0;
        }
    }
    return (result);
}
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
        long freeBytesOld;

        err = GetVInfo(i, volName, &vRefNum, &freeBytesOld);
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

        UnsignedWide freeBytes;
        UnsignedWide totalBytes;

        err = XGetVInfo(vRefNum, volName, &vRefNum, &freeBytes, &totalBytes);

        if (err != 0)
        {
            return;
        }
        float allBlocks = (float)(totalBytes.lo) + (float)(totalBytes.hi);
        float freeBlocks = (float)(freeBytes.lo) + (float)(freeBytes.hi);

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
*/