#include "functions.hpp"
#include <AppleScript.h>
namespace detection
{
    void name()
    {
        auto gScriptingComponent = OpenDefaultComponent(kOSAComponentType,
                                                        kOSAGenericScriptingComponentSubtype);

        auto err = ASInit(gScriptingComponent, kOSAModeNull, kASDefaultMinStackSize, kASDefaultPreferredStackSize, kASDefaultMaxStackSize, kASDefaultMinHeapSize, kASDefaultPreferredHeapSize, kASDefaultMaxHeapSize);
    }
}