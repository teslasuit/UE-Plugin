#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "TsLoader.h"

/**
 * \addtogroup core
 * @{
 */

/*!
	\brief Manages loading of Teslasuit library and core C API initialization.

	Class shouldn't be used directly.
	#FTeslasuitModule creates an instance of this class in order to load
	Teslasuit C API library and initialize C API as required.
*/
class TESLASUIT_API TsCore
{
public:
	/*!
		\brief Core constructor.
	*/
	TsCore();

	/*!
		\brief Core destructor.
	*/
	~TsCore();

	/*!
		\brief Loads Teslasuit C API library and initializes Teslasuit API.
	*/
	void Initialize();

	/*!
		\brief Returns raw pointer to the Teslasuit library.
	*/
	void* GetLibHandle() const;

	/*!
		\brief Deinitializes Teslasuit API and unloads the library.
	*/
	void Uninitialize();

private:
	TsLoader Loader;
};

/**@}*/
