#include "TsAssetFactory.h"
#include "TsAsset.h"

UTsAssetFactory::UTsAssetFactory()
{
    bCreateNew = false;
    bEditAfterNew = true;
    bEditorImport = true;
    SupportedClass = UTsAsset::StaticClass();
    Formats.Add(TEXT("ts_asset;Teslasuit Asset Files"));
}

UObject* UTsAssetFactory::FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
    UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, 
    FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
    const std::size_t Size = BufferEnd - Buffer;
    auto Asset = NewObject<UTsAsset>(InParent, UTsAsset::StaticClass(), InName, Flags);
    Asset->Initialize(Buffer, Size);
    return Asset;
}
