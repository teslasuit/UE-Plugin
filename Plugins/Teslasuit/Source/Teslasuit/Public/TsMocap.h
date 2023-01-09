// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <mutex>
#include "CoreMinimal.h"
#include "TsDevice.h"
#include "TsMocap.generated.h"

/**
 * \defgroup mocap Mocap Module
 * 
 * The Mocap API provides real time access to mocap data.
 * 
 * To start working with mocap assign #UTsMotion component to actor.
 * @{
 */

/*!
    \brief Teslasuit Bone indexes.
*/
UENUM(BlueprintType)
enum class FTsBoneIndex: uint8
{
    TsBoneIndex_Hips = 0,
    TsBoneIndex_LeftUpperLeg = 1,
    TsBoneIndex_RightUpperLeg = 2,
    TsBoneIndex_LeftLowerLeg = 3,
    TsBoneIndex_RightLowerLeg = 4,
    TsBoneIndex_LeftFoot = 5,
    TsBoneIndex_RightFoot = 6,
    TsBoneIndex_Spine = 7,
    TsBoneIndex_Chest = 8,
    TsBoneIndex_UpperSpine = 9,
    TsBoneIndex_Neck = 10,
    TsBoneIndex_Head = 11,
    TsBoneIndex_LeftShoulder = 12,
    TsBoneIndex_RightShoulder = 13,
    TsBoneIndex_LeftUpperArm = 14,
    TsBoneIndex_RightUpperArm = 15,
    TsBoneIndex_LeftLowerArm = 16,
    TsBoneIndex_RightLowerArm = 17,
    TsBoneIndex_LeftHand = 18,
    TsBoneIndex_RightHand = 19,
    TsBoneIndex_LeftThumbProximal = 20,
    TsBoneIndex_LeftThumbIntermediate = 21,
    TsBoneIndex_LeftThumbDistal = 22,
    TsBoneIndex_LeftIndexProximal = 23,
    TsBoneIndex_LeftIndexIntermediate = 24,
    TsBoneIndex_LeftIndexDistal = 25,
    TsBoneIndex_LeftMiddleProximal = 26,
    TsBoneIndex_LeftMiddleIntermediate = 27,
    TsBoneIndex_LeftMiddleDistal = 28,
    TsBoneIndex_LeftRingProximal = 29,
    TsBoneIndex_LeftRingIntermediate = 30,
    TsBoneIndex_LeftRingDistal = 31,
    TsBoneIndex_LeftLittleProximal = 32,
    TsBoneIndex_LeftLittleIntermediate = 33,
    TsBoneIndex_LeftLittleDistal = 34,
    TsBoneIndex_RightThumbProximal = 35,
    TsBoneIndex_RightThumbIntermediate = 36,
    TsBoneIndex_RightThumbDistal = 37,
    TsBoneIndex_RightIndexProximal = 38,
    TsBoneIndex_RightIndexIntermediate = 39,
    TsBoneIndex_RightIndexDistal = 40,
    TsBoneIndex_RightMiddleProximal = 41,
    TsBoneIndex_RightMiddleIntermediate = 42,
    TsBoneIndex_RightMiddleDistal = 43,
    TsBoneIndex_RightRingProximal = 44,
    TsBoneIndex_RightRingIntermediate = 45,
    TsBoneIndex_RightRingDistal = 46,
    TsBoneIndex_RightLittleProximal = 47,
    TsBoneIndex_RightLittleIntermediate = 48,
    TsBoneIndex_RightLittleDistal = 49,
    TsBoneIndex_BonesCount = 50
};

/*!
     \brief Controls mocap streaming from provided #UTsDevice.
 */
UCLASS(Blueprintable, ClassGroup = Teslasuit, Category = "Teslasuit|Mocap")
class TESLASUIT_API UTsMocap : public UObject
{
	GENERATED_BODY()
public:
    using MocapData = TMap<FTsBoneIndex, FTransform>;

public:
	UTsMocap();
	~UTsMocap() override;

    /*!
        \brief Initializes Teslasuit API library functions for mocap subsystem.
    */
    void Initialize();

    /*!
        \brief Starts mocap streaming.
    */
	void StartMocap();

    /*!
        \brief Stops mocap streaming.
    */
	void StopMocap();

    /*!
        \brief Calibrates mocap subsystem.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Mocap")
	void Calibrate();

    /*!
        \brief Copies mocap data to provided buffer.
    */
    void GetMocapData(MocapData& OutData) const;

    /*!
        \brief Sets #UTsDevice to stream data from.
    */
	UFUNCTION(BlueprintCallable, Category = "Teslasuit|General")
	void SetTsDevice(UTsDevice* device);
	
    /*!
        \brief Is mocap subsystem initialized with device.
    */
    UPROPERTY(BlueprintReadOnly, Category = "Teslasuit|General")
    bool DeviceInitialized = false;

private:
	void SetCallbacks();

private:
	UTsDevice* ts_device {nullptr};
    bool bMocapRunning = false;
    mutable std::mutex AccessMutex;

    MocapData Data;
};

/**@}*/
