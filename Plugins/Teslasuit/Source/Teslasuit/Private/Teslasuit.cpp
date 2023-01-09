#include "Teslasuit.h"

#define LOCTEXT_NAMESPACE "FTeslasuitModule"

void FTeslasuitModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("FTeslasuitModule: startup module"));

    Core = std::make_unique<TsCore>();
    DeviceProvider = std::make_unique<TsDeviceProvider>();
    HapticAssetManager = std::make_unique<TsHapticAssetManager>();

    Core->Initialize();
    DeviceProvider->SetLibHandle(GetLibHandle());
    HapticAssetManager->SetLibHandle(GetLibHandle());
    DeviceProvider->Start();
}

void FTeslasuitModule::ShutdownModule()
{
    HapticAssetManager.reset();

    DeviceProvider->Stop();
    DeviceProvider.reset();

    Core->Uninitialize();
    Core.reset();
}

void* FTeslasuitModule::GetLibHandle() const
{
    return Core->GetLibHandle();
}

TsDeviceProvider& FTeslasuitModule::GetDeviceProvider()
{
    return *DeviceProvider;
}

TsHapticAssetManager& FTeslasuitModule::GetHapticAssetManager()
{
    return *HapticAssetManager;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTeslasuitModule, Teslasuit)
