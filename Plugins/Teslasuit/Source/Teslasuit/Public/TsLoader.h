#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

/**
 * \addtogroup core
 * @{
 */

/*!
	\brief Manages opening and closing of Teslasuit C API library

	Class shouldn't be used directly.
	Class is used by #TsCore in order to manage Teslasuit C API library.
 */
class TESLASUIT_API TsLoader
{
public:
	/*!
		\brief Loader constructor.
	*/
	TsLoader();

	/*!
		\brief Loader destructor.

		Unloads library if it's loaded.
	*/
	~TsLoader();

	/*!
		\brief Loads Teslasuit C API library and stores library handle
	*/
	void Load();

	/*!
		\brief Unloads Teslasuit C API library
	*/
	void Unload();

	/*!
		\brief Returns whether the Teslasuit C API library is already loaded

		\return bool
	*/
	bool IsLoaded() const;

	/*!
		\brief Returns raw pointer to Teslasuit C API library

		\return void*
	*/
	void* GetLibHandle() const;

private:
	bool bIsLoaded = false;
	void* LibHandle = nullptr;
};

/**@}*/
