// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <mutex>
#include "CoreMinimal.h"
#include "TsDevice.h"
#include "TsPpg.generated.h"

/**
 * \defgroup biometry Biometry Module
 *   
 * The Biometry module provides real time access to PPG data.
 * @{
 */

/*!
    \brief Controls PPG streaming from provided #UTsDevice.
*/
UCLASS(Blueprintable, ClassGroup = Teslasuit, Category = "Teslasuit|Biometry")
class TESLASUIT_API UTsPpg : public UObject
{
	GENERATED_BODY()
public:
    UTsPpg();
    ~UTsPpg();

    /*!
        \brief Initializes Teslasuit API library functions for PPG subsystem.
    */
    void Initialize();

    /*!
        \brief Starts PPG streaming.
    */
	void StartPpg();

    /*!
        \brief Stops PPG streaming.
    */
	void StopPpg();

    /*!
        \brief Sets #UTsDevice to stream data from.
    */
	UFUNCTION(BlueprintCallable, Category = "Teslasuit|General")
	void SetTsDevice(UTsDevice* device);

    /*!
        \brief Calibrates PPG subsystem.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Biometry")
    void Calibrate();

    /*!
        \brief Is PPG subsystem initialized with device.
    */
    UPROPERTY(BlueprintReadOnly, Category = "Teslasuit|Biometry")
    bool DeviceInitialized = false;

    /*!
        \brief Stores heart rate activity in beats per minute.
    */
    UPROPERTY(BlueprintReadOnly, Category = "Teslasuit|Biometry")
    int Heartrate{ 0 };

    /*!
        \brief Stores oxygen saturation in percents.
    */
    UPROPERTY(BlueprintReadOnly, Category = "Teslasuit|Biometry")
    int OxygenPercent { 0 };

private:
	void SetCallbacks();

private:
	UTsDevice* ts_device {nullptr};
    bool bPpgRunning = false;
    mutable std::mutex AccessMutex;
};

/**@}*/
