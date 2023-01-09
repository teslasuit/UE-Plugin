#include "Haptic/TsHapticAssetManager.h"
#include "ITeslasuitPlugin.h"
#include "ts_api/ts_asset_api.h"
#include "ts_api/ts_haptic_api.h"

TsHapticAssetManager::TsHapticAssetManager()
{
    UE_LOG(LogTemp, Log, TEXT("TsHapticAssetManager: constructed."));
}

TsHapticAssetManager::~TsHapticAssetManager()
{
    // Unload forgotten assets
    RemoveAllPlayables();
    UnloadAllAssets();
    UE_LOG(LogTemp, Log, TEXT("TsHapticAssetManager: deconstructed."));
}

void* TsHapticAssetManager::LoadAsset(const UTsAsset& Asset)
{
    // Check if asset already loaded
    auto It = AssetHandles.find(Asset.GetUniqueID());
    if (It != AssetHandles.end())
    {
        return It->second;
    }

    // Load asset and get handle
    auto LoadFn = reinterpret_cast<decltype(&ts_asset_load_from_binary_data)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_asset_load_from_binary_data")));
    if (LoadFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to load asset - null ts_asset_load_from_binary_data handle."));
        return nullptr;
    }
    auto Handle = static_cast<void*>(LoadFn(Asset.GetData().GetData(), Asset.GetData().Num()));
    if (Handle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to load asset - null handle returned."));
        return nullptr;
    }

    // Store and return handle
    AssetHandles[Asset.GetUniqueID()] = Handle;
    return Handle;
}

std::uint64_t TsHapticAssetManager::CreatePlayable(void* DeviceHandle, void* AssetHandle)
{
    // Create haptic playable from asset
    auto CreateFn = reinterpret_cast<decltype(&ts_haptic_create_playable_from_asset)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_haptic_create_playable_from_asset")));
    if (CreateFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to create playable asset - null ts_haptic_create_playable_from_asset handle."));
        return 0;
    }
    std::uint64_t PlayableId = 0;
    auto StatusCode = CreateFn(reinterpret_cast<TsDeviceHandle*>(DeviceHandle), reinterpret_cast<TsAsset*>(AssetHandle), false, &PlayableId);
    if (StatusCode != 0)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to create playable asset - code: %i."), StatusCode);
        return PlayableId;
    }

    // Register device and return id
    UsedDevices.insert(DeviceHandle);
    return PlayableId;
}

void TsHapticAssetManager::RemovePlayable(void* DeviceHandle, std::uint64_t PlayableId)
{
    auto RemoveFn = reinterpret_cast<decltype(&ts_haptic_remove_playable)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_haptic_remove_playable")));
    if (RemoveFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to remove playable asset - null ts_haptic_remove_playable handle."));
        return;
    }
    RemoveFn(reinterpret_cast<TsDeviceHandle*>(DeviceHandle), PlayableId);
}

void TsHapticAssetManager::RemoveAllPlayables()
{
    // Find clear function
    auto ClearFn = reinterpret_cast<decltype(&ts_haptic_clear_all_playables)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_haptic_clear_all_playables")));
    if (ClearFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to remove playable assets - null ts_haptic_clear_all_playables handle."));
        return;
    }

    // Remove all registered assets
    for (auto DeviceHandle : UsedDevices)
    {
        ClearFn(reinterpret_cast<TsDeviceHandle*>(DeviceHandle));
    }
    UsedDevices.clear();
}

void TsHapticAssetManager::UnloadAsset(const UTsAsset& Asset)
{
    // Unload asset if it is loaded
    auto It = AssetHandles.find(Asset.GetUniqueID());
    if (It != AssetHandles.end())
    {
        UnloadAsset(It->second);
        AssetHandles.erase(It);
    }
}

void TsHapticAssetManager::UnloadAsset(void* AssetHandle)
{
    // Check asset handle
    if (AssetHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to unload asset - null asset handle."));
        return;
    }

    // Unload asset
    auto UnloadFn = reinterpret_cast<decltype(&ts_asset_unload)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_asset_unload")));
    if (UnloadFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsHapticAssetManager: failed to unload asset - null ts_asset_unload handle."));
        return;
    }
    UnloadFn(reinterpret_cast<TsAsset*>(AssetHandle));
}

void TsHapticAssetManager::UnloadAllAssets()
{
    // Unload all registered assets
    for (auto& It : AssetHandles)
    {
        UnloadAsset(It.second);
    }
    AssetHandles.clear();
}

void TsHapticAssetManager::SetLibHandle(void* Handle)
{
    LibHandle = Handle;
}
