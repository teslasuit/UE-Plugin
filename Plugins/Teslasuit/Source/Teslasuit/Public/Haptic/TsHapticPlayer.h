#pragma once
#include <map>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TsAsset.h"
#include "TsDevice.h"
#include "TsHapticPlayer.generated.h"

/**
 * \addtogroup haptic
 * @{
 */

/*!
    \brief Controls haptic playback for provides #UTsDevice.

    UTsHapticPlayer is actor component that provides haptic asset playback functionality.
    Player should be assigned to specific device using SetTsDevice function.
    Player Playlist can be filled with haptic assets.
    Assets can be played with Play functiton by index in Playlist.
 */
UCLASS(ClassGroup=Teslasuit, Category = "Teslasuit", meta=(BlueprintSpawnableComponent))
class TESLASUIT_API UTsHapticPlayer : public UActorComponent
{
	GENERATED_BODY()
    
public:
	UTsHapticPlayer();

protected:
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    /*!
        \brief Set device to play haptic on.

        Set device is also initializes assets playlist for specific device using #TsHapticAssetManager.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|General")
    void SetTsDevice(UTsDevice* Device_);

    /*!
        \brief Plays haptic asset from HapticAssets array by index.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Haptic")
    void Play(int Index);

    /*!
        \brief Stops haptic asset from HapticAssets array by index.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Haptic")
    void Stop(int Index);

    /*!
        \brief Final stop of haptic player and all assets.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Haptic")
    void StopPlayer();

private:
    void InitializePlayables();

public:
    /*!
        \brief Assets available to play on device.

        Playlist can be filled in blueprint. It will be compiled for specific device on SetTsDevice.
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teslasuit|Haptic")
    TArray<UTsAsset*> Playlist;

private:
	void* LibHandle = nullptr;

    /*!
        \brief Device to play haptic on.
    */
    UPROPERTY()
    UTsDevice* Device = nullptr;

	std::map<uint32, std::uint64_t> PlayableIds;
};

/**@}*/
