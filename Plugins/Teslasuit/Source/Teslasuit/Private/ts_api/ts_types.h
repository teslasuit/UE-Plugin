#pragma once

#include <stdint.h>

#if defined(_MSC_VER)
#  define TS_API_EXPORT __declspec(dllexport)
#  define TS_API_IMPORT __declspec(dllimport)
#  define TS_CALL __stdcall
#elif defined(__GNUC__) || defined(__clang__)
#  define TS_API_EXPORT __attribute__((visibility("default")))
#  define TS_API_IMPORT
#  define TS_CALL
#else
#  define TS_API_EXPORT
#  define TS_API_IMPORT
#  define TS_CALL
#endif

#ifdef teslasuit_api_EXPORTS
#  define TS_API TS_API_EXPORT
#else
#  define TS_API TS_API_IMPORT
#endif

#ifdef __cplusplus
#  define TS_EXTERN_C_BEGIN extern "C" {
#  define TS_EXTERN_C_END }
#else
#  define TS_EXTERN_C_BEGIN
#  define TS_EXTERN_C_END
#endif

TS_EXTERN_C_BEGIN

/**
 * \defgroup common Common Types
    Types and structures that are common for different API modules.
 * @{
 */

 /*!
    \brief Result value for most API functions.

    Possible values:
    - Good = 0U,
    - GoodNotInitialized,
    - GoodAlreadyInitialized,
    - GoodAlreadyExists,
    - GoodNothingTodo,
    - Bad = 0x80000000U,
    - InvalidArgument,
    - BadPointer,
    - BadAlreadyExists,
    - OutOfMemory,
    - NotInitialized,
    - BadCommand,
    - NotImplemented,
    - NotFound,
    - NotValid,
    - NotSupported,
    - BadState,
    - BadSize,
    - IpcFail,
    - SessionLimitExceeded,
    - ParseFail,
    - FileOpenFailed,
    - FileFlushFailed,
    - FileWriteFailed,
    - AccessDenied,
    - ServiceStartFailed,
    - NoDevice,
    - Unexpected
 */
typedef int TsStatusCode;

/*!
    \brief Bone index.
*/
typedef enum TsBoneIndex
{
    TsBoneIndex_Hips = 0,
    TsBoneIndex_LeftUpperLeg = 1,
    TsBoneIndex_RightUpperLeg = 2,
    TsBoneIndex_LeftLowerLeg = 3,
    TsBoneIndex_RightLowerLeg = 4,
    TsBoneIndex_LeftFoot = 5,
    TsBoneIndex_RightFoot = 6,
    TsBoneIndex_Spine = 7,
    TsBoneIndex_Chest = 8,
    TsBoneIndex_UpperSpine = 9,
    TsBoneIndex_Neck = 10,
    TsBoneIndex_Head = 11,
    TsBoneIndex_LeftShoulder = 12,
    TsBoneIndex_RightShoulder = 13,
    TsBoneIndex_LeftUpperArm = 14,
    TsBoneIndex_RightUpperArm = 15,
    TsBoneIndex_LeftLowerArm = 16,
    TsBoneIndex_RightLowerArm = 17,
    TsBoneIndex_LeftHand = 18,
    TsBoneIndex_RightHand = 19,
    TsBoneIndex_LeftThumbProximal = 20,
    TsBoneIndex_LeftThumbIntermediate = 21,
    TsBoneIndex_LeftThumbDistal = 22,
    TsBoneIndex_LeftIndexProximal = 23,
    TsBoneIndex_LeftIndexIntermediate = 24,
    TsBoneIndex_LeftIndexDistal = 25,
    TsBoneIndex_LeftMiddleProximal = 26,
    TsBoneIndex_LeftMiddleIntermediate = 27,
    TsBoneIndex_LeftMiddleDistal = 28,
    TsBoneIndex_LeftRingProximal = 29,
    TsBoneIndex_LeftRingIntermediate = 30,
    TsBoneIndex_LeftRingDistal = 31,
    TsBoneIndex_LeftLittleProximal = 32,
    TsBoneIndex_LeftLittleIntermediate = 33,
    TsBoneIndex_LeftLittleDistal = 34,
    TsBoneIndex_RightThumbProximal = 35,
    TsBoneIndex_RightThumbIntermediate = 36,
    TsBoneIndex_RightThumbDistal = 37,
    TsBoneIndex_RightIndexProximal = 38,
    TsBoneIndex_RightIndexIntermediate = 39,
    TsBoneIndex_RightIndexDistal = 40,
    TsBoneIndex_RightMiddleProximal = 41,
    TsBoneIndex_RightMiddleIntermediate = 42,
    TsBoneIndex_RightMiddleDistal = 43,
    TsBoneIndex_RightRingProximal = 44,
    TsBoneIndex_RightRingIntermediate = 45,
    TsBoneIndex_RightRingDistal = 46,
    TsBoneIndex_RightLittleProximal = 47,
    TsBoneIndex_RightLittleIntermediate = 48,
    TsBoneIndex_RightLittleDistal = 49,
    TsBoneIndex_BonesCount = 50
} TsBoneIndex;

