#include "TsDevice.h"
#include "ITeslasuitPlugin.h"
#include "ts_api/ts_device_api.h"

bool UTsDevice::IsConnected() const
{
    return bConnected;
}

const TsDeviceId& UTsDevice::GetDeviceId() const
{
    return Id;
}

void UTsDevice::Connect(const TsDeviceId& Id_, void* Handle_)
{
    Id = Id_;
    Handle = Handle_;
    IdString = Id.ToString();
    bConnected = true;
}

void UTsDevice::Disconnect()
{
    Reset();
}

void UTsDevice::Reset()
{
    Id.Reset();
    Handle = nullptr;
    IdString = "0";
    bConnected = false;
}
