#include "core\BkRenderer.h"

#include "pil\__BkGraphicsAPI.h"

// ~~~~~ Def(ALL) ~~~~~

void	BkRender(BkBuffer const* pBuffer, BkMaterial const* pMaterial)
{
	_BkGraphicsAPI_Render(pBuffer->api, pMaterial->api);
}