/*!
    \brief Type of TS product.
*/
typedef enum TsProductType
{
    TsProductType_Undefined = 0,
    TsProductType_Suit = 1,
    TsProductType_Glove = 2
} TsProductType;

/*!
    \brief Side of TS device. Can be Undefined.
*/
typedef enum TsDeviceSide
{
    TsDeviceSide_Undefined = 0,
    TsDeviceSide_Right = 1,
    TsDeviceSide_Left = 2
} TsDeviceSide;

#pragma pack(push,1)

/*!
    \brief Version struct.

    Contains major, minor, patch, and build versions. The major version changes can cause incompatible changes.
*/
typedef struct TsVersion
{
    uint32_t major; ///< incompatible changes
    uint32_t minor; ///< compatible changes
    uint32_t patch; ///< patch changes
    uint32_t build; ///< build id
} TsVersion;

/*
    \brief Teslasuit device currently attached to the system.

    Device is represented by unique identifier, that assigned to hardware device.
 */
typedef struct TsDevice
{
    uint8_t uuid[16];
} TsDevice;

#pragma pack(pop)

/*
    \brief Handler to attached Teslasuit device.

    Use this handler to specify the device for an operation.
*/
typedef struct TsDeviceHandle TsDeviceHandle;

/*!
    \brief Types of device events
*/
typedef enum TsDeviceEvent
{
    /** A device has been connected and is ready to use. */
    TsDeviceEvent_DeviceAttached = 1,
    /** A device has been disconnected and is no longer available.
    * It is the user's responsibility to call ts_device_close on any handler associated with a disconnected device. */
    TsDeviceEvent_DeviceDetached = 2
} TsDeviceEvent;

/*!
    \brief Types of device event policy
*/
typedef enum TsDeviceEventPolicy
{
    /** Set the callback and fire it for all currently attached devices. */
    TsDeviceEventPolicy_Enumerate = 1
} TsDeviceEventPolicy;

/*!
    \brief Type of device event callback

    \param[in] device device the event occurred on. See #TsDevice
    \param[in] event event occurred. #TsDeviceEvent
    \param[in] user_data user data provided once the callback is registered.
    \sa ts_set_device_event_callback
*/
typedef void(*TsDeviceEventCallback)(const TsDevice* dev, TsDeviceEvent event, void* user_data);

/*!
 \brief Asset type.

 Possible values:
 - Undefined = 0,
 - Spline = 1,
 - HapticEffect = 2,
 - Material = 3,
 - TouchSequence = 4,
 - PresetAnimation = 5,
 - SceneAnimation = 6
*/
typedef unsigned int TsAssetType;

/*
   \brief Handler to loaded asset.
*/
typedef struct TsAsset TsAsset;

/*
    \brief Handler to bone content.
*/
typedef void* TsMapping2dBoneContent;

