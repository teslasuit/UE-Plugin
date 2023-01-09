#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup glove Glove API
    The Glove module provides specific functions for TESLASUIT Glove operating.

    TESLASUIT Glove has magnetic encoders that can be used to capture the movement of the hand and fingers and manage for force feedback.
    To receive magnetic encoders position, subscribe to data update using #ts_glove_me_set_update_callback,
    then start data streaming using #ts_glove_me_start_streaming. Stop streaming using #ts_glove_me_stop_streaming.
 * @{
 */

/*!
    \brief Magnetic encoder id.

    Magnetic encoders are divided into two groups:
    - magnetic encoders that capture flexion of each finger;
    - magnetic encoders that capture abduction of each finger.
    Possible values:
    Flexion:
    - Thumb = 1
    - Index = 2
    - Middle = 3
    - Ring = 4
    - Pinky = 5

    Abduction:
    - Thumb = 6
    - Index = 7
    - Middle = 8
    - Ring = 9
    - Pinky = 10
*/
typedef unsigned long long TsMagneticEncoderId;

/*!
    \brief Force feedback servo id.

    Force feedback servomotors are attached to each finger.
    Possible values:
    - Thumb = 1
    - Index = 2
    - Middle = 3
    - Ring = 4
    - Pinky = 5
*/
typedef unsigned long long TsForceFeedbackId;

/*!
    \brief Magnetic encoder calibration pose.

    Using in magnetic encoder calibration procedure to adjust min and max values for flexion / abduction.
    Possible values:
    - FlexionUp = 1
    - FlexionDown = 2
    - AbductionLeft = 3
    - AbductionRight = 4
*/
typedef unsigned long long TsMagneticEncoderCalibrationPose;

typedef void const* const TsMagneticEncoderAngles;

#pragma pack(push,1)

/*!
    \brief Magnetic encoder data.

    Magnetic encoder data contains flexion and abduction rotation angles.
    Flexion range is [0, 4095] where 0 is a value of open finger, 4095 is a value for a closed finger.
    Abduction range is [0, 1000] where 0 is a maximum left position, 1000 - is a maximum right.
    \sa ts_glove_me_set_update_callback
*/
typedef struct TsMagneticEncoderData
{
    TsMagneticEncoderId encoder_id; ///< encoder identifier
    uint64_t angle; ///< relative angle of encoder
} TsMagneticEncoderData;

/*!
    \brief Force feedback servo control.

    Describes force feedback servomotor in the given relative angle.
    For information about angle values see \ref TsMagneticEncoderData description
    Struct has two reserved fields for a future functionality.
    \sa TsMagneticEncoderData, ts_glove_force_feedback_set_controls
*/
typedef struct TsForceFeedbackControl
{
    TsForceFeedbackId servo_id; ///< servo identifier
    int64_t angle; ///< absolute angle of servo
    uint64_t reserved_1; ///< reserved field
    uint64_t reserved_2; ///< reserved field
} TsForceFeedbackControl;

#pragma pack(pop)

/*!
    \brief Magnetic encoder data update callback.

    A callback will be called after subscribing and starting magnetic encoder streaming.
    Received data will contain 10 #TsMagneticEncoderData structs - one for each of #TsMagneticEncoderId.

    \param[in] dev handle to attached glove
    \param[in] data array of TsMagneticEncoderData struct
    \param[in] size size of data array
    \param[in] user_data opaque pointer for user data
    \sa ts_glove_me_set_update_callback, ts_glove_me_start_streaming, TsMagneticEncoderData
*/
typedef void(*TsMagneticEncoderDataUpdatedCallback)(TsDeviceHandle* dev, const TsMagneticEncoderData* data,
        uint64_t size, void* user_data);

typedef void(*TsMagneticEncoderAnglesUpdatedCallback)(TsDeviceHandle* device, TsMagneticEncoderAngles finger_data, void* user_data);

/*!
    \brief Subscribe to a magnetic encoder data updated event.

    Set callback should be called before starting data streaming.
    After start, a callback will be called when magnetic encoder position is updated.

    \pre #ts_initialize
    \param[in] dev handle to attached glove
    \param[in] callback callback that is called when magnetic encoder position is updated
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
    \sa ts_glove_me_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_glove_me_set_update_callback(TsDeviceHandle* dev,
    TsMagneticEncoderDataUpdatedCallback callback, void* user_data);

TS_API TsStatusCode TS_CALL ts_glove_set_angles_update_callback(TsDeviceHandle* device,
    TsMagneticEncoderAnglesUpdatedCallback callback, void* user_data);

/*!
    \brief Start magnetic encoder data streaming.

    Set callback function #ts_glove_me_set_update_callback should be used before start to receive data.

    \pre #ts_initialize
    \param[in] dev handle to attached glove
    \return #TsStatusCode
    \sa ts_glove_me_set_update_callback, ts_glove_me_stop_streaming
*/
TS_API TsStatusCode TS_CALL ts_glove_me_start_streaming(TsDeviceHandle* dev);

/*!
    \brief Stop magnetic encoder data streaming.

    \pre #ts_initialize
    \param[in] dev handle to attached glove
    \return #TsStatusCode
    \sa ts_glove_me_start_streaming
*/
TS_API TsStatusCode TS_CALL ts_glove_me_stop_streaming(TsDeviceHandle* dev);

/*!
    \brief Calibrate magnetic encoder by given calibration pose.

    \pre #ts_initialize
    \param[in] dev handle to attached glove
    \param[in] calibration_pose calibration pose type
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_glove_me_calibrate_by_pose(TsDeviceHandle* dev,
        const TsMagneticEncoderCalibrationPose calibration_pose);

/*!
    \brief Set force feedback servo controls.

    Fix force feedback servomotors in the given relative angle for specified servo ids.
    To release servomotors use #ts_glove_force_feedback_release_controls.

    \pre #ts_initialize
    \param[in] dev handle to attached glove
    \param[in] controls controls parameters array
    \param[in] size `controls` parameters array size
    \return #TsStatusCode
    \sa ts_glove_force_feedback_release_controls
*/
TS_API TsStatusCode TS_CALL ts_glove_force_feedback_set_controls(TsDeviceHandle* dev,
        const TsForceFeedbackControl* controls, uint64_t size);

/*!
    \brief Release force feedback.

    Release force feedback after set control with #ts_glove_force_feedback_set_controls.

    \pre #ts_initialize, #ts_glove_force_feedback_set_controls
    \param[in] dev handle to attached glove
    \param[in] servo_ids servo ids array
    \param[in] size `servo_ids` array size
    \return #TsStatusCode
    \sa ts_glove_force_feedback_set_controls
*/
TS_API TsStatusCode TS_CALL ts_glove_force_feedback_release_controls(TsDeviceHandle* dev,
        const TsForceFeedbackId* servo_ids, uint64_t size);

/*!
    \brief Get specified finger bone angle.

    Gets the value of finger bone angle./
    Bone angle value: [-90, 90]. Angle value -90 can be reached when finger is at it's maximum flexion up position.

    \pre #ts_initialize, #ts_glove_force_feedback_set_controls
    \param[in] angles_data handle to received data from callback
    \param[in] finger_bone index of specified bone needed
    \param[out] angle current value of specified bone angle
    \return #TsStatusCode
    \sa ts_glove_force_feedback_set_controls
*/
TS_API TsStatusCode TS_CALL ts_glove_get_finger_bone_angle(TsMagneticEncoderAngles angles_data, TsBoneIndex finger_bone, int64_t* angle);
/**@}*/

TS_EXTERN_C_END
