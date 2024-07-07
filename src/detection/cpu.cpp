
#include <string>
#include <OSUtils.h>
#include <ToolUtils.h>
#include "functions.hpp"

#include "xpostcode/CPUDevice.h"
#include <NameRegistry.h>
#include <cstring>

#include "xpostcode/CPUDevice.h"

namespace detection
{

#ifdef FOR_68K
    void cpu_68k();
    void cpu()
    {
        cpu_68k();
    }
#endif
#ifdef FOR_PPC
    void cpu_ppc();
    void cpu()
    {
        cpu_ppc();
    }
#endif
    void clockSpeed();

    void cpu_68k()
    {
        int ver = os_version();

        long procType;
        if (ver >= 0x605)
        {
            procType = detection::gestalt(gestaltProcessorType);
        }
        else
        {
            SysEnvRec rec;
            SysEnvirons(1, &rec);
            procType = rec.processor;
        }
        if (procType != NULL)
        {
            switch (procType)
            {
            case gestalt68000:
                printf("CPU: 68000");
                break;
            case gestalt68010:
                printf("CPU: 68010");
                break;
            case gestalt68020:
                printf("CPU: 68020");
                break;
            case gestalt68030:
                printf("CPU: 68030");
                break;
            case gestalt68040:
                printf("CPU: 68040");
                break;
            }

#ifdef FOR_PPC
            int ver = os_version();
            if (ver >= 0x605)
            {
                clockSpeed();
            }
#endif
            printf(" (ID: %d)", procType);
        }
    }