/*!
    \brief Mapping version.

    Possible values:
    - Undefined = 0,
    - Mapping_4_5_4 = 1,
    - Mapping_4_5_5 = 2,
    - Mapping_4_6_0 = 3,
    - MappingLeftGlove_1_0_0 = 4,
    - MappingRightGlove_1_0_0 = 5,
    - Mapping_4_5_4_Legacy = 6,
    - Mapping_4_5_5_Legacy = 7,
    - Mapping_5_0_0 = 8,
    - MappingLeftGlove_1_2_0 = 9,
    - MappingRightGlove_1_2_0 = 10,
    - Mapping_5_0_1 = 11,
    - Mapping_5_0_2 = 12,
    - Mapping_5_0_3 = 13,
    - Mapping_4_7_0 = 14,
    - MappingLeftGlove_1_3_0 = 15,
    - MappingRightGlove_1_3_0 = 16,
    - Mapping_4_X_Medical = 17,
    - Mapping_4_5_6 = 18
*/
typedef unsigned char TsMapping2dVersion;

/*!
    \brief Type of sensors layout in mapping.

    Possible values:
    - Undefined = 0,
    - Electric = 1,
    - Temperature = 2,
    - Vibration = 3,
    - Emg = 4,
    - Ecg = 5
*/
typedef unsigned char TsLayout2dType;

/*!
    \brief Layout element type.

    Possible values:
    - Undefined = 0,
    - Cell = 1,
    - Channel = 2
*/
typedef unsigned char TsLayout2dElementType;

/*!
    \brief Bone side.

    Possible values:
    - Undefined = 0,
    - Front = 1,
    - Back = 2
*/
typedef unsigned char TsBone2dSide;

/*
    \brief Handler to mapping bone data
*/
typedef void* TsMapping2dBone;

/*
    \brief Handler to mapping2d object
*/
typedef void const* TsMapping2d;

/*
    \brief Handler to layout object
 */
typedef void* TsLayout2d;

#pragma pack(push,1)
/*!
    \brief Vector 2D float.

    Represents a point in 2d space.
*/
typedef struct TsVec2f
{
    float x;
    float y;
} TsVec2f;

/*!
     \brief Vector 3D float.

     Represents a point in 3D space.
 */
typedef struct TsVec3f
{
    float x;
    float y;
    float z;
} TsVec3f;

/*!
    \brief Quaternion float.

    Represents an object rotation in 3D space.
*/
typedef struct TsQuat
{
    float w;
    float x;
    float y;
    float z;
} TsQuat;

/*!
    \brief Skeleton bone data.

    Represents a skeleton bone with position and rotation.
*/
typedef struct TsMocapBone
{
    TsVec3f position;
    TsQuat  rotation;
} TsMocapBone;

/*!
    \brief Mocap sensor raw data.

    Structure of raw sensor data includes 9x quaternion, 6x quaternion,
    accelerometer, gyroscope, magnetometer, linear accelerometer, timestamp of data capture.
*/
typedef struct TsMocapSensor
{
    TsQuat quat9x;
    TsQuat quat6x;
    TsVec3f accel;
    TsVec3f gyro;
    TsVec3f magn;
    TsVec3f linear_accel;
    uint64_t timestamp;
} TsMocapSensor;

#pragma pack(pop)

/*
    \brief Handler to skeleton data.
 */
typedef void const* TsMocapSkeleton;

/*
   \brief Handler to mocap sensors raw data.
*/
typedef void const* TsMocapSensorSkeleton;

/*!
    \brief Mocap skeleton update callback.

    The callback is called after subscribing and starting mocap streaming.
    Received skeleton can be parsed by bones with #ts_mocap_skeleton_get_bone.

    \param[in] dev handler to the attached device
    \param[in] skeleton handler to skeleton data
    \param[in] user_data opaque pointer for user data
    \sa ts_mocap_set_skeleton_update_callback, TsMocapSkeleton, ts_mocap_skeleton_get_bone
*/
typedef void(*TsMocapSkeletonCallback)(TsDeviceHandle* dev, TsMocapSkeleton skeleton, void* user_data);

