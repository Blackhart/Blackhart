#include "core\BkRenderer.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkRender)(void);

// ~~~~~ Def(ALL) ~~~~~

void	BkRender()
{
	_BkRender();
}