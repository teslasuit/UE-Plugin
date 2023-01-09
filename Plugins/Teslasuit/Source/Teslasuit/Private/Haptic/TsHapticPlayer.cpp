#include "Haptic/TsHapticPlayer.h"
#include "ITeslasuitPlugin.h"
#include "Haptic/TsHapticAssetManager.h"
#include "ts_api/ts_haptic_api.h"

UTsHapticPlayer::UTsHapticPlayer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTsHapticPlayer::BeginPlay()
{
	Super::BeginPlay();

    LibHandle = ITeslasuitPlugin::Get().GetLibHandle();
    UE_LOG(LogTemp, Log, TEXT("UTsHapticPlayer: begin play."));
}

void UTsHapticPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Device->Handle == nullptr)
    {
        return;
    }

    // Remove playables and unload assets
    for (auto& Asset : Playlist)
    {
		auto& AM = ITeslasuitPlugin::Get().GetHapticAssetManager();
		AM.RemovePlayable(Device->Handle, PlayableIds[Asset->GetUniqueID()]);
        AM.UnloadAsset(*Asset);
    }
    UE_LOG(LogTemp, Log, TEXT("UTsHapticPlayer: end play."));
    Super::EndPlay(EndPlayReason);
}

void UTsHapticPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTsHapticPlayer::SetTsDevice(UTsDevice* Device_)
{
	Device = Device_;
    if (Device != nullptr && Playlist.Num() > 0)
    {
        InitializePlayables();
    }
}

void UTsHapticPlayer::Play(int Index)
{
    UE_LOG(LogTemp, Log, TEXT("UTsHapticPlayer: play haptic."));

	// Check if device available
	if (Device == nullptr)
	{
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to play asset - null device."));
		return;
	}

    // Check if asset available to play
    if (Index < 0 || Index >= Playlist.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to play asset - asset index is out of range."));
        return;
    }

	// Play asset
    auto PlayFn = reinterpret_cast<decltype(&ts_haptic_play_playable)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_haptic_play_playable")));
    if (PlayFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to play asset - null ts_haptic_play_playable handle."));
        return;
    }
    const auto PlayableId = PlayableIds[Playlist[Index]->GetUniqueID()];
	PlayFn(reinterpret_cast<TsDeviceHandle*>(Device->Handle), PlayableId);
}

void UTsHapticPlayer::Stop(int Index)
{
    UE_LOG(LogTemp, Log, TEXT("UTsHapticPlayer: stop haptic."));

    // Check if device available
    if (Device == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to stop asset - null device."));
        return;
    }

    // Check if asset available
    if (Index < 0 || Index >= Playlist.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to stop asset - asset index is out of range."));
        return;
    }

    // Stop asset
    auto StopFn = reinterpret_cast<decltype(&ts_haptic_stop_playable)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_haptic_stop_playable")));
    if (StopFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to stop asset - null ts_haptic_stop_playable handle."));
        return;
    }
    const auto PlayableId = PlayableIds[Playlist[Index]->GetUniqueID()];
    StopFn(reinterpret_cast<TsDeviceHandle*>(Device->Handle), PlayableId);
}

void UTsHapticPlayer::StopPlayer()
{
    UE_LOG(LogTemp, Log, TEXT("UTsHapticPlayer: stop haptic player."));

    // Check if device available
    if (Device == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to stop player - null device."));
        return;
    }

    // Stop player
    auto StopFn = reinterpret_cast<decltype(&ts_haptic_stop_player)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_haptic_stop_player")));
    if (StopFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("UTsHapticPlayer: failed to stop player - null ts_haptic_stop_player handle."));
        return;
    }
    StopFn(reinterpret_cast<TsDeviceHandle*>(Device->Handle));
}

void UTsHapticPlayer::InitializePlayables()
{
    // Load each asset from playlist, create playables and store their ids
    auto& AM = ITeslasuitPlugin::Get().GetHapticAssetManager();
    for (auto& Asset : Playlist)
    {
        auto AssetHandle = AM.LoadAsset(*Asset);
        PlayableIds[Asset->GetUniqueID()] = AM.CreatePlayable(Device->Handle, AssetHandle);
    }
}
