#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TsAsset.generated.h"

/**
 * \addtogroup asset
 * @{
 */

/*!
   \brief Stores binary data of loaded Teslasuit Asset.

   Wrapper of asset data. 
   Class is used by #UTsAssetFactory in module #TeslasuitAssetImporter to import ".ts_asset" files.
   #TeslasuitAssetImporter detects import of ".ts_asset" files and creates instances of #UTsAsset class.
   TS asset files can be created in Teslasuit Studio application.
 */
UCLASS(Blueprintable, Category = "Teslasuit")
class TESLASUIT_API UTsAsset : public UObject
{
	GENERATED_BODY()
public:
    /*!
        \brief Initialization from raw data.
    */
    void Initialize(const uint8* Data_, std::size_t Size_);

    /*!
        \brief Get data array reference.
    */
    const TArray<uint8>& GetData() const;
	
private:
    UPROPERTY()
    TArray<uint8> Data;
};

/**@}*/
