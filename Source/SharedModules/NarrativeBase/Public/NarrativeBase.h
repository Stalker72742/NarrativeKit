#pragma once

#include "Modules/ModuleManager.h"

class FNarrativeBaseModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
