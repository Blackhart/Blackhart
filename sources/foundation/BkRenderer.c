// Blackhart.foundation headers.
#include "foundation\__BkGraphicsAPI.h"
#include "foundation\BkCamera.h"

// Blackhart.renderer headers.
#include "foundation\BkRenderer.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkRender(struct BkCamera* camera)
{
	_BkGraphicsAPI_Render(camera);
}