#include "pil\BkGraphicsAPI.h"
#include "pil\__BkGraphicsAPI.h"

#include "core\BkString.h"

#include "renderer\hardware\__BkOpenGL.h"

// ~~~~~ Def(INTERNAL) ~~~~~

BkResult	(*_BkGraphicsAPI_Initialize)(void) = NULL;
void		(*_BkGraphicsAPI_Uninitialize)(void) = NULL;
void		(*_BkGraphicsAPI_Render)(void) = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	_BkGraphicsAPI_Load(void)
{
	_BkGraphicsAPI_Initialize = &_BkOpenGL_Initialize;
	_BkGraphicsAPI_Uninitialize = &_BkOpenGL_Uninitialize;
	_BkGraphicsAPI_Render = &_BkOpenGL_Render;
}