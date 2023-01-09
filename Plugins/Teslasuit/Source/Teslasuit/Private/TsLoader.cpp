#include "TsLoader.h"
#include "Utils/TsLibPathUtils.h"

TsLoader::TsLoader()
{
    UE_LOG(LogTemp, Log, TEXT("TsLoader: constructed"));
}

void TsLoader::Load()
{
    UE_LOG(LogTemp, Log, TEXT("TsLoader: load"));
    if (bIsLoaded)
    {
        UE_LOG(LogTemp, Log, TEXT("TsLoader: already loaded"));
        return;
    }

    FString LibDir = GetTsLibraryDir();
    FString LibPath = LibDir + "/" + GetTsLibraryName();
    UE_LOG(LogTemp, Log, TEXT("TsLoader: Lib Path: %s."), *LibPath);
    FPlatformProcess::AddDllDirectory(*LibDir);
    LibHandle = FPlatformProcess::GetDllHandle(*LibPath);
    if (LibHandle != nullptr)
    {
        bIsLoaded = true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("TsLoader: cannot load Teslasuit API DLL, try to reinstall Teslasuit Software."));

    }
}

void TsLoader::Unload()
{
    UE_LOG(LogTemp, Log, TEXT("TsLoader: unload"));
    if (!bIsLoaded)
    {
        return;
    }
    if (LibHandle != nullptr)
    {
        FPlatformProcess::FreeDllHandle(LibHandle);
    }
    bIsLoaded = false;
}

bool TsLoader::IsLoaded() const
{
    return bIsLoaded;
}

void* TsLoader::GetLibHandle() const
{
    if (!bIsLoaded)
    {
        UE_LOG(LogTemp, Warning, TEXT("TsLoader: getting lib handle while lib is not loaded."));
    }
    return LibHandle;
}

TsLoader::~TsLoader()
{
    if (IsLoaded())
    {
        Unload();
    }
}
