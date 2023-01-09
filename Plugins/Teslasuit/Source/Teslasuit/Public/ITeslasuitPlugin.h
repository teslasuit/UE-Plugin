#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

/*! \mainpage Main Page
 * \section intro_section Introduction
 * Teslasuit Unreal Engine Plugin provides a set of classes for working with the main features of Teslasuit 4.X, 5.X and Teslasuit Glove, 
 * such as getting information about connected devices, controlling haptic feedback, motion capture, biometry data.
 *
 * Plugin contains next modules:
 * Module            | Description   | Link
 * ----------------- | ------------- | -------------
 * **Core**          | Unreal Engine plugin implementation and core functionality of plugin. | \ref core
 * **Device**        | Device module provides information about connected Teslasuit devices and the main control funсtions for them. | \ref device
 * **Haptic**        | Haptic module provides functions for haptic playback control. | \ref haptic
 * **Mocap**         | Mocap module provides functions for mocap streaming. | \ref mocap
 * **Biometry**      | Biometry module provides functions for ppg streaming. | \ref biometry
 * **Asset**         | Asset module provides functions for asset management, such as loading and parsing asset files. | \ref asset
 *
 * 
 * \section Requrements
 * To start working with Teslasuit Unreal Engine Plugin:
 * - 1.Go to [the Downloads page of the Developer portal](https://developer.teslasuit.io/downloads).
 * - 2.In the SOFTWARE section, download and install the latest version of the Teslasuit Studio.
 *

 * \section TsDeviceManager
 * UTsDeviceManager object provides access to all available devices and its events.
 * 
 * Code usage:
 * 
 * @code
 * ...
 * UTsDeviceManager* manager = NewObject<UTsDeviceManager>();
 * manager->Initialize();
 * UTsDevice* device = manager->GetDevice(EDeviceIndex::Device0);
 * ...
 * @endcode
 * 
 * Blueprint usage:
 * 
 * \image html ts_device_manager_construct.JPG TsDeviceManager construct
 * 
 * 
 * \section TsDevice
 * UTsDevice object is used by subsystems
 * 
 * Code usage:
 * 
 * @code
 * ...
 * UTsDevice* device = manager->GetDevice(EDeviceIndex::Device0);
 * 
 * UTsPpg* ppg = NewObject<UTsPpg>();
 * ppg->SetTsDevice(device);
 * ...
 * @endcode
 * 
 * Blueprint usage:
 * 
 * \image html ts_device_manager_usage.JPG TsDevice events and access
 * 
 * 
 * \section Subsystems
 * 
 * \subsection PPG
 * UTsPpg object provides access to biometry pulse oximeter data 
 * 
 * Code usage:
 * @code
 * ...
 * UTsDevice* device = manager->GetDevice(EDeviceIndex::Device0);
 * 
 * UTsPpg* ppg = NewObject<UTsPpg>();
 * ppg->SetTsDevice(device);
 * ppg->Initialize();
 * ppg->Calibrate();
 * 
 * ...
 * 
 * int heartrate = ppg->Heartrate;
 * int spo2 = ppg->OxygenPercent;
 * 
 * ...
 * @endcode
 * 
 * 
 * Blueprint usage:
 * 
 * \image html ts_ppg_usage.JPG PPG Initialization
 * <br>
 * \image html ts_ppg_usage_calibr.JPG PPG Calibration
 * 
 * 
 * \subsection Motion
 * UTsMotion component is used to animate character models. 
 * It should be added to model with SkeletalMeshComponent.
 * In AnimationClass property TeslasuitMannequinAnimation should be selected.
 * Character should be set to I-Pose as a default pose in skeleton editor (straight stance, arms is lowered down).
 * 
 * \image html ts_motion_component_usage.JPG TsMotion component
 * 
 * Blueprint usage:
 * 
 * \image html ts_mocap_usage_1.JPG Mocap initialization
 * <br>
 * \image html ts_mocap_usage_2.JPG Mocap calibration
 * 
 * @code
 * ...
 * UTsDevice* device = manager->GetDevice(EDeviceIndex::Device0);
 * 
 * UTsMotion* motion = Cast<UTsMotion>(GetOwner()->GetComponentByClass(UTsMotion::StaticClass()));
 * motion->mocap->SetTsDevice(device);
 * motion->mocap->Calibrate();
 * ...
 * @endcode
 * 
 * \subsection Haptic
 * UTsHapticPlayer component is used to play haptic animation assets.
 * There are Playlist array property that can be filled with TsAsset items (Haptic animations).
 * Where TsAsset item is haptic animation asset created is Studio.
 * 
 * \image html ts_haptic_component_usage.JPG TsHapticPlayer component
 * 
 * Blueprint usage:
 * 
 * \image html ts_haptic_usage.JPG Haptic initialization and play
 * 
 * Code usage:
 * 
 * @code
 * ...
 * UTsDevice* device = manager->GetDevice(EDeviceIndex::Device0);
 * 
 * UTsHapticPlayer* haptic_player = Cast<UTsHapticPlayer>(GetOwner()->GetComponentByClass(UTsHapticPlayer::StaticClass()));
 * haptic_player->SetTsDevice(device);
 * haptic_player->Play(2);
 * ...
 * @endcode
 * 
 * 
 * \section Troubleshooting
 * There are some guides regarding to TeslasuitPlugin problems
 * 
 * \subsection Missing TeslasuitPlugin Modules
 * In some versions of the Unreal Engine, a "Missing TeslasuitPlugin Modules" message may appear:
 * 
 * \image html missing_ts_plugin.JPG Missing TeslasuitPlugin Modules dialog
 * 
 * TeslasuitPlugin can be rebuilt by the clicking "Yes" on the popup dialog.
 * 
 * If the problem still remains, another way is to rebuild TeslasuitPlugin manually:
 * 
 * To create TeslasuitPlugin.sln solution, open context menu on TeslasuitPlugin.uproject and click "Generate Visual Studio project files".
 * 
 * \image html generate_ts_plugin_solution.JPG TeslasuitPlugin.uproject context menu
 * 
 * After opening TeslasuitPlugin.sln, find and build the project with name "TeslasuitPlugin".
 * 
 * \image html ts_plugin_solution.JPG TeslasuitPlugin project contents
 * 
 */



