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

struct sOpenGLBuffer
{
	GLuint	bufferID;
};

typedef struct sOpenGLShader	BkOpenGLShader;
typedef struct sOpenGLProgram	BkOpenGLProgram;
typedef struct sOpenGLBuffer	BkOpenGLBuffer;

#endif