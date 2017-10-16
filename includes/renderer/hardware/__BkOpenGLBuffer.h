#ifndef __BK_OPENGL_BUFFER_H__
#define __BK_OPENGL_BUFFER_H__

#include <GL\glew.h>

#include "pil\BkAtomicDataType.h"

struct BkOpenGLBuffer
{
	GLuint	id;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern struct BkOpenGLBuffer*	_BkOpenGL_CreateBuffer(uint32 const size, void const* data);
extern void			_BkOpenGL_ReleaseBuffer(struct BkOpenGLBuffer** opengl_buffer);

#endif