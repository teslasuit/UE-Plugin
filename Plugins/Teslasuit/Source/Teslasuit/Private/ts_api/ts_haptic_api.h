#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup haptic Haptic API
    The Haptic module contains functions to create haptic assets, play single and multiple haptic assets,
    control playback with mixer functions, such as solo and mute, apply multipliers to specific assets or channels.
 * @{
 */

/*!
    \brief Checks out if the haptic player is running.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to attached the device
    \param[out] is_running state is running `true` or is stopped `false`
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_is_player_running(TsDeviceHandle* dev, bool* is_running);

/*!
    \brief Stops the haptic player for the device.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_stop_player(TsDeviceHandle* dev);

/*!
    \brief Checks out if the haptic player is paused.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[out] is_paused paused
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_player_paused(TsDeviceHandle* dev, bool* is_paused);

/*!
    \brief Sets the haptic player on pause or resumes the state.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] is_paused is paused `true` or resume `false`
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_player_paused(TsDeviceHandle* dev, bool is_paused);

/*!
    \brief Checks out if the haptic player is muted.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[out] is_muted muted
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_player_muted(TsDeviceHandle* dev, bool* is_muted);

/*!
    \brief Sets the muting state for the haptic player.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] is_muted muted
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_player_muted(TsDeviceHandle* dev, bool is_muted);

/*!
    \brief Gets haptic player time since the player has started.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[out] time player time since start in milliseconds
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_player_time(TsDeviceHandle* dev, uint64_t* time);

/*!
    \brief Gets number of haptic master multipliers.

    Master multiplier changes affect all playable items.
    There can be numerous multipliers, one for each haptic parameter type.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[out] number_of_multipliers number of master multipliers
    \return #TsStatusCode
    \sa ts_haptic_get_master_multipliers
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_number_of_master_multipliers(TsDeviceHandle* dev,
        uint64_t* number_of_multipliers);

/*!
    \brief Gets haptic player master multipliers.

    Each multiplier in `multipliers` corresponds to a certain haptic parameter type.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_haptic_get_number_of_master_multipliers
    \param[in] dev handler to the attached device
    \param[out] multipliers preallocated array of master multipliers
    \param[in] number_of_multipliers size of `multipliers` array
    \return #TsStatusCode
    \sa ts_haptic_get_number_of_master_multipliers, ts_haptic_set_master_multipliers
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_master_multipliers(TsDeviceHandle* dev,
        TsHapticParamMultiplier* multipliers, uint64_t number_of_multipliers);

/*!
    \brief Sets haptic player master multipliers.

    Master multipliers affect all the clients of the provided device.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] multipliers master multipliers
    \param[in] number_of_multipliers size of `multipliers` array
    \return #TsStatusCode
    \sa ts_haptic_get_master_multipliers
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_master_multipliers(TsDeviceHandle* dev,
        const TsHapticParamMultiplier* multipliers, uint64_t number_of_multipliers);

/*!
    \brief Creates a haptic playable object from an asset.

    A haptic asset should be preloaded using \ref asset.
    

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] haptic_asset handler to the preloaded haptic asset
    \param[in] is_looped makes a haptic playable object looped
    \param[out] playable_id haptic playable object ID
    \return #TsStatusCode
    \sa ts_haptic_play_playable, ts_haptic_remove_playable
*/
TS_API TsStatusCode ts_haptic_create_playable_from_asset(TsDeviceHandle* dev, TsAsset* haptic_asset,
        bool is_looped, uint64_t* playable_id);

/*!
    \brief Checks out if a haptic playable object exists in the haptic player.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id haptic playable object ID
    \param[out] is_exists haptic playable object exists
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_is_playable_exists(TsDeviceHandle* dev, uint64_t playable_id,
        bool* is_exists);

/*!
    \brief Plays a haptic playable object by an ID.

    Sets the playing state for a haptic playable.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id haptic playable object ID
    \return #TsStatusCode
    \sa ts_haptic_stop_playable
*/
TS_API TsStatusCode TS_CALL ts_haptic_play_playable(TsDeviceHandle* dev, uint64_t playable_id);

/*!
    \brief Instantly plays a haptic touch back with the provided parameters.

    Requires `channel_id` from mapping to play haptic. It can be obtained using \ref mapping.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] params touch parameters array
    \param[in] size size of `params` array
    \param[in] channels handler of channels array
    \param[in] number_of_channels size of `channels` array
    \param[in] duration touch duration in milliseconds
    \return #TsStatusCode
    \sa ts_haptic_create_touch, ts_haptic_stop_playable
*/

TS_API TsStatusCode TS_CALL ts_haptic_play_touch(TsDeviceHandle* dev, TsHapticParam* params,
        uint64_t size, const TsMapping2dBoneContent* channels,
        uint64_t number_of_channels, uint64_t duration);

/*!
    \brief Creates a haptic touch.

    Creates a haptic touch and gets `playable_id` for a future playback.
    Requires `channels` from mapping to play haptic. It can be obtained using \ref mapping.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] params touch parameters array
    \param[in] params_size size of `params` array
    \param[in] channels handler of channels array
    \param[in] number_of_channels the size of `channels` array
    \param[in] duration touch duration in milliseconds
    \param[out] playable_id ID of created touch playable
    \return #TsStatusCode
    \sa ts_haptic_play_touch, ts_haptic_stop_playable, ts_haptic_remove_playable
*/
TS_API TsStatusCode TS_CALL ts_haptic_create_touch(TsDeviceHandle* dev, TsHapticParam* params,
        uint64_t params_size, const TsMapping2dBoneContent* channels,
        uint64_t number_of_channels, uint64_t duration,
        uint64_t* playable_id);

/*!
    \brief Creates a haptic material asset.

    Creates a haptic material asset from touch_sequence and effect asset handlers and returns a new material asset handler.
    Touch sequence and effect asset instances will be cloned and can be used in a newly created material instance only.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] touch_sequence handler to a touch_sequence asset
    \param[in] effect handler to an effect asset
    \param[in] touch_version touch version used by the created asset
    \return #TsAsset
    \sa ts_haptic_create_playable_from_asset
*/
TS_API TsAsset* TS_CALL ts_haptic_create_material_asset(TsAsset* touch_sequence, TsAsset* effect);

/*!
    \brief Checks out if a haptic playable object is playing.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[out] is_playing is playing
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_is_playable_playing(TsDeviceHandle* dev, uint64_t playable_id,
        bool* is_playing);

/*!
    \brief Stops a haptic playable object.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_stop_playable(TsDeviceHandle* dev, uint64_t playable_id);

/*!
    \brief Removes a haptic playable object from the haptic player.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded playable haptic object
    \return #TsStatusCode
    \sa ts_haptic_create_playable_from_asset, ts_haptic_create_touch
*/
TS_API TsStatusCode TS_CALL ts_haptic_remove_playable(TsDeviceHandle* dev, uint64_t playable_id);

/*!
    \brief Checks out if a haptic playable object is paused.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[out] is_paused is paused
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_playable_paused(TsDeviceHandle* dev, uint64_t playable_id,
        bool* is_paused);

/*!
    \brief Sets the paused state for a haptic playable object.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[in] is_paused is paused
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_playable_paused(TsDeviceHandle* dev, uint64_t playable_id,
        bool is_paused);

/*!
    \brief Checks out if a haptic playable object is muted.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[out] is_muted is muted
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_playable_muted(TsDeviceHandle* dev, uint64_t playable_id,
        bool* is_muted);

/*!
    \brief Sets the muting state for a haptic playable object.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[in] is_muted is muted
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_playable_muted(TsDeviceHandle* dev, uint64_t playable_id,
        bool is_muted);

/*!
    \brief Checks out if a haptic playable object is looped.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[out] is_looped is looped
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_playable_looped(TsDeviceHandle* dev, uint64_t playable_id,
        bool* is_looped);

/*!
    \brief Sets a haptic playable object in a looped state.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[in] is_looped is looped
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_playable_looped(TsDeviceHandle* dev, uint64_t playable_id,
        bool is_looped);

/*!
    \brief Counts haptic playable multipliers.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded playable 
    \param[out] number_of_multipliers number of playable multipliers
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_number_of_playable_multipliers(TsDeviceHandle* dev,
        uint64_t playable_id, uint64_t* number_of_multipliers);

/*!
    \brief Gets haptic playable multipliers.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_haptic_get_number_of_playable_multipliers
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded playable
    \param[out] multipliers preallocated multipliers array
    \param[in] number_of_multipliers size of `multipliers` array
    \return #TsStatusCode
    \sa ts_haptic_get_number_of_playable_multipliers
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_playable_multipliers(TsDeviceHandle* dev, uint64_t playable_id,
        TsHapticParamMultiplier* multipliers, uint64_t number_of_multipliers);

/*!
    \brief Sets haptic playable multipliers.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id iD of the preloaded playable
    \param[in] multipliers multipliers array
    \param[in] number_of_multipliers size of `multipliers` array
    \return #TsStatusCode
    \sa ts_haptic_get_playable_multipliers
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_playable_multipliers(TsDeviceHandle* dev, uint64_t playable_id,
        const TsHapticParamMultiplier* multipliers, uint64_t number_of_multipliers);

/*!
    \brief Gets haptic playable object local playback time.

    Returns relative time since the playable object playback has started.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[out] local_time current playable object relative time in milliseconds
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_playable_local_time(TsDeviceHandle* dev, uint64_t playable_id,
        uint64_t* local_time);

/*!
    \brief Sets haptic playable object local playback time.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded haptic playable object
    \param[in] local_time playable relative time in milliseconds
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_playable_local_time(TsDeviceHandle* dev, uint64_t playable_id,
        uint64_t local_time);

/*!
    \brief Gets haptic playable duration.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] playable_id ID of the preloaded playable object
    \param[out] duration duration of playable in milliseconds
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_playable_duration(TsDeviceHandle* dev, uint64_t playable_id,
        uint64_t* duration);

/*!
    \brief Removes all haptic playable objects from the haptic player.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_clear_all_playables(TsDeviceHandle* dev);

/*!
    \brief Adds a channel to a dynamic haptic playable object.

    Adds a channel by `channel_id` from \ref mapping.
    A channel can be added to a dynamic haptic playable object that has no predefined channels for playback: `Touch`, `TouchSequence`, `HapticMaterial`.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] channel handler to a channel
    \param[in] playable_id ID of the preloaded haptic playable object
    \return #TsStatusCode
    \sa ts_haptic_remove_channel_from_dynamic_playable
*/
TS_API TsStatusCode TS_CALL ts_haptic_add_channel_to_dynamic_playable(TsDeviceHandle* dev,
        const TsMapping2dBoneContent channel,
        uint64_t playable_id);

/*!
    \brief Removes a channel from a dynamic haptic playable object.

    See also #ts_haptic_add_channel_to_dynamic_playable.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] channel handler to a channel
    \param[in] playable_id ID of the preloaded haptic playable object
    \return #TsStatusCode
    \sa ts_haptic_add_channel_to_dynamic_playable
*/
TS_API TsStatusCode TS_CALL ts_haptic_remove_channel_from_dynamic_playable(TsDeviceHandle* dev,
        const TsMapping2dBoneContent channel,
        uint64_t playable_id);

/*!
    \brief Sets channel impact for a haptic material.

    Sets channel impact with the value from 0 to 1 to a `HapticMaterial` playable.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] channel handler to a channel
    \param[in] impact impact value [0..1] for material
    \param[in] playable_id ID of the preloaded playable
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_material_channel_impact(TsDeviceHandle* dev,
        const TsMapping2dBoneContent channel, float impact,
        uint64_t playable_id);

/*!
    \brief Sets the Global Haptic Power parameter.

	Entered value should be [0 - 1], otherwise it will be clamped.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] value desired power value

    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_global_power(TsDeviceHandle* dev, float value);

/*!
    \brief Gets the Global Haptic Power parameter.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[out] value Current Global Haptic Power value

    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_get_global_power(TsDeviceHandle* dev, float* value);

/*!
    \brief Subscribe on multiplier change event.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] callback User's callback which will be called on event

    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_haptic_set_multiplier_change_callback(TsDeviceHandle* dev, void(*callback)());

/**@}*/

TS_EXTERN_C_END
