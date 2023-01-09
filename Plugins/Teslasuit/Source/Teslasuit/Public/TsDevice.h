#pragma once
#include "CoreMinimal.h"
#include "TsDeviceId.h"
#include "TsDevice.generated.h"

/**
 * \defgroup device Device Module
	Device module includes next elements:
		- #UTsDevice class is representing Teslasuit Device
		- #TsDeviceId convinient class for unique device id with compare operators
		- #TsDeviceProvider low level singleton device provider
		- #UTsDeviceManager high level UE class for managing devices

	Note that usage of #UTsDeviceManager is more preferred than low level #TsDeviceProvider.

	#UTsDeviceManager can be instanced multiple times and can be accessed from blueprints.
	
	#UTsDeviceManager also provides #UTsDevice accessible from blueprints.
 * @{
 */
 
/*!
    \brief Teslasuit device.

	Represents Teslasuit device or slot for device that can be connected in future.
	Stores handle to the device, it's unique id and connection state.
*/
UCLASS(Blueprintable, ClassGroup = Teslasuit, Category = "Teslasuit|Device")
class TESLASUIT_API UTsDevice : public UObject
{
    GENERATED_BODY()

public:
	/*!
		\brief Returns connecton state of the device.

		\return bool
	*/
	bool IsConnected() const;

	/*!
		\brief Returns #TsDeviceId of the device.

		\return #TsDeviceId
	*/
	const TsDeviceId& GetDeviceId() const;

	// Management methods

	/*!
		\brief Connects the device.

		Connects by its #TsDeviceId and device handle received from the Teslasuit C API library.
	*/
	void Connect(const TsDeviceId& Id_, void* Handle_);

	/*!
		\brief Disconnects the device.
	*/
    void Disconnect();

private:
	void Reset();

public:
	/*!
		\brief Raw Teslasuit device handle.

		Raw handle can be used for custom C API calls associated with current device.
	*/
	void* Handle;

private:
	TsDeviceId Id;

	/*!
		\brief Is device connected.

		To subscribe to device connection event use #UTsDeviceManager.
	*/
    UPROPERTY()
	bool bConnected = false;

	/*!
		\brief String representation of device id.

		Printable version of device id.
	*/
	UPROPERTY()
    FString IdString = "0";
};

/**@}*/
