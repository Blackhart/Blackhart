#ifndef __BK_OPENGL_SHADER_H__
#define __BK_OPENGL_SHADER_H__

#include <GL\glew.h>

enum BkShaderType
{
	_BK_VERTEX_SHADER_,
	_BK_PIXEL_SHADER_
};

struct BkOpenGLShader
{
	GLuint	id;
};

struct BkOpenGLShaderProgram
{
	GLuint	id;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

struct BkOpenGLShader*		_BkOpenGL_CreateShader(char const* path, enum BkShaderType const shader_type);
void				_BkOpenGL_ReleaseShader(struct BkOpenGLShader** shader);
struct BkOpenGLShaderProgram*	_BkOpenGL_CreateShaderProgram(struct BkOpenGLShader* vertex_shader, struct BkOpenGLShader* pixel_shader);
void				_BkOpenGL_ReleaseShaderProgram(struct BkOpenGLShaderProgram** shader_program);

#endif
