#include "TsDeviceManager.h"
#include "ITeslasuitPlugin.h"
#include "TsDeviceProvider.h"


void UTsDeviceManager::Initialize()
{
    // Init device slots
    Devices =
    {
        { EDeviceIndex::Device0, NewObject<UTsDevice>() },
        { EDeviceIndex::Device1, NewObject<UTsDevice>() },
        { EDeviceIndex::Device2, NewObject<UTsDevice>() },
        { EDeviceIndex::Device3, NewObject<UTsDevice>() },
        { EDeviceIndex::Device4, NewObject<UTsDevice>() },
        { EDeviceIndex::Device5, NewObject<UTsDevice>() },
        { EDeviceIndex::Device6, NewObject<UTsDevice>() },
        { EDeviceIndex::Device7, NewObject<UTsDevice>() }
    };

    // Register device provider callbacks
    auto& Provider = ITeslasuitPlugin::Get().GetDeviceProvider();
    Provider.SubscribeOnConnect((intptr_t)this,[this](const TsDeviceId& Id, void* Handle) { ProcessDeviceConnected(Id, Handle); });
    Provider.SubscribeOnDisconnect((intptr_t)this,[this](const TsDeviceId& Id) { ProcessDeviceDisconnected(Id); });

    // Process already connected devices
    const auto& Ids = Provider.GetDeviceIds();
    for (const auto& Id : Ids)
    {
        ProcessDeviceConnected(Id, Provider.GetDeviceHandle(Id));
    }
}

void UTsDeviceManager::UnInitialize()
{
    // Register device provider callbacks
    auto& Provider = ITeslasuitPlugin::Get().GetDeviceProvider();
    Provider.UnSubscribeOnConnect((intptr_t)this);
    Provider.UnSubscribeOnDisconnect((intptr_t)this);
}

UTsDevice* UTsDeviceManager::GetDevice(EDeviceIndex index)
{
    auto it = Devices.Find(index);
    return it != nullptr ? *it : nullptr;
}

void UTsDeviceManager::ProcessDeviceConnected(const TsDeviceId& Id, void* Handle)
{
    // Search variables
    UTsDevice* Device = nullptr;
    EDeviceIndex FreeIndex = EDeviceIndex::Device0;

    // Check if device is already existing
    auto It = LinkedIndexes.find(Id);
    if (It != LinkedIndexes.end())
    {
        Device = Devices[It->second];
    }
    // Find slot for a new device
    else
    {
        for (std::uint8_t Index = 0; Index < static_cast<std::uint8_t>(EDeviceIndex::Count); ++Index)
        {
            const auto EIndex = static_cast<EDeviceIndex>(Index);
            if (ReservedIndexes.find(EIndex) == ReservedIndexes.end())
            {
                FreeIndex = EIndex;
                break;
            }
        }
        Device = Devices[FreeIndex];
    }

    // Check for logic error
    if (Device->IsConnected())
    {
        UE_LOG(LogTemp, Error, TEXT("UTsDeviceManager: device is alredy connected, guid: %s."), *Id.ToString());
        return;
    }

    // Reserve device slot and connect it
    ReservedIndexes.insert(FreeIndex);
    LinkedIndexes[Id] = FreeIndex;
    Device->Connect(Id, Handle);

    // Notify connect
    OnDeviceConnected.Broadcast(FreeIndex);
}

void UTsDeviceManager::ProcessDeviceDisconnected(const TsDeviceId& Id)
{
    // Check if device exists
    auto It = LinkedIndexes.find(Id);
    if (It == LinkedIndexes.end())
    {
        return;
    }
    const auto EIndex = It->second;

    // Notify disconnect
    OnDeviceDisconnected.Broadcast(EIndex);

    // Remove device
    Devices[EIndex]->Disconnect();
    LinkedIndexes.erase(Id);
    ReservedIndexes.erase(EIndex);
}