/*!
    \brief Update callback for mocap sensor raw data.

    The callback is called after subscribing and starting mocap streaming.
    Received skeleton can be parsed by bones with #ts_mocap_sensor_skeletone_get_bone.

    \param[in] dev handler to the attached device
    \param[in] skeleton handler to raw mocap data
    \param[in] user_data opaque pointer for user data
    \sa ts_mocap_set_sensor_skeleton_update_callback, TsMocapSensorSkeleton, ts_mocap_sensor_skeletone_get_bone
*/
typedef void(*TsMocapSensorSkeletonCallback)(TsDeviceHandle* dev, TsMocapSensorSkeleton skeleton, void* user_data);

/*!
    \brief Force feedback lock direction.

    A direction value that corresponds for what side will be limited to move by servomotor.

    \sa TsForceFeedbackConfig
*/
typedef enum TsForceFeedbackLockDirection
{
    TsForceFeedbackLockDirection_Up = 1,
    TsForceFeedbackLockDirection_Down = 2,
    TsForceFeedbackLockDirection_Both = 3
} TsForceFeedbackLockDirection;

#pragma pack(push,1)

/*!
    \brief Force feedback config struct.

    Describes servomotor force feedback control by `bone` index with the given `angle` in degrees and its direction.

    \sa TsForceFeedbackLockDirection, ts_force_feedback_enable
*/
typedef struct TsForceFeedbackConfig
{
    TsBoneIndex bone;
    float angle;
    uint8_t hardness_percent;
    TsForceFeedbackLockDirection lock_direction;
} TsForceFeedbackConfig;
#pragma pack(pop)

/*
   \brief Handler to Force Feedback position container.
*/
typedef const void* const TsForceFeedbackPositionContainer;

/*!
    \brief Force Feedback position update callback.

    A callback will be called after subscribing and starting position streaming.
    Received container can be parsed by bones with #ts_force_feedback_get_flexion_angle
    and #ts_force_feedback_get_abduction_angle

    \param[in] dev handler to attached glove
    \param[in] container handler to position container
    \param[in] user_data opaque pointer for user data
    \sa ts_force_feedback_set_position_update_callback, TsForceFeedbackPositionContainer
*/
typedef void(*TsForceFeedbackPositionUpdatedCallback)(TsDeviceHandle* dev,
    TsForceFeedbackPositionContainer container, void* user_data);

/*!
 \brief Haptic parameter type.

 Possible values:
 - Undefined = 0,
 - Period = 1,
 - Amplitude = 2,
 - PulseWidth = 3,
 - Temperature = 4
*/
typedef unsigned int TsHapticParamType;

/*!
    \brief Haptic parameter value.
*/
typedef unsigned long long TsHapticParamValue;

#pragma pack(push,1)

/*!
    \brief Haptic parameter struct.
*/
typedef struct TsHapticParam
{
    TsHapticParamType type;
    TsHapticParamValue value;
} TsHapticParam;

/*!
    \brief Haptic parameter multiplier struct.
*/
typedef struct TsHapticParamMultiplier
{
    TsHapticParamType type;
    float value;
} TsHapticParamMultiplier;

#pragma pack(pop)

#pragma pack(push,1)

/*!
 \brief EMG options
*/
typedef struct TsEmgOptions
{
    uint32_t lower_bandwidth;
    uint32_t upper_bandwidth;
    uint32_t sampling_frequency;
    uint8_t sample_size;
} TsEmgOptions;

/*!
 \brief Complex integer value representation.
*/
typedef struct TsComplex
{
    int real_value;
    int im_value;
} TsComplex;

typedef struct TsHrv
{
    float mean_rr;
    float sdnn;
    float sdsd;
    float rmssd;
    float sd1;
    float sd2;
    float counted_hlf;
} TsHrv;

#pragma pack(pop)

/*
   \brief Handler to EMG data.
*/
typedef void const* TsEmgData;

/*
   \brief Handler to HRV data.
*/
typedef void const* TsHrvData;