    void cpu_ppc()
    {
        CPUDevice::Initialize();
        auto vec = CPUDevice::GetCPUS();
        for (int i = 0; i < vec.size(); i++)
        {
            UInt32 propSize;
            auto entry = vec.at(i);

            int cpuNumber = 0;
            auto err = RegistryPropertyGetSize(&entry, kCPUIDPropName, &propSize);
            if ((err == noErr) && (propSize == sizeof(cpuNumber)))
            {
                ThrowIfOSErr_AC(RegistryPropertyGet(&entry, kCPUIDPropName, &cpuNumber, &propSize));
            }

            uint processorVersion = 0;
            err = RegistryPropertyGetSize(&entry, kCPUVersionPropName, &propSize);
            if ((err == noErr) && (propSize == sizeof(processorVersion)))
            {
                ThrowIfOSErr_AC(RegistryPropertyGet(&entry, kCPUVersionPropName, &processorVersion, &propSize));
            }
            std::string name;

            switch (processorVersion)
            {
            case 0x00010001:
                name = "PowerPC 601 Rev. 0.1";
                break;
            case 0x00010002:
                name = "PowerPC 601 Rev. 0.1";
                break;
            case 0x00030001:
                name = "PowerPC 603 Rev. 0.1";
                break;
            case 0x00060101:
                name = "PowerPC 603e Rev. 1.1";
                break;
            case 0x00060102:
                name = "PowerPC 603e Rev. 1.2";
                break;
            case 0x00060103:
                name = "PowerPC 603e Rev. 1.3";
                break;
            case 0x00060104:
                name = "PowerPC 603e Rev. 1.4";
                break;
            case 0x00060202:
                name = "PowerPC 603e Rev. 2.2";
                break;
            case 0x00060300:
                name = "PowerPC 603e Rev. 3.0";
                break;
            case 0x00060400:
                name = "PowerPC 603e Rev. 4.0";
                break;
            case 0x00060401:
                name = "PowerPC 603e Rev. 4.1";
                break;
            case 0x00070101:
                name = "PowerPC 603ev Rev. 1.1";
                break;
            case 0x00071201:
                name = "PowerPC 603r Rev. 2.1";
                break;
            case 0x00040103:
                name = "PowerPC 604 Rev. 1.3";
                break;
            case 0x00090204:
                name = "PowerPC 604e Rev. 2.4";
                break;
            case 0x00080100:
                name = "PowerPC G3 740/750 Rev. 1.0";
                break;
            case 0x00080200:
                name = "PowerPC G3 740/750 Rev. 2.0";
                break;
            case 0x00080300:
                name = "PowerPC G3 740/750 Rev. 3.0";
                break;
            case 0x00080301:
                name = "PowerPC G3 740/750 Rev. 3.1";
                break;
            case 0x00082202:
                name = "PowerPC G3 750CX Rev. 2.2";
                break;
            case 0x00082214:
                name = "PowerPC G3 750CXe Rev. 2.4";
                break;
            case 0x00082311:
                name = "PowerPC G3 750CXe Rev. 3.1";
                break;
            case 0x70000100:
            case 0x70000101:
            case 0x70000102:
            case 0x70000103:
            case 0x70000104:
            case 0x70000105:
            case 0x70000106:
            case 0x70000107:
            case 0x70000108:
            case 0x70000109:
            case 0x7000010A:
            case 0x7000010B:
            case 0x7000010C:
            case 0x7000010D:
            case 0x7000010E:
            case 0x7000010F:
                name = "PowerPC G3 750FX Rev. 1.x";
                break;
            case 0x70000200:
                name = "PowerPC G3 750FX Rev. 2.0";
                break;
            case 0x70000201:
                name = "PowerPC G3 750FX Rev. 2.1";
                break;
            case 0x70000202:
                name = "PowerPC G3 750FX Rev. 2.2";
                break;
            case 0x70000203:
                name = "PowerPC G3 750FX Rev. 2.3";
                break;
            case 0x00080202:
                name = "PowerPC G3 740(P)/750(P) Rev. 1.1/1.2/2.1";
                break;
            case 0x00083100:
                name = "PowerPC G3 745/755 Rev. 1.0";
                break;
            case 0x00083101:
                name = "PowerPC G3 745/755 Rev. 1.1";
                break;
            case 0x00083200:
                name = "PowerPC G3 745/755 Rev. 2.0";
                break;
            case 0x00083201:
                name = "PowerPC G3 745/755 Rev. 2.1";
                break;
            case 0x00083202:
                name = "PowerPC G3 745/755 Rev. 2.2";
                break;
            case 0x00083203:
                name = "PowerPC G3 745/755 Rev. 2.3";
                break;
            case 0x00083204:
                name = "PowerPC G3 745/755 Rev. 2.4";
                break;
            case 0x00083205:
                name = "PowerPC G3 745/755 Rev. 2.5";
                break;
            case 0x00083206:
                name = "PowerPC G3 745/755 Rev. 2.6";
                break;
            case 0x00083207:
                name = "PowerPC G3 745/755 Rev. 2.7";
                break;
            case 0x00083208:
                name = "PowerPC G3 745/755 Rev. 2.8";
                break;
            case 0x000c0101:
                name = "PowerPC G4 7400 Rev. 1.1";
                break;
            case 0x000c0200:
                name = "PowerPC G4 7400 Rev. 2.0";
                break;
            case 0x000c0202:
                name = "PowerPC G4 7400 Rev. 2.2";
                break;
            case 0x000c0206:
                name = "PowerPC G4 7400 Rev. 2.6";
                break;
            case 0x000c0207:
                name = "PowerPC G4 7400 Rev. 2.7";
                break;
            case 0x000c0209:
                name = "PowerPC G4 7400 Rev. 2.8";
                break;
            case 0x000c0208:
                name = "PowerPC G4 7400 Rev. 2.9";
                break;
            case 0x800c1101:
                name = "PowerPC G4 7410 Rev. 1.1";
                break;
            case 0x800c1102:
                name = "PowerPC G4 7410 Rev. 1.2";
                break;
            case 0x800c1103:
                name = "PowerPC G4 7410 Rev. 1.3";
                break;
            case 0x800c1104:
                name = "PowerPC G4 7410 Rev. 1.4";
                break;
            case 0x80000100:
                name = "PowerPC G4 7450 Rev. 1.0";
                break;
            case 0x80000101:
                name = "PowerPC G4 7450 Rev. 1.1";
                break;
            case 0x80000102:
                name = "PowerPC G4 7450 Rev. 1.2";
                break;
            case 0x80000200:
                name = "PowerPC G4 7450 Rev. 2.0";
                break;
            case 0x80000201:
                name = "PowerPC G4 7441/7450 Rev. 2.1";
                break;
            case 0x80000203:
                name = "PowerPC G4 7441/7451 Rev. 2.3";
                break;
            case 0x80000202:
                name = "PowerPC G4 7441 Rev. 2.2";
                break;
            case 0x80010201:
                name = "PowerPC G4 7445/7455 Rev. 2.1";
                break;
            case 0x80010302:
                name = "PowerPC G4 7445/7455 Rev. 3.2";
                break;
            case 0x80010303:
                name = "PowerPC G4 7445/7455 Rev. 3.3";
                break;
            case 0x80010304:
                name = "PowerPC G4 7445/7455 Rev. 3.4";
                break;
            case 0x80020100:
                name = "PowerPC G4 7447/7457 Rev. 1.0";
                break;
            case 0x80020101:
                name = "PowerPC G4 7447/7457 Rev. 1.1";
                break;
            case 0x80020102:
                name = "PowerPC G4 7447/7457 Rev. 1.2";
                break;
            case 0x00390202:
                name = "PowerPC G5 970 Rev. 2.2";
                break;
            case 0x003c0300:
                name = "PowerPC G5	970FX Rev. 3.0";
                break;
            case 0x00200000:
                name = "PowerPC 403GA";
                break;
            case 0x00200100:
                name = "PowerPC 403GB";
                break;
            case 0x00200200:
                name = "PowerPC 403GC";
                break;
            case 0x00201400:
                name = "PowerPC 403GCX";
                break;
            case 0x40110000:
                name = "PowerPC 405GP";
                break;
            case 0x40110040:
                name = "PowerPC 405GP Rev. B";
                break;
            case 0x40110082:
                name = "PowerPC 405GP Rev. C";
                break;
            case 0x401100C4:
                name = "PowerPC 405GP Rev. D";
                break;
            case 0x40110145:
                name = "PowerPC 405GP Rev. E or 405CR Rev. C";
                break;
            case 0x40110041:
                name = "PowerPC 405CR Rev. A";
                break;
            case 0x401100C5:
                name = "PowerPC 405CR Rev. B";
                break;
            case 0x51210950:
                name = "PowerPC 405EP Rev. A or Rev. B";
                break;
            case 0x50910951:
                name = "PowerPC 405GPR Rev. B";
                break;
            case 0x41511460:
                name = "PowerPC 405EZ Rev. A";
                break;
            case 0x12911471:
                name = "PowerPC 405EXR2 Rev. A";
                break;
            case 0x12911477:
                name = "PowerPC 405EX1 Rev. A";
                break;
            case 0x1291147B:
                name = "PowerPC 405EXR1 Rev. C";
                break;
            case 0x12911479:
                name = "PowerPC 405EXR2 Rev. C";
                break;
            case 0x1291147F:
                name = "PowerPC 405EX1 Rev. C";
                break;
            case 0x1291147D:
                name = "PowerPC 405EX2 Rev. C";
                break;
            case 0x12911472:
                name = "PowerPC 405EXR1 Rev. D";
                break;
            case 0x12911470:
                name = "PowerPC 405EXR2 Rev. D";
                break;
            case 0x12911475:
                name = "PowerPC 405EX1 Rev. D";
                break;
            case 0x12911473:
                name = "PowerPC 405EX2 Rev. D";
                break;
            case 0x40120440:
                name = "PowerPC 440GP Rev. B";
                break;
            case 0x40120481:
                name = "PowerPC 440GP Rev. C";
                break;
            case 0x42221850:
                name = "PowerPC 440EP Rev. A";
                break;
            case 0x422218D3:
                name = "PowerPC 440EP Rev. B or 440GR Rev. A";
                break;
            case 0x422218D4:
                name = "PowerPC 440EP Rev. C or 440GR Rev. B";
                break;
            case 0x216218D0:
                name = "PowerPC 440EPX1 Rev. A or 440GRX1 Rev. A";
                break;
            case 0x216218D4:
                name = "PowerPC 440EPX2 Rev. A or 440GRX2 Rev. A";
                break;
            case 0x51B21850:
                name = "PowerPC 440GX Rev. A";
                break;
            case 0x51B21851:
                name = "PowerPC 440GX Rev. B";
                break;
            case 0x51B21892:
                name = "PowerPC 440GX Rev. C";
                break;
            case 0x51B21894:
                name = "PowerPC 440GX Rev. F";
                break;
            case 0x53221850:
                name = "PowerPC 440SP_6 Rev. AB";
                break;
            case 0x53321850:
                name = "PowerPC 440SP Rev. AB";
                break;
            case 0x53221891:
                name = "PowerPC 440SP_6 Rev. C";
                break;
            case 0x53321891:
                name = "PowerPC 440SP Rev. C";
                break;
            case 0x53421890:
                name = "PowerPC 440SPe_6 Rev. A";
                break;
            case 0x53521890:
                name = "PowerPC 440SPe Rev. A";
                break;
            case 0x53421891:
                name = "PowerPC 440SPe_6 Rev. B";
                break;
            case 0x53521891:
                name = "PowerPC 440SPe Rev. B";
                break;
            case 0x130218A2:
                name = "PowerPC 460EX_SE Rev. A";
                break;
            case 0x130218A3:
                name = "PowerPC 460EX Rev. A";
                break;
            case 0x130218A4:
                name = "PowerPC 460EX Rev. B";
                break;
            case 0x130218A0:
                name = "PowerPC 460GT_SE Rev. A";
                break;
            case 0x130218A1:
                name = "PowerPC 460GT Rev. A";
                break;
            case 0x130218A5:
                name = "PowerPC 460GT Rev. B";
                break;
            case 0x13541800:
                name = "PowerPC 460SX Rev. A";
                break;
            case 0x13541801:
                name = "PowerPC 460SX Rev. A_V1";
                break;
            case 0x13541802:
                name = "PowerPC 460GX Rev. A";
                break;
            case 0x13541803:
                name = "PowerPC 460GX Rev. A_V1";
                break;
            case 0x12C41C80:
                name = "PowerPC APM821XX Rev. A";
                break;
            case 0x00010000:
                name = "PowerPC 601";
                break;
            case 0x00050000:
                name = "PowerPC 602";
                break;
            case 0x00030000:
                name = "PowerPC 603";
                break;
            case 0x00060000:
                name = "PowerPC 603e";
                break;
            case 0x00070000:
                name = "PowerPC 603ev";
                break;
            case 0x00071000:
                name = "PowerPC 603r";
                break;
            case 0x00040000:
                name = "PowerPC 604";
                break;
            case 0x00090000:
                name = "PowerPC 604e";
                break;
            case 0x000A0000:
                name = "PowerPC 604r";
                break;
            case 0x00140000:
                name = "PowerPC 620";
                break;
            case 0x00080000:
                name = "PowerPC 740/750";
                break;
            case 0x10080000:
                name = "PowerPC 740P/750P";
                break;
            case 0x000C0000:
                name = "PowerPC 7400";
                break;
            case 0x800C0000:
                name = "PowerPC 7410";
                break;
            case 0x80000000:
                name = "PowerPC 7450";
                break;
            case 0x80200000:
                name = "PowerPC 85xx";
                break;
            case 0x80210000:
                name = "PowerPC 85xx Rev. 1.0";
                break;
            case 0x80220000:
                name = "PowerPC 85xx Rev. 1.0";
                break;
            case 0x80040000:
                name = "PowerPC 86xx";
                break;
            case 0x7ff21912:
                name = "PowerPC VIRTEX5";
                break;
            case 0x00500000:
                name = "PowerPC 821/832/850/860";
                break;
            case 0x00810100:
                name = "PowerPC 8240/8240/8260";
                break;
            case 0x00810101:
                name = "PowerPC 8260_HIP3";
                break;
            case 0x80811014:
                name = "PowerPC 8260_HIP4";
                break;
            case 0x80822011:
                name = "PowerPC 5200/8260_HIP7";
                break;
            case 0x80822013:
                name = "PowerPC 8260_HIP7R1";
                break;
            case 0x80822014:
                name = "PowerPC 5200B/8260_HIP7RA";
                break;

            default:
                name = "Unknown";
                break;
            }

            printf("CPU: %s", name.c_str());

            clockSpeed();

            printf(" (ID: %0X)", processorVersion);
        }
    }

