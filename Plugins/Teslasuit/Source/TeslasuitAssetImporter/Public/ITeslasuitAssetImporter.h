#pragma once
#include "Modules/ModuleManager.h"

/**
 * \defgroup asset Asset Module
 * 
 * Module allows to import assets to UE project, load them to C API and control their lifetime.
 * @{
 */

/*!
   \brief Asset importer module interface.

   Intarface of UE module, which is used for importing ".ts_asset" files to UE engine.
   \sa UTsAssetFactory, UTsAsset
 */
class ITeslasuitAssetImporter : public IModuleInterface
{
public:
    /*!
        \brief Returns is Asset Importer module is loaded.
        \return bool
    */
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("TeslasuitAssetImporter");
    }

    /*!
        \brief Returns loaded Asset Importer module.

        Returns instance if the module with current interface.
        If module is not loaded, it will be loaded before return.
        \return #ITeslasuitAssetImporter&
    */
    static inline ITeslasuitAssetImporter& Get()
    {
        return FModuleManager::LoadModuleChecked<ITeslasuitAssetImporter>("TeslasuitAssetImporter");
    }
};

/**@}*/