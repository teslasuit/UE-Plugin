#pragma once
#include <set>
#include <map>
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TsDevice.h"
#include "TsDeviceManager.generated.h"

/**
 * \addtogroup device
 * @{
 */

/*!
    \brief Device indexes.

    Index of device or empty device slot.
*/
UENUM(BlueprintType)
enum class EDeviceIndex : uint8
{
    Device0 = 0,
    Device1 = 1,
    Device2 = 2,
    Device3 = 3,
    Device4 = 4,
    Device5 = 5,
    Device6 = 6,
    Device7 = 7,
    Count = 8
};

/*!
    \brief Notification on device connected.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceConnectedDelegate, EDeviceIndex, DeviceIndex);

/*!
    \brief Notification on device disconnected.
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeviceDisconnectedDelegate, EDeviceIndex, DeviceIndex);

 /*!
     \brief Manages the access to Teslasuit devices.

     The class can be used to get object of #UTsDevice in order to use it 
     with device subsystems: #UTsHapticPlayer, #UTsMotion, #UTsPpg.
 */
UCLASS(Blueprintable, Category = "Teslasuit")
class TESLASUIT_API UTsDeviceManager : public UObject
{
	GENERATED_BODY()
public:

    /*!
        \brief Initialize Device Manager.

        The method must be called before using an instance of the class.
        #UTsDeviceManager is initialized on base of #TsDeviceProvider.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Device")
    void Initialize();

    /*!
        \brief UnInitialize Device Manager.

        The method must be called after using an instance of the class.
    */
    UFUNCTION(BlueprintCallable, Category = "Teslasuit|Device")
    void UnInitialize();
    /*!
        \brief Returns the device by index.

		\return #UTsDevice
    */
	UFUNCTION(BlueprintCallable, Category = "Teslasuit|Device")
    UTsDevice* GetDevice(EDeviceIndex index = EDeviceIndex::Device0);

private:
    void ProcessDeviceConnected(const TsDeviceId& Id, void* Handle);
    void ProcessDeviceDisconnected(const TsDeviceId& Id);

private:
    /*!
        \brief Device slots accesible by device index.

        Connected devices places at first empty slot, so first connected devices will be
        at EDeviceIndex::Device0, second connected device will be at EDeviceIndex::Device1.

        To check is device connected check #UTsDevice property bConnected.
    */
    UPROPERTY()
    TMap<EDeviceIndex, UTsDevice*> Devices;

    /*!
        \brief Notification on device connected.
    */
    UPROPERTY(BlueprintAssignable, Category = "Teslasuit|Device")
    FDeviceConnectedDelegate OnDeviceConnected;

    /*!
        \brief Notification on device disconnected.
    */
    UPROPERTY(BlueprintAssignable, Category = "Teslasuit|Device")
    FDeviceDisconnectedDelegate OnDeviceDisconnected;

    std::map<TsDeviceId, EDeviceIndex> LinkedIndexes;
    std::set<EDeviceIndex> ReservedIndexes;
};

/**@}*/
