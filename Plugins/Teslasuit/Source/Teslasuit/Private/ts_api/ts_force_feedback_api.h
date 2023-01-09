#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup force_feedback Force Feedback API

    Force Feedback API can be used to capture the movement of the hand and fingers and manage for force feedback.
    To receive position, subscribe to data update using #ts_force_feedback_set_position_update_callback,
    then start data streaming using #ts_force_feedback_start_position_streaming. To stop streaming use #ts_force_feedback_stop_position_streaming.
 * @{
 */

/*!
    \brief Enables force feedback.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to attached device
    \param[in] configs config parameters array
    \param[in] size `configs` parameters array size
    \return #TsStatusCode
    \sa ts_force_feedback_disable
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_enable(TsDeviceHandle* dev,
    const TsForceFeedbackConfig* configs, uint64_t size);

/*!
    \brief Disable force feedback.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_force_feedback_enable
    \param[in] dev handler to attached glove
    \param[in] bones bone array
    \param[in] size `bones` array size
    \return #TsStatusCode
    \sa ts_force_feedback_enable
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_disable(TsDeviceHandle* dev,
    const TsBoneIndex* bones, uint64_t size);

/*!
    \brief Sets position updated callback.

    A provided callback will be called when position is updated.
    After a callback was set, streaming can be started with #ts_force_feedback_start_position_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to attached device
    \param[in] callback #TsForceFeedbackPositionUpdatedCallback
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa TsForceFeedbackPositionUpdatedCallback, ts_force_feedback_start_position_streaming
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_set_position_update_callback(TsDeviceHandle* dev,
    TsForceFeedbackPositionUpdatedCallback callback, void* user_data);

/*!
    \brief Starts magnetic encoder data streaming.

    Sets callback function #ts_force_feedback_set_position_update_callback which should be used before start to receive data.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to attached device
    \return #TsStatusCode
    \sa ts_force_feedback_set_position_update_callback, ts_force_feedback_stop_position_streaming
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_start_position_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops magnetic encoder data streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to attached device
    \return #TsStatusCode
    \sa ts_force_feedback_start_position_streaming
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_stop_position_streaming(TsDeviceHandle* dev);

/*!
    \brief Retrieves flexion angle for a bone by index.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_force_feedback_start_position_streaming
    \param[in] container handler to position container
    \param[in] index bone index to receive data from
    \param[in] angle angle in degrees
    \return #TsStatusCode
    \sa TsBoneIndex
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_get_flexion_angle(TsForceFeedbackPositionContainer container,
    TsBoneIndex index, float* angle);

/*!
    \brief Retrieves abduction angle for a bone by index.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_force_feedback_start_position_streaming
    \param[in] container handler to position container
    \param[in] index bone index to receive data from
    \param[in] angle angle in degrees
    \return #TsStatusCode
    \sa TsBoneIndex
*/
TS_API TsStatusCode TS_CALL ts_force_feedback_get_abduction_angle(TsForceFeedbackPositionContainer container,
    TsBoneIndex index, float* angle);

/**@}*/

TS_EXTERN_C_END
