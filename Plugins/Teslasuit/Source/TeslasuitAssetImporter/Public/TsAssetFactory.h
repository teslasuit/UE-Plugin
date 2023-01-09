#pragma once
#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "TsAssetFactory.generated.h"

/**
 * \addtogroup asset
 * @{
 */

/*!
   \brief Factory of assets.

   Class is used to import ".ts_asset" files.
   It's detects import of ".ts_asset" files and creates instances of #UTsAsset class.
 */
UCLASS()
class TESLASUITASSETIMPORTER_API UTsAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
    /*!
        \brief Initializes and configures factory for ".ts_asset" files.
    */
    UTsAssetFactory();

private:
    /*!
        \brief Creates instance of #UTsAsset on base of ".ts_asset" files.

        Called on import of ".ts_asset" file into UE project,
        Creates data wrapper class #UTsAsset, which becames available in UE editor.
    */
    UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
        UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd,
        FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};

/**@}*/
