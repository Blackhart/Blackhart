// Blackhart headers.
#include "Blackhart.h"

// blackhart headers.
#include "foundation\BkLogger.h"
#include "foundation\BkError.h"
#include "renderer\BkRenderer.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkInitialize(void)
{
	_BkError_Initialize();
	_BkLogger_Initialize();
    _BkRender_Initialize();
}

void	BkUninitialize(void)
{
    _BkRender_Uninitialize();
	_BkLogger_Uninitialize();
	_BkError_Uninitialize();
}