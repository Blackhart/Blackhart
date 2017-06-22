#include "pil\BkGraphicWrapper.h"
#include "pil\BkOpenGL.h"
#include "core\BkLogger.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

BkResult	GwInitialize();
void		GwUninitialize();

// ~~~~~ Def(ALL) ~~~~~

BkResult	GwInitialize()
{
	GLenum	lResult = GLEW_OK; // 4 bytes

	lResult = glewInit();
	if (lResult != GLEW_OK)
		BkDie("Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(lResult));
	
	return BK_SUCCESS;
}

void	GwUninitialize()
{

}

void	BkRender()
{
	static real const	lClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Float precision: 16 bytes | Double precision: 32 bytes
	
	glClearBufferfv(GL_COLOR, 0, lClearColor);
}