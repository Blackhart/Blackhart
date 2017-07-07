#include "core\BkRenderer.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkGraphicsAPI_Render)(void);

// ~~~~~ Def(ALL) ~~~~~

void	BkRender()
{
	_BkGraphicsAPI_Render();
}