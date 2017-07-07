#include "core\BkRenderer.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkGraphicsAPI_Render)(void* pShaderProgram);

// ~~~~~ Def(ALL) ~~~~~

void	BkRender(BkBuffer const* pBuffer, BkMaterial const* pMaterial)
{
	_BkGraphicsAPI_Render(pBuffer->api, pMaterial->api);
}