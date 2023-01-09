#include "TsDeviceProvider.h"
#include "TsDevice.h"
#include "ts_api/ts_device_api.h"

const uint32_t UpdatePeriodMs = 1000;
const uint32_t DefaultDeviceListSize = 8;
std::vector<TsDevice> RefreshingDeviceList(DefaultDeviceListSize);
TsDevice* ConnectingDevice;

TsDeviceProvider::TsDeviceProvider()
    : UpdateThread{ &TsDeviceProvider::UpdateDeviceList, this }
{
    UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: constructed."));
}

void TsDeviceProvider::SetLibHandle(void* Handle)
{
    LibHandle = Handle;
}

void TsDeviceProvider::Start()
{
    UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: start update device list."));
    bUpdateRunning = true;
}

void TsDeviceProvider::Stop()
{
    UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: stop update device list."));
    bUpdateRunning = false;
}

void TsDeviceProvider::UpdateDeviceList()
{
    // Run update until destruction
    while (!bUpdateFinished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(UpdatePeriodMs));

        // Update can be started or stopped multiple times for a single object life time
        if (!bUpdateRunning)
            continue;

        // Checks for library and API functions availability
        if (LibHandle == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("TsDeviceProvider: can't update device list - null lib handle."));
            return;
        }
        auto GetDeviceListFn = reinterpret_cast<decltype(&ts_get_device_list)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_get_device_list")));
        if (GetDeviceListFn == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("TsDeviceProvider: can't update device list - null ts_get_device_list handle."));
            return;
        }

        // Refresh device list through API
        uint32_t DeviceCount = DefaultDeviceListSize;
        GetDeviceListFn(RefreshingDeviceList.data(), &DeviceCount);
        UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: update device list - count: %i."), DeviceCount);

        // Determine connected and disconnected devices
        Ids DisconnectedIds = DeviceIds;
        for (uint32_t DeviceIndex = 0; DeviceIndex < DeviceCount; ++DeviceIndex)
        {
            auto& Device = RefreshingDeviceList[DeviceIndex];
            const TsDeviceId Id(Device.uuid);
            UE_LOG(LogTemp, Log, TEXT("    device guid: %s."), *Id.ToString());
            
            if (DeviceIds.find(Id) != DeviceIds.end())
            {
                DisconnectedIds.erase(Id);
            }
            else
            {
                // Process connected devices
                ConnectingDevice = &Device;
                AsyncTask(ENamedThreads::GameThread, [=]()
                {
                    OnDeviceConnected(Id);
                });
            }
        }

        // Process disconnected devices
        for (const auto& Id : DisconnectedIds)
        {
            AsyncTask(ENamedThreads::GameThread, [=]()
            {
                OnDeviceDisconnected(Id);
            });
        }
    }
}

void TsDeviceProvider::OnDeviceConnected(const TsDeviceId& Id)
{
    UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: device CONNECTED - guid: %s."), *Id.ToString());
    
    // Open device before working with it
    auto DeviceOpenFn = reinterpret_cast<decltype(&ts_device_open)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_device_open")));
    if (DeviceOpenFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsDeviceProvider: failed to open device - null ts_device_open handle."));
        return;
    }
    auto Device = reinterpret_cast<const TsDevice*>(Id.GetData());
    auto Handle = static_cast<void*>(DeviceOpenFn(const_cast<TsDevice*>(Device)));
    if (Handle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsDeviceProvider: failed to open device - null handle returned."));
        return;
    }

    // Register connected device
    DeviceHandles[Id] = Handle;
    DeviceIds.insert(Id);

    // Notify connected device
    for (auto It = ConnectCallbacks.begin(); It != ConnectCallbacks.end(); ++It)
    {
        auto& Fn = It->second;
        if (Fn)
        {
            Fn(Id, Handle);
        }
        else
        {
            It = ConnectCallbacks.erase(It);
        }
    }
}

void TsDeviceProvider::OnDeviceDisconnected(const TsDeviceId& Id)
{
    UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: device DISCONNECTED - guid: %s."), *Id.ToString());
    // Notify disconnected device
    for (auto It = DisconnectCallbacks.begin(); It != DisconnectCallbacks.end(); ++It)
    {
        auto& Fn = It->second;
        if (Fn)
        {
            Fn(Id);
        }
        else
        {
            It = DisconnectCallbacks.erase(It);
        }
    }
    
    // Unregister device
    DeviceIds.erase(Id);
    DeviceHandles.erase(Id);
}

void TsDeviceProvider::CloseDevices()
{
    // Resolve and check close function
    auto DeviceCloseFn = reinterpret_cast<decltype(&ts_device_close)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_device_close")));
    if (DeviceCloseFn == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("TsDeviceProvider: failed to close device - null ts_device_close handle."));
        return;
    }

    // Close open devices
    for (auto& It : DeviceHandles)
    {
        DeviceCloseFn(static_cast<TsDeviceHandle*>(It.second));
    }
}

TsDeviceProvider::~TsDeviceProvider()
{
    // Stop updating device list
    Stop();
    // Close all open devices
    CloseDevices();
    // Stop update thread
    bUpdateFinished = true;
    if (UpdateThread.joinable())
    {
        UpdateThread.join();
    }
    UE_LOG(LogTemp, Log, TEXT("TsDeviceProvider: deconstructed."));
}

void TsDeviceProvider::SubscribeOnConnect(intptr_t subscriberID, const ConnectCallback& Cb)
{
    ConnectCallbacks[subscriberID] = Cb;
}

void TsDeviceProvider::SubscribeOnDisconnect(intptr_t subscriberID, const DisconnectCallback& Cb)
{
    DisconnectCallbacks[subscriberID] = Cb;
}

void TsDeviceProvider::UnSubscribeOnConnect(intptr_t subscriberID)
{
    ConnectCallbacks.erase(subscriberID);
}

void TsDeviceProvider::UnSubscribeOnDisconnect(intptr_t subscriberID)
{
    DisconnectCallbacks.erase(subscriberID);
}

const TsDeviceProvider::Ids& TsDeviceProvider::GetDeviceIds() const
{
    return DeviceIds;
}

void* TsDeviceProvider::GetDeviceHandle(const TsDeviceId& Id) const
{
    auto It = DeviceHandles.find(Id);
    return It != DeviceHandles.end() ? It->second : nullptr;
}
