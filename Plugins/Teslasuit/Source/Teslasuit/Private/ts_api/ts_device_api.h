#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup device Device API
    The Device module provides functions to connect and subscribe to connections and disconnections of TESLASUIT devices.
    It also provides functions for retrieving device information and the main device control functions.

    The start point for Device API is to receive a number of attached devices using #ts_get_device_list,
    then receive a handler for each attached device using #ts_device_open.
    These device handlers can be applied to retrieve device information and can be used with other API functions for a certain device.
    To keep tracking attached devices, #ts_get_device_list should be called periodically.
 * @{
 */

/*!
    \brief Retrieves a list of Teslasuit devices currently attached to the system.
    
    To get the list of devices, `list` should be preallocated with an expected number of devices, with
    `list` and its size passed to the function.
    This function fills `list` with attached devices but no more than `list_size`.
    The function changes `list_size` to the number of attached devices, if it is less than `list_size` passed.
    To keep tracking attached devices, #ts_get_device_list should be called periodically.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[out] list pointer to the preallocated array to be filled with the attached devices
    \param[in,out] list_size input is a size of the preallocated `list`, output is a number of attached devices
    \return #TsStatusCode
    \sa ts_device_open
*/
TS_API TsStatusCode TS_CALL ts_get_device_list(TsDevice* list, uint32_t* list_size);

/*!
    \brief Sets device event callback.
    
    The callback fires once an event occurs on a device.
    The callback may be called by an internal event thread and as such, it is
    recommended the callback does minimal processing before returning.
    
    \pre #ts_initialize
    \param[in] policy #TsDeviceEventPolicy
    \param[in] callback #TsDeviceEventCallback
    \param[in] user_data opaque pointer for user data
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_set_device_event_callback(TsDeviceEventPolicy policy,
    TsDeviceEventCallback callback, void* user_data);

/*!
    \brief Obtains a device handler using a device identifier.
    
    Obtains a device handler by the device identifier received in #ts_get_device_list.
    The device handler should be used for all operations with the corresponding device.
    All open device handlers must be closed with #ts_device_close.
    Returns null if the device became unavailable.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_get_device_list
    \param[in] device device identifier
    \return #TsDeviceHandle
    \sa ts_device_close, ts_device_get_name
*/
TS_API TsDeviceHandle* TS_CALL ts_device_open(const TsDevice* device);

/*!
    \brief Closes a device handler.
    
    All open device handlers must be closed with this method.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_device_open
    \param[in] dev device handler
    \sa ts_device_open
*/
TS_API void TS_CALL ts_device_close(TsDeviceHandle* dev);

/*!
    \brief Obtains a device identifier by a device handler.

    The device identifier is valid at least as long as the device handler.

    \pre #ts_initialize, #ts_device_open
    \param[in] dev device handler
    \return const TsDevice*
*/
TS_API const TsDevice* TS_CALL ts_device_get_id(TsDeviceHandle* dev);

/*!
    \brief Returns a device name.
    
    Returns a device name, which corresponds to SSID by default.
    The name is represented by a null-terminated string.
    The string is valid at least as long as the device handler.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_device_open
    \param[in] dev device handler
    \return const char*
*/
TS_API const char* TS_CALL ts_device_get_name(TsDeviceHandle* dev);

/*!
    \brief Returns a device serial number.
    
    Returns a device serial number represented by a null-terminated string.
    The string is valid at least as long as the device handler.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_device_open
    \param[in] dev device handler
    \return const char*
*/
TS_API const char* TS_CALL ts_device_get_serial(TsDeviceHandle* dev);

/*!
    \brief Returns a device product type.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_device_open
    \param[in] dev device handler
    \return #TsProductType
*/
TS_API TsProductType TS_CALL ts_device_get_product_type(TsDeviceHandle* dev);

/*!
    \brief Returns device side for devices that have it. Otherwise, returns Undefined.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_device_open
    \param[in] dev device handler
    \return #TsDeviceSide
*/
TS_API TsDeviceSide TS_CALL ts_device_get_device_side(TsDeviceHandle* dev);

/**@}*/

TS_EXTERN_C_END
