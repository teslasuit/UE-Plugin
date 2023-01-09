#pragma once
#include <memory>
#include "Modules/ModuleManager.h"
#include "ITeslasuitPlugin.h"
#include "TsCore.h"
#include "TsDeviceProvider.h"
#include "Haptic/TsHapticAssetManager.h"

/**
 * \addtogroup core
 * @{
 */

/*!
    \brief UE module implementation

    Implementation of UE module and #ITeslasuitPlugin interface.
    Module is automatically loads and unloads C API library.
    Provides access to device provider, haptic asset manager
    and library handle for custom C API wrappers.
*/
class FTeslasuitModule : public ITeslasuitPlugin
{
public:
    /*!
        \brief Module initialization.

        Startup module is automatically called by UE.
        Initializes core API, loads C API library, initializes haptic asset manager.
        Initializes and starts device provider which scan for Teslasuit devices.
    */
	virtual void StartupModule() override;

    /*!
        \brief Module deinitialization.

        Shutdown module is automatically called by UE.
        Stops device provider, deinitializes core API and unloads C API library.
    */
	virtual void ShutdownModule() override;

    virtual void* GetLibHandle() const override;
    virtual TsDeviceProvider& GetDeviceProvider() override;
    virtual TsHapticAssetManager& GetHapticAssetManager() override;

private:
    std::unique_ptr<TsCore> Core;
    std::unique_ptr<TsDeviceProvider> DeviceProvider;
    std::unique_ptr<TsHapticAssetManager> HapticAssetManager;
};

/**@}*/
