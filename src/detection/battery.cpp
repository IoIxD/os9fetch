#include <Power.h>
#include <string>

namespace detection
{
    int battery_count()
    {
        return BatteryCount();
    }

    bool has_battery()
    {
        return detection::battery_count() >= 1;
    }
    void battery()
    {

        short count = (short)detection::battery_count();

        for (short i = 0; i < count - 1; i++)
        {
            BatteryInfo info;
            GetScaledBatteryInfo(i, &info);
            BatteryTimeRec time;
            GetBatteryTimes(i, &time);
            printf("Battery");
            if (count - 1 >= 2)
            {
                printf(" %d", i);
            }
            printf(": %f%%", ((float)info.batteryLevel / 255.0f) * 100.0);
            if (count - 1 >= 2)
            {
                printf(", ", i);
            }
            if (info.flags & batteryCharging == batteryCharging)
            {
                printf(" (Charging)");
            }
            if (info.flags & batteryDeadBit == batteryDeadBit)
            {
                printf(" (Dead)");
            }
        }
    }
}