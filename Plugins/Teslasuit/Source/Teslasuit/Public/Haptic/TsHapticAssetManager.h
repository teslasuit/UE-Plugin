#pragma once
#include <set>
#include <map>
#include "TsAsset.h"

/**
* \defgroup haptic Haptic Module
	The Haptic module provides haptic playback and haptic assets managing functions with next classes:
		- #TsHapticAssetManager
		- #UTsHapticPlayer
* @{
*/

/*!
\brief Loads binary assets and assings it for future playing on a device.

You may preffer to use #UTsHapticPlayer with specific #UTsDevice instead of using this class directly.

In order to be able to play haptic asset you need:
	- Import haptic assets to UE project (importing should be auto handled by TeslasuitAssetImporter)
	- Acquire #UTsAsset object after import
	- Load asset to C API to get AssetHandle using #LoadAsset method
	- #CreatePlayable for specific device with device handle and asset handle
	- Acquire playable id to control it's playback

In order to release resources:
	- Remove all created playables with #RemoveAllPlayables method
	- Unload all assets with #UnloadAllAssets method

#UTsHapticPlayer is automatically manages all things listed above.
*/
class TESLASUIT_API TsHapticAssetManager
{
public:
	TsHapticAssetManager();
	~TsHapticAssetManager();

	// Client methods

	/*!
		\brief Loads haptic asset and returns handle to it.

		\return void*
	*/
	void* LoadAsset(const UTsAsset& Asset);

	/*!
		\brief Unloads haptic asset.
	*/
	void UnloadAsset(const UTsAsset& Asset);

	/*!
		\brief Creates playable from asset handle for device with specific haptic configuration.

		Returns id of created playable, which can be used to control playback.

		\return std::uint64_t
	*/
	std::uint64_t CreatePlayable(void* DeviceHandle, void* AssetHandle);

	/*!
		\brief Removes playable.
	*/
	void RemovePlayable(void* DeviceHandle, std::uint64_t PlayableId);

	/*!
		\brief Removes all created playables for all devices.
	*/
	void RemoveAllPlayables();

	/*!
		\brief Unloads all loaded assets.
	*/
	void UnloadAllAssets();

	// Configure methods

	/*!
		\brief Set Teslasuit C API library.
	*/
	void SetLibHandle(void* Handle);

private:
	void UnloadAsset(void* AssetHandle);

private:
	void* LibHandle = nullptr;
	std::map<uint32, void*> AssetHandles;
	std::set<void*> UsedDevices;
};

/**@}*/
