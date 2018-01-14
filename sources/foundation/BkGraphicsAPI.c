// Blackhart.foundation headers.
#include "foundation\__BkGraphicsAPI.h"
#include "foundation\BkGraphicsAPI.h"
#include "foundation\BkCamera.h"

// Blackhart.renderer headers.
#include "renderer\hardware\__BkOpenGL.h"

// ~~~~~ Def(INTERNAL) ~~~~~

void	(*_BkGraphicsAPI_Initialize)(void) = NULL;
void	(*_BkGraphicsAPI_Uninitialize)(void) = NULL;
void	(*_BkGraphicsAPI_Render)(struct BkCamera*) = NULL;

void	_BkGraphicsAPI_Load(void)
{
	_BkGraphicsAPI_Initialize = &_BkOpenGL_Initialize;
	_BkGraphicsAPI_Uninitialize = &_BkOpenGL_Uninitialize;
	_BkGraphicsAPI_Render = &_BkOpenGL_Render;
}