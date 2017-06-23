#ifndef __BK_OPENGL_H__
#define __BK_OPENGL_H__

#include <GL\glew.h>

#include "core\BkError.h"

struct sOpenGLShader
{
	GLuint	shader;
};

typedef struct sOpenGLShader	BkOpenGLShader;

#endif