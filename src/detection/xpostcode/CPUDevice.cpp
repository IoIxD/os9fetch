#include "CPUDevice.h"

#include <NameRegistry.h>
#include <MacMemory.h>
#include <string.h>

CPUDeviceList CPUDevice::gCPUDeviceList;
bool CPUDevice::gHasBeenInitialized = false;
int CPUDevice::gCPUCount = 0;

void ThrowIfNULL_AC(void *what, char *hit)
{
	if (what == NULL)
	{
		printf("%s was null!\n", hit);
		getchar();
		exit(1);
		return;
	}
};
void ThrowIfOSErr_AC(OSErr what)
{
	if (what != 0)
	{
		printf("Error: %d\n", what);
		getchar();
		exit(1);
		return;
	}
};
void CPUDevice::Initialize()
{
	if (gHasBeenInitialized)
		return;

	gHasBeenInitialized = true;

	// We iterate through, and collected all entries with a device type "cpu"

	RegEntryIter cookie;
	RegEntryID entry;
	Boolean done = false;
	RegEntryIterationOp iterOp = kRegIterDescendants;
	OSStatus err = RegistryEntryIterateCreate(&cookie);

	while (true)
	{
		err = RegistryEntryIterate(&cookie, iterOp, &entry, &done);
		if (!done && (err == noErr))
		{
			RegPropertyValueSize propSize;
			err = RegistryPropertyGetSize(&entry, kDeviceTypeProperty, &propSize);
			if (err == noErr)
			{
				char *deviceType = NewPtr(propSize + 1);
				ThrowIfNULL_AC(deviceType, "deviceType");
				ThrowIfOSErr_AC(RegistryPropertyGet(&entry, kDeviceTypeProperty, deviceType, &propSize));
				deviceType[propSize] = '\0';
				if (!strcmp(deviceType, "cpu"))
				{
					gCPUDeviceList.push_back(entry);
				}
				DisposePtr(deviceType);
			}
			RegistryEntryIDDispose(&entry);
		}
		else
		{
			break;
		}
		iterOp = kRegIterContinue;
	}
	RegistryEntryIterateDispose(&cookie);
}

CPUDevice::~CPUDevice()
{
#ifdef __MACH__
#else
	RegistryEntryIDDispose(fRegEntryID);
#endif
}

#define kCPUIDPropName "cpu#"
#define kCPUVersionPropName "cpu-version"

CPUDevice::CPUDevice(REG_ENTRY_TYPE regEntry)
{

	ThrowIfNULL_AC(regEntry, "regEntry");
	RegistryEntryIDCopy(regEntry, &fRegEntryIDStorage);
	fRegEntryID = &fRegEntryIDStorage;

	// OFAliases::AliasFor(fRegEntryID, fOpenFirmwareName, fShortOpenFirmwareName);

	RegPropertyValueSize propSize;

	OSErr err;

	fCPUNumber = 0;
	err = RegistryPropertyGetSize(fRegEntryID, kCPUIDPropName, &propSize);
	if ((err == noErr) && (propSize == sizeof(fCPUNumber)))
	{
		ThrowIfOSErr_AC(RegistryPropertyGet(regEntry, kCPUIDPropName, &fCPUNumber, &propSize));
	}

	fCPUVersion = 0;
	err = RegistryPropertyGetSize(fRegEntryID, kCPUVersionPropName, &propSize);
	if ((err == noErr) && (propSize == sizeof(fCPUVersion)))
	{
		ThrowIfOSErr_AC(RegistryPropertyGet(fRegEntryID, kCPUVersionPropName, &fCPUVersion, &propSize));
	}

#if qLogging
	gLogFile << "CPU#: " << fCPUNumber << endl_AC;
	gLogFile << "OpenFirmwareName: " << fOpenFirmwareName << endl_AC;
	gLogFile << "ShortOpenFirmwareName: " << fShortOpenFirmwareName << endl_AC;
	gLogFile << "CPUVersion: " << fCPUVersion << endl_AC;
#endif
}

std::vector<RegEntryID> CPUDevice::GetCPUS()
{
	return gCPUDeviceList;
}
