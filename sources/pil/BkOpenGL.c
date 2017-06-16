#include "pil\BkGraphicWrapper.h"
#include "pil\BkOpenGL.h"
#include "core\debug\BkLogger.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

int8	GwInitialize(BkGraphicsInfo const* const);
void	GwUninitialize();

// ~~~~~ Def(ALL) ~~~~~

int8	GwInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	GLenum	lResult = GLEW_OK; // 4 bytes

	lResult = glewInit();
	if (lResult != GLEW_OK)
	{
		BkLog("Glew error : %s\n", glewGetErrorString(lResult));
		BkLog("Failed to initialize OpenGL!\n");
		return -1;
	}
	BkLog("OpenGL Initialized | v%s\n", glGetString(GL_VERSION));
	return 0;
}

void	GwUninitialize()
{

}

void	BkRender()
{
	real	lClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, lClearColor);
}