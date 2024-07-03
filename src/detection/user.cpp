#include "functions.hpp"
#include <AppleScript.h>
#include <Files.h>

namespace detection
{
    int driveAmount = -1;
    bool name_avaliable()
    {
        HParamBlockRec pb = HParamBlockRec{
            .objParam = ObjParam{
                .ioCompletion = NULL,
                .ioVRefNum = 0,
            }};
        OSErr err = PBHGetLogInInfo(&pb, false);
        if (err != 0)
        {
            return false;
        };

        // We might get a false positive, indicitive by the resulting string not being valid name. Double check to make sure it's valid.
        auto n = pb.objParam.ioNamePtr;
        auto len = n[0];
        auto str = std::string();
        for (int i = 1; i < len + 1; i++)
        {
            str += n[i];
        };
        return is_utf8(str.c_str());
    }

    std::string name_str()
    {
        std::string name;
        HParamBlockRec pb = HParamBlockRec{
            .objParam = ObjParam{
                .ioCompletion = NULL,
                .ioVRefNum = 0,
            }};
        OSErr err = PBHGetLogInInfo(&pb, false);
        if (err == 0)
        {
            auto n = pb.objParam.ioNamePtr;
            auto len = n[0];
            auto str = std::string();
            for (int i = 1; i < len + 1; i++)
            {
                name += n[i];
            };
        }

        auto obj = HParamBlockRec{
            .objParam = ObjParam{
                .ioCompletion = NULL,
                .ioNamePtr = pb.objParam.ioNamePtr,
                .ioVRefNum = pb.objParam.ioVRefNum,
                .ioObjNamePtr = pb.objParam.ioObjNamePtr,
                .ioObjID = pb.objParam.ioObjID,
            }};
        obj.objParam.ioObjType = 4;
        err = PBHMapName(&obj, false);
        if (err == 0)
        {
            name += "@";
            auto n = obj.objParam.ioObjNamePtr;
            auto len = n[0];
            auto str = std::string();
            for (int i = 1; i < len + 1; i++)
            {
                name += n[i];
            };
        }
        return name;
    }
    void line()
    {
        auto n = name_str();
        for (int i = 0; i < n.length(); i++)
        {
            printf("-");
        }
    }
    void name()
    {
        printf("%s", name_str().c_str());
    }
}