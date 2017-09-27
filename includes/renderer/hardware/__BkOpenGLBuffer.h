#ifndef __BK_OPENGL_BUFFER_H__
#define __BK_OPENGL_BUFFER_H__

#include <GL\glew.h>

#include "pil\BkAtomicDataType.h"

struct sOpenGLBuffer
{
	GLuint	bufferID;
};

typedef struct sOpenGLBuffer	BkOpenGLBuffer;

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkOpenGLBuffer*	_BkOpenGL_CreateBuffer(uint32 const Size, void const* pData);
extern void				_BkOpenGL_ReleaseBuffer(BkOpenGLBuffer** ppBufferAPI);

#endif