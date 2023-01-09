#pragma once

#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup mocap Mocap API
    The Mocap module provides functions to receive raw data from IMU sensors and processed data in a form of #TsMocapSensorSkeleton and #TsMocapSkeleton.
    Raw data are received in a form of an opaque pointer to data, which can be used with a special function to extract inner fields of data.

    To start with, subscribe to data update, then begin streaming. After the start, data updates are received in a registered callback.
    The #ts_mocap_stop_streaming function should be called to stop streaming.
 * @{
 */

/*!
    \brief Sets skeleton update callback.

    The provided callback is called once mocap skeleton is updated.
    After the callback is set, streaming can be started with #ts_mocap_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] callback #TsMocapSkeletonCallback
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa TsMocapSkeletonCallback, ts_mocap_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_mocap_set_skeleton_update_callback(TsDeviceHandle* dev,
    TsMocapSkeletonCallback callback, void* user_data);

/*!
    \brief Sets skeleton update callback.

    The provided callback is called once raw sensor data are updated.
    After the callback is set, streaming can be started with #ts_mocap_start_streaming.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[in] callback #TsMocapSensorSkeletonCallback
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa TsMocapSensorSkeletonCallback, ts_mocap_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_mocap_set_sensor_skeleton_update_callback(TsDeviceHandle* dev,
    TsMocapSensorSkeletonCallback callback, void* user_data);

/*!
    \brief Starts mocap streaming for a provided device handler.

    Before streaming, use #ts_mocap_set_skeleton_update_callback or #ts_mocap_set_sensor_skeleton_update_callback
    to register a callback for receiving skeleton data or raw data updates.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \return #TsStatusCode
    \sa ts_mocap_stop_streaming
*/
TS_API TsStatusCode TS_CALL ts_mocap_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stops mocap streaming for a provided device handler.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mocap_start_streaming
    \param[in] dev handler to the attached device
    \return #TsStatusCode
    \sa ts_mocap_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_mocap_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief Calibrates mocap skeleton model.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mocap_start_streaming
    \param[in] dev handler to the attached device
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mocap_skeleton_calibrate(TsDeviceHandle* dev);

/*!
    \brief Retrieves mocap skeleton data for a bone by index.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mocap_start_streaming
    \param[in] skeleton handler to raw mocap data
    \param[in] index bone index to receive data from
    \param[in] bone mocap bone data
    \return #TsStatusCode
    \sa TsBoneIndex
*/
TS_API TsStatusCode TS_CALL ts_mocap_skeleton_get_bone(const TsMocapSkeleton skeleton, TsBoneIndex index, TsMocapBone* bone);

/*!
    \brief Retrieves mocap raw data for a bone by index.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mocap_start_streaming
    \param[in] skeleton handler to raw mocap data
    \param[in] index bone index to receive data from
    \param[in] bone raw mocap bone data
    \return #TsStatusCode
    \sa TsBoneIndex
*/
TS_API TsStatusCode TS_CALL ts_mocap_sensor_skeleton_get_bone(const TsMocapSensorSkeleton skeleton, TsBoneIndex index, TsMocapSensor* bone);

/**@}*/

TS_EXTERN_C_END
