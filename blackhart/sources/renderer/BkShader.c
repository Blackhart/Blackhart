// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "foundation\BkFileSystem.h"
#include "renderer\BkShader.h"

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkShader*	_BkShader_Create(char const* path, enum BkShaderType const shader_type)
{
	BK_ASSERT(BK_ISNULL(path));

	char* str = NULL;
	size_t size = 0;

	BkFileSystem_ReadFromPath(path, &str, &size);

	struct BkShader* shader = malloc(sizeof(struct BkShader));
    BK_ERROR(BK_ISNULL(shader), "Memory system failed to allocate memory");

	shader->id = glCreateShader(shader_type);

	glShaderSource(shader->id, 1, &str, NULL);
	glCompileShader(shader->id);

	return shader;
}

void	_BkShader_Release(struct BkShader** shader)
{
	BK_ASSERT(BK_ISNULL(shader) || BK_ISNULL(*shader));

	glDeleteShader((*shader)->id);

	free(*shader);
	*shader = NULL;
}

struct BkShaderProgram*	_BkShaderProgram_Create(void)
{
	struct BkShaderProgram* shader_program = malloc(sizeof(struct BkShaderProgram));
    BK_ERROR(BK_ISNULL(shader_program), "Memory system failed to allocate memory block");

	shader_program->id = glCreateProgram();

	return shader_program;
}

void _BkShaderProgram_AttachShader(struct BkShaderProgram* shader_program, struct BkShader* shader)
{
    BK_ASSERT(BK_ISNULL(shader_program));
    BK_ASSERT(BK_ISNULL(shader));

    glAttachShader(shader_program->id, shader->id);
}

void _BkShaderProgram_Compile(struct BkShaderProgram* shader_program)
{
    BK_ASSERT(BK_ISNULL(shader_program));

    glLinkProgram(shader_program->id);
}

void	_BkShaderProgram_Release(struct BkShaderProgram** shader_program)
{
	BK_ASSERT(BK_ISNULL(shader_program) || BK_ISNULL(*shader_program));

	glDeleteProgram((*shader_program)->id);

	free(*shader_program);
	*shader_program = NULL;
}