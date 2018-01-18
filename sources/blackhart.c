// Blackhart headers.
#include "Blackhart.h"

// Blackhart.foundation headers.
#include "foundation\BkLogger.h"
#include "foundation\BkError.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkInitialize()
{
	_BkError_Initialize();
	_BkLogger_Initialize();
}

void	BkUninitialize(void)
{
	_BkLogger_Uninitialize();
	_BkError_Uninitialize();
}