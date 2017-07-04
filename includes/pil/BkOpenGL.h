#ifndef __BK_OPENGL_H__
#define __BK_OPENGL_H__

#include <GL\glew.h>

#include "core\BkError.h"

struct sOpenGLShader
{
	GLuint	shaderID;
};

struct sOpenGLProgram
{
	GLuint	programID;
};

typedef struct sOpenGLShader	BkOpenGLShader;
typedef struct sOpenGLProgram	BkOpenGLProgram;

#endif