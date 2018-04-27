// Blackhart headers.
#include "Blackhart.h"

// blackhart headers.
#include "foundation\BkLogger.h"
#include "foundation\BkError.h"
#include "renderer\BkOpenGL.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkInitialize()
{
	_BkError_Initialize();
	_BkLogger_Initialize();
    _BkOpenGL_Initialize();
}

void	BkUninitialize(void)
{
    _BkOpenGL_Uninitialize();
	_BkLogger_Uninitialize();
	_BkError_Uninitialize();
}