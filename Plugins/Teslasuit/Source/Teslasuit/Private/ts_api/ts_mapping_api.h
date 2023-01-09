#pragma once
#include <ts_api/ts_types.h>

TS_EXTERN_C_BEGIN

/**
 * \defgroup mapping Mapping API
    Mapping represents a set of device's elements mapped on 2d space.
    Elements are described by the 2D Polygon - an array of points.
    Elements are bound to bones, a full set of bones is included in a layout, multiple layouts with the same element types are contained in an array,
    an array of layouts with same type are packed by #TsLayout2dType and #TsLayout2dElementType.
    Mappings might have different versions. Mapping can be requested by a mapping version or by a device handler because each device has
    a bound mapping version by default.

    For example, a path to get shapes of all electric haptic channels would be:
    - #ts_mapping2d_get_by_device for attached device
    - #ts_mapping2d_get_number_of_layouts for device mapping
    - #ts_mapping2d_get_layouts with preallocated array of received number of layouts
    - check is received array contains #TsLayout2dType == Electric and #TsLayout2dElementType == Channel
    - #ts_mapping2d_layout_get_number_of_bones for layout with #TsLayout2dType == Electric and #TsLayout2dElementType == Channel
    - #ts_mapping2d_layout_get_bones with preallocated array of received number of bones
    - for each bone handler #ts_mapping2d_bone_get_number_of_contents
    - #ts_mapping2d_bone_get_contents
    - for each bone content #ts_mapping2d_bone_content_get_number_of_points
    - #ts_mapping2d_bone_content_get_points with preallocated array of received number of points
 * @{
 */

/*!
    \brief Get default mapping2d handler for a device.

    Requires handler to an attached device.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] dev handler to the attached device
    \param[out] mapping pointer to mapping object in memory
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_get_by_device(TsDeviceHandle* dev, TsMapping2d* mapping);

/*!
    \brief Gets mapping2d handler by the mapping version.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] version mapping version
    \param[out] mapping pointer to mapping object in memory
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_get_by_version(TsMapping2dVersion version, TsMapping2d* mapping);

/*!
    \brief Gets mapping2d layouts number.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] mapping pointer to mapping object in memory
    \param[out] number_of_layouts number of layouts
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_get_number_of_layouts(const TsMapping2d mapping, uint64_t* number_of_layouts);

/*!
    \brief Gets mapping2d layouts.

    Fills in preallocated memory `layouts` with size `number_of_layouts`.\n
    to get `number_of_layouts` use #ts_mapping2d_get_number_of_layouts

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] mapping pointer to mapping object in memory
    \param[out] layouts handles to layouts
    \param[in] number_of_layouts size of preallocated memory
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_get_layouts(const TsMapping2d mapping, TsLayout2d* layouts,
        uint64_t number_of_layouts);

/*!
    \brief Gets mapping2d layout index.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] layout handler to layout object in memory
    \param[out] layout_index index of specified layout
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_layout_get_index(TsLayout2d layout, uint8_t* layout_index);

/*!
    \brief Gets mapping2d layout type.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] layout handler to layout object in memory
    \param[out] layout_type index of specified layout
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_layout_get_type(const TsLayout2d layout, TsLayout2dType* layout_type);

/*!
    \brief Gets mapping2d layout element type.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_get_layouts
    \param[in] layout handler to layout object in memory
    \param[out] element_type type of layout element type
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_layout_get_element_type(const TsLayout2d layout,
        TsLayout2dElementType* element_type);

/*!
    \brief Gets mapping2d layout bones number.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_get_layouts
    \param[in] layout handler to layout object
    \param[out] number_of_bones number of bones in layout
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_layout_get_number_of_bones(const TsLayout2d layout, uint64_t* number_of_bones);

/*!
    \brief Gets mapping2d bones from provided layout.

    Receives possible pointers to bones, that can be used to get corresponding bone content such as cells and channels.
    Function fills preallocated array `bone_ids` with `size`.
    To allocate correct array `bone_ids` should be used #ts_mapping2d_layout_get_number_of_bones.

    \pre #ts_initialize or #ts_initialize_with_path
    \param[in] layout handler to layout object in memory
    \param[out] bones pointers to bones
    \param[in] number_of_bones size of `bone` array
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_layout_get_bones(const TsLayout2d layout, TsMapping2dBone* bones,
        uint64_t number_of_bones);

/*!
    \brief Gets bone index from passed bone object.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_layout_get_bones
    \param[in] bone pointer to bone object in memory
    \param[out] bone_index index of bone
    \return #TsStatusCode
    \sa ts_mapping2d_layout_get_bones
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_bone_get_index(const TsMapping2dBone bone, TsBoneIndex* bone_index);

/*!
    \brief Gets bone side from passed bone object.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_layout_get_bones
    \param[in] bone pointer to bone object in memory
    \param[out] bone_side side of bone
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_bone_get_side(const TsMapping2dBone bone, TsBone2dSide* bone_side);

/*!
    \brief Gets mapping2d layout bone contents number.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_layout_get_bones
    \param[in] bone pointer to bone object in memory
    \param[out] number_of_contents layout bone contents size
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_bone_get_number_of_contents(const TsMapping2dBone bone,
        uint64_t* number_of_contents);

/*!
    \brief Gets mapping2d layout bone content objects.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_bone_get_number_of_contents
    \param[in] bone pointer to bone object in memory
    \param[out] bone_contents bone contents array of objects
    \param[in] number_of_bone_contents size of `bone_contents` array
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_bone_get_contents(const TsMapping2dBone bone,
        TsMapping2dBoneContent* bone_contents,
        uint64_t number_of_bone_contents);

/*!
    \brief Gets number of mapping2d bone content shape points.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_bone_get_contents
    \param[in] bone_content pointer to bone content object in memory
    \param[out] number_of_points number of bone content points
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_bone_content_get_number_of_points(const TsMapping2dBoneContent bone_content,
        uint64_t* number_of_points);

/*!
    \brief Gets mapping2d bone content shape points.

    Points represent a shape of bone content element in 2d space.

    \pre #ts_initialize or #ts_initialize_with_path, #ts_mapping2d_bone_content_get_number_of_points
    \param[in] bone_content pointer to bone content object in memory
    \param[out] points layout bone content points
    \param[in] number_of_points size of `points` array
    \return #TsStatusCode
*/
TS_API TsStatusCode TS_CALL ts_mapping2d_bone_content_get_points(const TsMapping2dBoneContent bone_content, TsVec2f* points,
        uint64_t number_of_points);

/**@}*/

TS_EXTERN_C_END
