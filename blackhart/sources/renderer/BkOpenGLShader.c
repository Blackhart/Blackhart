// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "foundation\BkFileSystem.h"
#include "renderer\BkOpenGLShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkOpenGLShader*	_BkOpenGL_CreateShader(char const* path, enum BkShaderType const shader_type)
{
	BK_ASSERT(BK_ISNULL(path));

	char* str = NULL;
	size_t size = 0;

	BkFileSystem_ReadFromPath(path, &str, &size);

	struct BkOpenGLShader* shader = malloc(sizeof(struct BkOpenGLShader));
    BK_ERROR(BK_ISNULL(shader), "Memory system failed to allocate memory");

	if (shader_type == _BK_VERTEX_SHADER_)
		shader->id = glCreateShader(GL_VERTEX_SHADER);
	else if (shader_type == _BK_PIXEL_SHADER_)
		shader->id = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader->id, 1, &str, NULL);
	glCompileShader(shader->id);

	return shader;
}

void	_BkOpenGL_ReleaseShader(struct BkOpenGLShader** shader)
{
	BK_ASSERT(BK_ISNULL(shader) || BK_ISNULL(*shader));

	glDeleteShader((*shader)->id);

	free(*shader);
	*shader = NULL;
}

struct BkOpenGLShaderProgram*	_BkOpenGL_CreateShaderProgram(struct BkOpenGLShader* pVertexShader, struct BkOpenGLShader* pPixelShader)
{
	BK_ASSERT(BK_ISNULL(pVertexShader));
	BK_ASSERT(BK_ISNULL(pPixelShader));

	struct BkOpenGLShaderProgram* program = malloc(sizeof(struct BkOpenGLShaderProgram));
    BK_ERROR(BK_ISNULL(program), "Memory system failed to allocate memory block");

	program->id = glCreateProgram();
	glAttachShader(program->id, pVertexShader->id);
	glAttachShader(program->id, pPixelShader->id);
	glLinkProgram(program->id);

	return program;
}

void	_BkOpenGL_ReleaseShaderProgram(struct BkOpenGLShaderProgram** ppShaderProgram)
{
	BK_ASSERT(BK_ISNULL(ppShaderProgram) || BK_ISNULL(*ppShaderProgram));

	glDeleteProgram((*ppShaderProgram)->id);

	free(*ppShaderProgram);
	*ppShaderProgram = NULL;
}