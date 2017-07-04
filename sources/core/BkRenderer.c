#include "core\BkRenderer.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkGraphicsAPIRender)(void);

// ~~~~~ Def(ALL) ~~~~~

void	BkRender()
{
	_BkGraphicsAPIRender();
}