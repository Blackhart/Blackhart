#include "pil\BkOpenGL.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkResult	_BkInitializeOpenGL(void);
extern void		_BkUninitializeOpenGL(void);
extern void		_BkRenderOpenGL(void);

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkInitializeOpenGL(void)
{
	GLenum	lResult = GLEW_OK; // 4 bytes

	lResult = glewInit();
	if (lResult != GLEW_OK)
		BkDie(BK_ERROR_LOCATION "Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(lResult));
	
	return BK_SUCCESS;
}

void	_BkUninitializeOpenGL(void)
{

}

void	_BkRenderOpenGL(void)
{
	static real const	lClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Float precision: 16 bytes | Double precision: 32 bytes
	
	glClearBufferfv(GL_COLOR, 0, lClearColor);
}