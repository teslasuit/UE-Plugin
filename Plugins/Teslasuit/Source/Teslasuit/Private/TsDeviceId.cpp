#include "TsDeviceId.h"

TsDeviceId::TsDeviceId()
{
    Reset();
}

TsDeviceId::TsDeviceId(const UnderlyingType* RawData, std::size_t Size /*= UnderlyingSize*/)
{
    Reset();
    if (Size < UnderlyingSize)
    {
        throw std::exception("UTsDeviceId raw data constructor exception: wrong raw data size.");
        return;
    }

    strncpy(reinterpret_cast<char*>(&Data[0]), reinterpret_cast<const char*>(RawData), UnderlyingSize);
}

TsDeviceId::TsDeviceId(const TsDeviceId& Other)
{
    Reset();
    strncpy(reinterpret_cast<char*>(&Data[0]), reinterpret_cast<const char*>(&Other.Data[0]), UnderlyingSize);
}

TsDeviceId& TsDeviceId::operator=(const TsDeviceId& Other)
{
    if (this != &Other)
    {
        strncpy(reinterpret_cast<char*>(&Data[0]), reinterpret_cast<const char*>(&Other.Data[0]), UnderlyingSize);
    }
    return *this;
}

bool TsDeviceId::operator==(const TsDeviceId& Other) const
{
    return std::memcmp(&Data[0], &Other.Data[0], UnderlyingSize) == 0;
}

bool TsDeviceId::operator<(const TsDeviceId& Other) const
{
    return std::memcmp(&Data[0], &Other.Data[0], UnderlyingSize) < 0;
}

const TsDeviceId::UnderlyingType* TsDeviceId::GetData() const
{
    return &Data[0];
}

void TsDeviceId::Reset()
{
    std::memset(&Data[0], 0, UnderlyingSize);
}

FString TsDeviceId::ToString() const
{
    return FString::FromHexBlob(&Data[0], UnderlyingSize);
}