/*
   \brief Handler to PPG data.
*/
typedef void const* TsPpgData;

/*
   \brief Handler to Raw PPG data.
*/
typedef void const* TsRawPpgData;

/*
   \brief Handler to temperature data.
*/
typedef void const* TsTemperatureData;

/*
   \brief Handler to BIA data.
*/
typedef void const* TsBiaData;

/*!
    \brief EMG data update callback.

    A callback will be called after subscribing and starting EMG streaming.
    Received EMG data can be parsed with #ts_emg_get_channel_data.

    \param[in] dev handle to attached device
    \param[in] emg_data handle to EMG data
    \param[in] user_data opaque pointer for user data
    \sa ts_emg_set_update_callback, ts_emg_get_channel_data
*/
typedef void(*TsEmgUpdatedCallback)(TsDeviceHandle* dev, const TsEmgData emg_data, void* user_data);

/*!
    \brief PPG HRV data update callback.

    A callback will be called after subscribing and starting PPG streaming.
    Received HRV data can be parsed with #ts_hrv_get_data.

    \param[in] dev handle to attached device
    \param[in] hrv_data handle to HRV data
    \param[in] user_data opaque pointer for user data
    \sa ts_hrv_set_update_callback, ts_hrv_get_data
*/
typedef void(*TsHrvUpdatedCallback)(TsDeviceHandle* dev, const TsHrvData hrv_data, void* user_data);

/*!
    \brief Processed PPG data update callback.

    A callback will be called after subscribing and starting PPG streaming.
    Received processed PPG data can be parsed with #ts_ppg_get_heart_rate and #ts_ppg_get_oxygen_percent.

    \param[in] dev handle to attached device
    \param[in] ppg_data handle to processed PPG data
    \param[in] user_data opaque pointer for user data
    \sa ts_ppg_set_update_callback, ts_ppg_get_heart_rate, ts_ppg_get_oxygen_percent
*/
typedef void(*TsPpgUpdatedCallback)(TsDeviceHandle* dev, const TsPpgData ppg_data, void* user_data);

/*!
    \brief Raw PPG data update callback.

    A callback will be called after subscribing and starting raw PPG streaming.
    Received processed PPG data can be parsed with #ts_ppg_raw_get_infrared_data, #ts_ppg_raw_get_red_data,
    #ts_ppg_raw_get_blue_data, #ts_ppg_raw_get_green_data, #ts_ppg_raw_get_ambient_light_covf, #ts_ppg_raw_get_proximity

    \param[in] dev handle to attached device
    \param[in] raw_ppg_data handle to raw PPG data
    \param[in] user_data opaque pointer for user data
    \sa ts_ppg_raw_set_update_callback, ts_ppg_raw_get_infrared_data, ts_ppg_raw_get_red_data
*/
typedef void(*TsRawPpgUpdatedCallback)(TsDeviceHandle* dev, const TsRawPpgData raw_ppg_data, void* user_data);

/*!
    \brief Temperature data update callback.

    A callback will be called after subscribing and starting temperature streaming.
    Received temperature data can be parsed with #ts_temperature_get_value.

    \param[in] dev handle to attached device
    \param[in] temperature_data handle to temperature data
    \param[in] user_data opaque pointer for user data
    \sa ts_temperature_set_update_callback, ts_temperature_get_value
*/
typedef void(*TsTemperatureUpdatedCallback)(TsDeviceHandle* dev, const TsTemperatureData temperature_data, void* user_data);

/*!
    \brief BIA data update callback.

    A callback will be called after subscribing and starting BIA streaming.
    Received BIA data can be parsed with #ts_bia_get_channel_frequency_complex_value.

    \param[in] dev handle to attached device
    \param[in] bia_data handle to BIA data
    \param[in] user_data opaque pointer for user data
    \sa ts_bia_set_update_callback, ts_bia_get_channel_frequency_complex_value
*/
typedef void(*TsBiaUpdatedCallback)(TsDeviceHandle* dev, const TsBiaData bia_data, void* user_data);


/**@}*/

TS_EXTERN_C_END
