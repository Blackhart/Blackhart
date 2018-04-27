// blackhart headers.
#include "foundation\BkCamera.h"
#include "renderer\BkRenderer.h"
#include "renderer\BkOpenGL.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkRender(struct BkCamera* camera)
{
    _BkOpenGL_Render(camera);
}