    void clockSpeed()
    {
        float speed = (float)detection::gestalt(gestaltProcClkSpeed);
        if (speed != NULL)
        {
            if (speed < 1024.0)
            {
                printf(" %0.2fHz", speed);
            }
            else if (speed < 1048576.0)
            {
                printf(" %0.2fKHz", speed / 1024.0);
            }
            else if (speed < 1073741824.0)
            {
                printf(" %0.2fMHz", speed / 1048576.0);
            }
            else if (speed < 1099511627776.0)
            {
                printf(" %0.2fGHz", speed / 1073741824.0);
            }
            else if (speed < 1125899906842624.0)
            {
                printf(" %0.2fTHz", speed / 1099511627776.0);
            }
            else
            {
                printf(" %0.2fPHz", speed / 1125899906842624.0);
            }
            printf(" (%0.2f)", speed);
        }
    }
    void model()
    {
        int ver = os_version();

        long sys;
        if (ver >= 0x605)
        {
            sys = detection::gestalt(gestaltMachineType);
        }
        else
        {
            SysEnvRec rec;
            SysEnvirons(1, &rec);
            sys = rec.machineType;
            // The result we get near perfectly maps to the modern one, with some exceptions.
            if (sys == 1)
            {
                sys = -1;
            }
            else if (sys == 2)
            {
                sys = 2;
            }
            else
            {
                sys -= 2;
            }
        }
        if (sys != NULL)
        {
            // We're supposed to be able to use GetIndString. This does not work, presumably because they stopped updating the index, but they did give us all the numbers in the last header file.
            const char *name = NULL;
            unsigned char *name2 = NULL;
            switch (sys)
            {
            case 0:
                name = "Macintosh 128k";
                break;
            case 1:
                name = "Macintosh Classic";
                break;
            case 2:
                name = "Macintosh XL";
                break;
            case 3:
                name = "Macintosh 512K";
                break;

            case 4:
                name = "Macintosh Plus";
                break;
            case 5:
                name = "Macintosh SE";
                break;
            case 6:
                name = "Macintosh II";
                break;
            case 7:
                name = "Macintosh IIx";
                break;

            case 8:
                name = "Macintosh IIcx";
                break;
            case 9:
                name = "Macintosh SE030";
                break;
            case 10:
                name = "Macintosh Portable";
                break;
            case 11:
                name = "Macintosh IIci";
                break;

            case 12:
                name = "Power Macintosh 8100/120";
                break;
            case 13:
                name = "Macintosh IIfx";
                break;
            case 17:
                name = "Macintosh Classic";
                break;
            case 18:
                name = "Macintosh IIsi";
                break;

            case 19:
                name = "Macintosh LC";
                break;
            case 20:
                name = "Macintosh Quadra 900";
                break;
            case 21:
                name = "PowerBook  170";
                break;
            case 22:
                name = "Macintosh Quadra 700";
                break;

            case 23:
                name = "Classic II";
                break;
            case 24:
                name = "PowerBook  100";
                break;
            case 25:
                name = "PowerBook  140";
                break;
            case 26:
                name = "Macintosh Quadra950";
                break;

            case 27:
                name = "Macintosh LCIII or Performa 450";
                break;

            case 29:
                name = "PowerBook Duo 210";
                break;
            case 30:
                name = "Macintosh Centris650";
                break;

            case 32:
                name = "PowerBook Duo 230";
                break;
            case 33:
                name = "PowerBook 180";
                break;
            case 34:
                name = "PowerBook 160";
                break;
            case 35:
                name = "Macintosh Quadra800";
                break;

            case 36:
                name = "Macintosh Quadra650";
                break;
            case 37:
                name = "Macintosh LCII";
                break;
            case 38:
                name = "PowerBook Duo 250";
                break;
            case 39:
                name = "Apple Macintosh WGS 9150/80";
                break;

            case 40:
                name = "Power Macintosh 8100/110 or Apple Macintosh WGS 8110";
                break;
            case 41:
                name = "Power Macintosh 52x0 or 5300";
                break;
            case 42:
                name = "Power Macintosh 6200 or Performa 6300";
                break;
            case 44:
                name = "Macintosh IIvi";
                break;
            case 45:
                name = "Macintosh IIvm or Performa 600";
                break;
            case 47:
                name = "Power Macintosh 7100/80";
                break;
            case 48:
                name = "Macintosh IIvx";
                break;

            case 49:
                name = "Macintosh Color Classic or Performa 250";
                break;
            case 50:
                name = "PowerBook 165c";
                break;
            case 52:
                name = "Macintosh Centris610";
                break;

            case 53:
                name = "Macintosh Quadra610";
                break;
            case 54:
                name = "PowerBook 145";
                break;
            case 55:
                name = "Power Macintosh 8100/100";
                break;
            case 56:
                name = "Macintosh LC520";
                break;

            case 57:
                name = "Apple Macintosh WGS 9150/120";
                break;
            case 58:
                name = "Power Macintosh 6400 or Performa 6400 or Performa 6360";
                break;

            case 60:
                name = "Macintosh Centris660AV or Quadra660AV";
                break;
            case 62:
                name = "Performa 46x";
                break;
            case 65:
                name = "Power Macintosh 8100/80 or Apple Macintosh WGS 8150/80";
                break;
            case 67:
                name = "Power Macintosh 9x00";
                break;
            case 68:
                name = "Power Macintosh 7x00 or Apple Macintosh WGS 8550";
                break;
            case 69:
                name = "Power Macintosh 8x00";
                break;
            case 71:
                name = "PowerBook 180c";
                break;
            case 72:
                name = "PowerBook 520 or 520c or 540 or 540c";
                break;
            case 74:
                name = "Power Macintosh 5400";
                break;
            case 75:
                name = "Power Macintosh 6100/60 or Apple Macintosh WGS 6150/60";
                break;
            case 77:
                name = "PowerBook Duo 270c";
                break;
            case 78:
                name = "Macintosh Quadra840AV";
                break;
            case 80:
                name = "Performa 550";
                break;
            case 84:
                name = "PowerBook 165";
                break;

            case 85:
                name = "PowerBook 190";
                break;
            case 88:
                name = "Macintosh TV";
                break;
            case 89:
                name = "Macintosh LC475 or Performa 47x";
                break;

            case 92:
                name = "Macintosh LC575";
                break;
            case 94:
                name = "Macintosh Quadra605";
                break;
            case 98:
                name = "Macintosh Quadra630";
                break;
            case 99:
                name = "Macintosh LC580 or Performa 580";
                break;
            case 100:
                name = "Power Macintosh 6100/66 or Apple Macintosh WGS 6150/66";
                break;
            case 102:
                name = "PowerBook Duo 280";
                break;
            case 103:
                name = "PowerBook Duo 280c";
                break;
            case 104:
                name = "Power Macintosh LC475 or Power Macintosh Performa 47x";
                break;
            case 105:
                name = "Power Macintosh LC575 or Power Macintosh Performa 57x";
                break;
            case 106:
                name = "Power Macintosh Quadra 630 or Power Macintosh LC630 or Performa 63x";
                break;
            case 108:
                name = "Power Macintosh 7200";
                break;
            case 109:
                name = "Power Macintosh 7300";
                break;
            case 112:
                name = "Power Macintosh 7100/66";
                break;
            case 115:
                name = "PowerBook 150";
                break;
            case 116:
                name = "Power Macintosh Quadra 700";
                break;
            case 117:
                name = "Power Macintosh Quadra 900";
                break;
            case 118:
                name = "Power Macintosh Quadra 950";
                break;
            case 119:
                name = "Power Macintosh Centris 610";
                break;

            case 120:
                name = "Power Macintosh Centris 650";
                break;
            case 121:
                name = "Power Macintosh Quadra 610";
                break;
            case 122:
                name = "Power Macintosh Quadra 650";
                break;
            case 123:
                name = "Power Macintosh Quadra 800";
                break;

            case 124:
                name = "PowerBook Duo 2300";
                break;
            case 126:
                name = "PowerBook 500 PPC Upgrade";
                break;
            case 128:
                name = "PowerBook 5300";
                break;
            case 310:
                name = "PowerBook 1400";
                break;
            case 306:
                name = "PowerBook 3400";
                break;
            case 307:
                name = "PowerBook 2400";
                break;
            case 312:
                name = "PowerBook G3 Series";
                break;
            case 313:
                name = "PowerBook G3";
                break;
            case 314:
                name = "PowerBook G3 Series 2";
                break;
            case 406:
                name = "New World";
                break;
            case 510:
                name = "Power Macintosh G3";
                break;
            case 512:
                name = "Power Macintosh 5500 or Macintosh 20th Anniversary";
                break;
            case 513:
                name = "Power Macintosh 6500";
                break;
            case 514:
                name = "Power Macintosh 4400/160";
                break;
            case 515:
                name = "Power Macintosh 4400";
                break;
            default:
                GetIndString(name2, -16395, sys);
                break;
            }
            if (name != NULL)
            {
                printf("Model: %s (ID: %0.2f)", name, sys);
            }
            else
            {
                printf("Model: %s (ID: %0.2f)", name2, sys);
            }
        }
        return;
    }
}
