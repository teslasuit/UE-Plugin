#pragma once
#include "CoreMinimal.h"


FString GetTsLibraryDir()
{
    const FString InstallPath = std::getenv("TESLASUIT_INSTALL_DIR");
    if (InstallPath.IsEmpty())
        return FString();
    return InstallPath;
}

FString GetTsLibraryName()
{
#ifdef _WIN32
    return "teslasuit_api.dll";
#endif _WIN32

#ifdef __unix__
    // unix code for finding library
#endif// __unix__
    return FString();
}
