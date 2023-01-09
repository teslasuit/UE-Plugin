#pragma once
#include "Modules/ModuleManager.h"
class ITeslasuitEditor : public IModuleInterface
{
public:
    static inline ITeslasuitEditor& Get()
    {
        return FModuleManager::LoadModuleChecked< ITeslasuitEditor >("TeslasuitEditor");
    }

    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("TeslasuitEditor");
    }
};