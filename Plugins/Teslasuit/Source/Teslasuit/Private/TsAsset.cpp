#include "TsAsset.h"

void UTsAsset::Initialize(const uint8* Data_, std::size_t Size_)
{
    Data.Empty();
    Data.Append(Data_, Size_);
    UE_LOG(LogTemp, Log, TEXT("UTsAsset: initialized, size: %i."), Data.Num());
}

const TArray<uint8>& UTsAsset::GetData() const
{
    return Data;
}
