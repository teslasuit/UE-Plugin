#include "TsCore.h"
#include "ts_api/ts_core_api.h"

TsCore::TsCore()
{
    UE_LOG(LogTemp, Log, TEXT("TsCore: constructed."));
}

void TsCore::Initialize()
{
    Loader.Load();

    auto InitializeFn = reinterpret_cast<decltype(&ts_initialize)>(FPlatformProcess::GetDllExport(Loader.GetLibHandle(), *FString("ts_initialize")));
    if (InitializeFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsCore: can't initialize - null ts_initialize handle."));
        return;
    }
    InitializeFn();
    UE_LOG(LogTemp, Log, TEXT("TsCore: initialized."));
}

void* TsCore::GetLibHandle() const
{
    return Loader.GetLibHandle();
}

void TsCore::Uninitialize()
{
    if (!Loader.IsLoaded())
        return;

    auto UninitializeFn = reinterpret_cast<decltype(&ts_uninitialize)>(FPlatformProcess::GetDllExport(Loader.GetLibHandle(), *FString("ts_uninitialize")));
    if (UninitializeFn != nullptr)
    {
        UninitializeFn();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TsCore: can't uninitialize - null ts_uninitialize handle."));
    }

    Loader.Unload();
    UE_LOG(LogTemp, Log, TEXT("TsCore: uninitialized."));
}

TsCore::~TsCore()
{
    UE_LOG(LogTemp, Log, TEXT("TsCore: deconstructed."));
}
