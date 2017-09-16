#include "Blackhart.h"

#include "pil\__BkGraphicsAPI.h"
#include "core\__BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkInitialize()
{
	if (BK_ERROR(_BkLogger_Initialize()))
		return BK_FAILURE;

	_BkGraphicsAPI_Load();

	if (BK_ERROR(_BkGraphicsAPI_Initialize()))
	{
		BkError(BK_ERROR_LOCATION "Failed to initialize the graphics API!");
		_BkLogger_Uninitialize();
		return BK_FAILURE;
	}
	
	return BK_SUCCESS;
}

void	BkUninitialize(void)
{
	_BkLogger_Uninitialize();
	_BkGraphicsAPI_Uninitialize();
}