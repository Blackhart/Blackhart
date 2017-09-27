#ifndef __BK_OPENGL_SHADER_H__
#define __BK_OPENGL_SHADER_H__

#include <GL\glew.h>

enum eShaderType
{
	_BK_VERTEX_SHADER_,
	_BK_PIXEL_SHADER_
};
typedef enum eShaderType	BkShaderType;

struct sOpenGLShader
{
	GLuint	shaderID;
};
typedef struct sOpenGLShader	BkOpenGLShader;

struct sOpenGLShaderProgram
{
	GLuint	programID;
};
typedef struct sOpenGLShaderProgram	BkOpenGLShaderProgram;

// ~~~~~ Dcl(INTERNAL) ~~~~~

BkOpenGLShader*			_BkOpenGL_CreateShader(char const* pPath, BkShaderType const Type);
void					_BkOpenGL_ReleaseShader(BkOpenGLShader** ppShader);
BkOpenGLShaderProgram*	_BkOpenGL_CreateShaderProgram(BkOpenGLShader* pVertexShader, BkOpenGLShader* pPixelShader);
void					_BkOpenGL_ReleaseShaderProgram(BkOpenGLShaderProgram** ppShaderProgram);

#endif
