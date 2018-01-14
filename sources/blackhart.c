// Blackhart headers.
#include "Blackhart.h"

// Blackhart.foundation headers.
#include "foundation\__BkGraphicsAPI.h"
#include "foundation\__BkLogger.h"
#include "foundation\__BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkInitialize()
{
	_BkError_Initialize();
	_BkLogger_Initialize();
	_BkGraphicsAPI_Load();
	_BkGraphicsAPI_Initialize();
}

void	BkUninitialize(void)
{
	_BkGraphicsAPI_Uninitialize();
	_BkLogger_Uninitialize();
	_BkError_Uninitialize();
}