/**
 * \defgroup core Core Module
	Unreal Engine plugin implementation and core functionality.

    Module provides main #ITeslasuitPlugin interface which is implemented by #FTeslasuitModule class.
    
    Module loads Teslasuit C API library and provides wrapper classes for it.
 * @{
 */


class TsDeviceProvider;
class TsHapticAssetManager;

/*!
	\brief Interface of Teslasuit module.

	The interface describes Teslasuit module implementation.
    Provides methods for getting singleton classes of the plugin, such as:
    - module instance
    - C API library handle
    - device provider instance
    - haptic asset manager instance
*/
class TESLASUIT_API ITeslasuitPlugin : public IModuleInterface
{
public:
    /*!
        \brief Returns is Teslasuit module is loaded.
        \return bool
    */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Teslasuit");
	}

    /*!
        \brief Returns loaded Teslasuit module.

        Returns instance if the module with current interface.
        If module is not loaded, it will be loaded before return.
        \return #ITeslasuitPlugin&
    */
	static inline ITeslasuitPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<ITeslasuitPlugin>("Teslasuit");
	}

	/*!
		\brief Returns pointer to the Teslasuit C API library.

        Library is automatically loaded when Teslasuit module starts.
        Library can be used to resolve C API function adresses, for example:

        \code{.cpp}
        #include "ts_api/ts_device_api.h"
        auto GetDeviceListFn = reinterpret_cast<decltype(&ts_get_device_list)>(FPlatformProcess::GetDllExport(LibHandle, *FString("ts_get_device_list")));
        \endcode

		\return void*
	*/
	virtual void* GetLibHandle() const = 0;

	/*!
		\brief Returns a reference for instance of #TsDeviceProvider.

        #TsDeviceProvider is convinient CPP wrapper of device C API.
        It's implemented to be signle instance per application - it's built into Teslasuit module.
        For accessing devices in Unreal Engine way you might use #UTsDeviceManager class, which is based on #TsDeviceProvider.
		\return #TsDeviceProvider
	*/
	virtual TsDeviceProvider& GetDeviceProvider() = 0;	
	
	/*!
		\brief Returns a reference for instance of #TsHapticAssetManager.
		\return #TsHapticAssetManager
	*/
	virtual TsHapticAssetManager& GetHapticAssetManager() = 0;
};

/**@}*/
