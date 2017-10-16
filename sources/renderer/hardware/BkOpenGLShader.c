#include "pil\BkFileSystem.h"

#include "core\BkString.h"

#include "renderer\hardware\__BkOpenGLShader.h"

// ~~~~~ Def(ALL) ~~~~~

struct BkOpenGLShader*	_BkOpenGL_CreateShader(char const* path, enum BkShaderType const shader_type)
{
	assert(!BK_ISNULL(path));

	struct BkStringBuf string;

	BkStringBuf_Set(&string, NULL);

	if (BK_ERROR(BkFileSystem_ReadFromPath(path, &(string.buffer), &(string.size))))
	{
		BkError(BK_ERROR_LOCATION "Failed to load shader from flux [ $%s$ ]");
		return NULL;
	}

	struct BkOpenGLShader* shader = malloc(sizeof(struct BkOpenGLShader));
	if (shader == NULL)
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");

	if (shader_type == _BK_VERTEX_SHADER_)
		shader->id = glCreateShader(GL_VERTEX_SHADER);
	else if (shader_type == _BK_PIXEL_SHADER_)
		shader->id = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader->id, 1, &(string.buffer), NULL);
	glCompileShader(shader->id);

	BkStringBuf_Release(&string);

	return shader;
}

void	_BkOpenGL_ReleaseShader(struct BkOpenGLShader** shader)
{
	assert(!BK_ISNULL(shader));
	assert(!BK_ISNULL(*shader));

	glDeleteShader((*shader)->id);

	free(*shader);
	*shader = NULL;
}

struct BkOpenGLShaderProgram*	_BkOpenGL_CreateShaderProgram(struct BkOpenGLShader* pVertexShader, struct BkOpenGLShader* pPixelShader)
{
	assert(!BK_ISNULL(pVertexShader));
	assert(!BK_ISNULL(pPixelShader));

	struct BkOpenGLShaderProgram*	lpProgram = malloc(sizeof(struct BkOpenGLShaderProgram)); // 4 bytes
	if (BK_ISNULL(lpProgram))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpProgram->id = glCreateProgram();
	glAttachShader(lpProgram->id, pVertexShader->id);
	glAttachShader(lpProgram->id, pPixelShader->id);
	glLinkProgram(lpProgram->id);

	return lpProgram;
}

void	_BkOpenGL_ReleaseShaderProgram(struct BkOpenGLShaderProgram** ppShaderProgram)
{
	assert(!BK_ISNULL(ppShaderProgram));
	assert(!BK_ISNULL(*ppShaderProgram));

	glDeleteProgram((*ppShaderProgram)->id);

	free(*ppShaderProgram);
	*ppShaderProgram = NULL;
}