#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup asset Asset API
    The Asset module provides functions to load assets from a file on the disk or from a binary array of data, get information about a loaded asset,
    unload an asset from memory.
 * @{
 */

/*!
    \brief Loads an asset from a file.

    Loads an asset (.ts_asset) from a file by the given path, returns a handler to a loaded asset.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] asset_path path of *.ts_asset file
    \return #TsAsset
    \sa ts_asset_load_from_binary_data
*/
TS_API TsAsset* TS_CALL ts_asset_load_from_path(const char* asset_path);

/*!
    \brief Loads an asset from a byte array.

    Loads an asset from a byte array, returns a handler to a loaded asset.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] asset_binary_data byte array pointer
    \param[in] size size of a byte array
    \return #TsAsset
    \sa ts_asset_unload
*/
TS_API TsAsset* TS_CALL ts_asset_load_from_binary_data(const uint8_t* asset_binary_data, uint64_t size);

/*!
    \brief Gets the asset type.

    Returns the asset type by the given asset handler.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] asset handler to the loaded asset
    \param[out] asset_type type of the loaded asset
    \return #TsStatusCode
    \sa TsAssetType
*/
TS_API TsStatusCode TS_CALL ts_asset_get_type(TsAsset* asset, TsAssetType* asset_type);

/*!
    \brief Unloads an asset.

    Unloads and unregisters an asset by the given asset handler.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] asset handler to the loaded asset
    \sa ts_asset_load_from_binary_data
*/
TS_API void TS_CALL ts_asset_unload(TsAsset* asset);

/**@}*/

TS_EXTERN_C_END
