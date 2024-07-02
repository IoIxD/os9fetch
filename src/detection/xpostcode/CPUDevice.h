/*

CPUDevice
=========

The function of this class is to maintain a list of all the name registry
entries that are CPUs.

*/

#ifndef __CPUDEVICE_H__
#define __CPUDEVICE_H__

#include <vector>
#include <iterator>
#include <NameRegistry.h>

#define kCPUIDPropName "cpu#"
#define kCPUVersionPropName "cpu-version"
#define kDeviceTypeProperty "device_type"

typedef RegEntryID *REG_ENTRY_TYPE;
class CPUDevice;

typedef std::vector<RegEntryID> CPUDeviceList;

void ThrowIfNULL_AC(void *what, char *hit);
void ThrowIfOSErr_AC(OSErr what);
class CPUDevice
{

public:
	static void Initialize();

	static std::vector<RegEntryID> GetCPUS();

	static int getCPUCount() { return gCPUCount; }

	~CPUDevice();

	RegEntryID fRegEntryIDStorage;
	REG_ENTRY_TYPE fRegEntryID;
	char fOpenFirmwareName[256];
	char fShortOpenFirmwareName[256];
	UInt32 fCPUNumber;
	UInt32 fCPUVersion;

	CPUDevice(REG_ENTRY_TYPE regEntry);

private:
	static CPUDeviceList gCPUDeviceList;
	static int gCPUCount;
	static bool gHasBeenInitialized;
};

#endif
