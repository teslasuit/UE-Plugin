#pragma once

#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/*! \mainpage Main Page
 * \section intro_section Introduction
 * TESLASUIT SDK API provides a set of modules for working with the key features of TESLASUIT 4.5.4, 4.5.5, 5.0, and TESLAGLOVE allowing the user to get information about connected devices,
 * control haptic feedback, capture motion data, and analyze biometry data.
 *
 * API is divided into multiple modules:
 * Module            | Description   | Link
 * ----------------- | ------------- | -------------
 * **Core**          | Core API provides the main functions being a start point for initialization. | \ref core
 * **Device**        | Device API provides information about TESLASUIT connected devices together with the main control funсtions. | \ref device
 * **Haptic**        | Haptic API provides functions for haptic playback control. | \ref haptic
 * **Mocap**         | Mocap API provides functions for mocap data streaming and recording. | \ref mocap
 * **Biometry**      | Biometry API provides functions for EMG, ECG, PPG data streaming and recording. | \ref biometry
 * **Asset**         | Asset API provides functions for asset management, such as loading and parsing asset files. | \ref asset
 * **Mapping**       | Mapping API provides functions for channel retrieving and sensor mapping for TESLASUIT devices. | \ref mapping
 * **Force feedback**| Force feedback API provides functions for force feedback control. | \ref force_feedback
 * **Types**         | This module contains common data types for different APIs. | \ref common
 *
 *
 * \section version_section Version and compatibility
 * The Core module contains the #ts_get_version function, which returns major, minor, and patch version numbers. The major version number is incremented if any backward incompatible changes are introduced to the public API, e.g. removing parts from the public API, reordering public struct members, etc. The minor version number is incremented if any backward compatible changes or new major features are introduced to the public API, e.g. adding a new public function or a new decoder. The patch version number is incremented for smaller changes, e.g. changing behavior in a previously unspecified situation.
 *
 * TESLASUIT SDK guarantees backward API and ABI compatibility for each library as long as its major version number is unchanged. This means that no public symbols will be removed or renamed. Types and names of the public struct members and values of public macros and enums will remain the same unless they are explicitly declared as not being a part of the public API. Documented behavior will not change.
 *
 * In other words, any correct program that works with a given TESLASUIT library should work as it is with any later library containing the same major version numbers. This applies both to rebuilding the program against new TESLASUIT versions and replacing the dynamic TESLASUIT library the program links against.
 *
 * However, new public symbols may be added and new members may be appended to public structs which size is not a part of the public ABI (most public structs in TESLASUIT). New macros and enum values may be added. Behavior in undocumented situations can change slightly and be documented.
 *
 * \section android_section Android specific
 * Android manifest should provide INTERNET permission and write to a file or create a directory permissions if #ts_initialize_with_path is invoked with a path requiring this.
 */

/**
 * \defgroup core Core API
    The Core API provides the main functions, such as initialization, deinitialization, getting API version.

    ##Getting started##

    To start working with TESLASUIT SDK:

    - 1. Go to [the Downloads page of the Developer portal](https://developer.teslasuit.io/downloads).
    - 2. In the SOFTWARE section, download and install the latest version of the TESLASUIT SDK. By default, the installer starts system services.
    - 3. Load c_api library from TESLASUIT Studio installation directory. For Windows, directory path can be found in registry `HKEY_LOCAL_MACHINE\SOFTWARE\Teslasuit\Studio` in variable `InstalledPath`.
    - 4. Call #ts_initialize or #ts_initialize_with_path function to load resources for a session scope and start internal processing threads.
 *    After initialization, you can use TESLASUIT API and work with modules(get info about connected TESLASUIT devices using \ref device,
    work with device modules - \ref haptic, \ref mocap, \ref biometry).
    - 5. To release resources correctly, finish internal processing threads and disconnect from services, call #ts_uninitialize function at the end of the session.

 * @{
 */

/*!
    \brief Retrieves SDK version, which includes major, minor and patch version numbers.

    The version can be used to determine if the current SDK is compatible with the application that uses it.
    The major version can be used to determine compatibility.

    \return #TsVersion
    \sa ts_initialize, ts_initialize_with_path
*/
TS_API TsVersion TS_CALL ts_get_version();

/*!
    \brief Initializes API, connects to services, creates an API client and a session.

    The initialization of API is required for most of SDK functions.
    At this step, SDK libraries are connecting to TESLASUIT services and creating helper objects.
    #TsStatusCode should return a good result, otherwise make sure that TESLASUIT services are running.
    Services should be running by default after SDK installation. In case they are stopped for some reason, they should be restarted at least with System account rights.
    For Android, use #ts_initialize.

    \return #TsStatusCode
    \sa ts_initialize_with_path, ts_uninitialize
*/

TS_API TsStatusCode TS_CALL ts_initialize();

/*!
    \brief Initializes API with custom directory path parameter. SDK can write any type of data there.

    The initialization of API is required for most of SDK functions.
    At this step, SDK libraries are connecting to TESLASUIT services and creating helper objects.
    #TsStatusCode should return a good result, otherwise make sure that TESLASUIT services are running.
    Services should be running by default after SDK installation. In case they are stopped for some reason, they should be restarted at least with System account rights.

    \param[in] data_directory path for SDK to write internal data
    \return #TsStatusCode
    \sa ts_initialize, ts_uninitialize
*/

TS_API TsStatusCode TS_CALL ts_initialize_with_path(const char* data_directory);

/*!
    \brief Deinitializes API, stops all threads. API client and session will be destroyed.

    This function releases resources, finishes internal processing threads, and disconnects from services. The function should be called at the end of the session.

    \pre #ts_initialize or #ts_initialize_with_path
    \sa ts_initialize
*/
TS_API void TS_CALL ts_uninitialize();

/*!
    \brief Gets text representation of the status code.

    Status code is a returned value of most API functions.
    Current method helps to convert status code to text.

    \return const char*
    \sa TsStatusCode
*/
TS_API const char* TS_CALL ts_get_status_code_message(TsStatusCode status_code);

/**@}*/

TS_EXTERN_C_END
