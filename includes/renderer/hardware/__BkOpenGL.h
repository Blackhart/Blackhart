#ifndef __INTERNAL_BK_OPENGL_H__
#define __INTERNAL_BK_OPENGL_H__

#include <GL\glew.h>

#include "core\BkError.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkResult	_BkOpenGL_Initialize(void);
extern void		_BkOpenGL_Uninitialize(void);
extern void		_BkOpenGL_Render(void);

#endif
