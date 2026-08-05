// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL/glew.h>

// blackhart headers.
#include "foundation/BkError.h"
#include "foundation/BkFileSystem.h"
#include "foundation/BkString.h"
#include "renderer/BkShader.h"

// ~~~~~ Type Definitions ~~~~~

struct BkShader {
  GLuint id;
};

struct BkShaderProgram {
  GLuint id;
};

// ~~~~~ Def(INTERNAL) ~~~~~

BkShader* _BkShader_Create(char const* path,
                           enum BkShaderType const shader_type) {
  BK_ASSERT(BK_ISNULL(path));

  char* str = NULL;
  size_t size = 0;

  BkFileSystem_ReadFromPath(path, &str, &size);

  BkShader* shader = malloc(sizeof(BkShader));
  BK_FATAL(BK_ISNULL(shader),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system failed to allocate memory",
               .result = "Process aborted",
           }));

  shader->id = glCreateShader((GLenum)shader_type);

  const GLchar* source = (const GLchar*)str;

  glShaderSource(shader->id, 1, &source, NULL);

  glCompileShader(shader->id);

  GLint compile_status = 0;

  glGetShaderiv(shader->id, GL_COMPILE_STATUS, &compile_status);

  if (!compile_status) {
    GLchar info_log[1024];
    GLsizei log_length = 0;

    glGetShaderInfoLog(shader->id, (GLsizei)sizeof(info_log), &log_length,
                       info_log);

    free(str);

    BK_FATAL(
        true,
        ((struct BkErrorInfo){
            .what = "Cannot compile shader",
            .why = BkString_CreateFormatted("GLSL compile error: %s", info_log),
            .how = "Fix the shader source and reload",
            .result = "Process aborted",
        }));
  }

  free(str);

  return shader;
}

void _BkShader_Release(BkShader** shader) {
  BK_ASSERT(BK_ISNULL(shader) || BK_ISNULL(*shader));

  glDeleteShader((*shader)->id);

  free(*shader);
  *shader = NULL;
}

uint32 _BkShader_GetId(BkShader const* shader) {
  BK_ASSERT(BK_ISNULL(shader));
  return (uint32)shader->id;
}

BkShaderProgram* _BkShaderProgram_Create(void) {
  BkShaderProgram* shader_program = malloc(sizeof(BkShaderProgram));
  BK_FATAL(BK_ISNULL(shader_program),
           ((struct BkErrorInfo){
               .what = "Fatal error",
               .why = "Memory system failed to allocate memory block",
               .result = "Process aborted",
           }));

  shader_program->id = glCreateProgram();

  return shader_program;
}

void _BkShaderProgram_AttachShader(BkShaderProgram* shader_program,
                                   BkShader* shader) {
  BK_ASSERT(BK_ISNULL(shader_program));
  BK_ASSERT(BK_ISNULL(shader));

  glAttachShader(shader_program->id, shader->id);
}

void _BkShaderProgram_Compile(BkShaderProgram* shader_program) {
  BK_ASSERT(BK_ISNULL(shader_program));

  glLinkProgram(shader_program->id);

  GLint link_status = 0;

  glGetProgramiv(shader_program->id, GL_LINK_STATUS, &link_status);

  if (!link_status) {
    GLchar info_log[1024];
    GLsizei log_length = 0;

    glGetProgramInfoLog(shader_program->id, (GLsizei)sizeof(info_log),
                        &log_length, info_log);

    _BkShaderProgram_Release(&shader_program);

    BK_FATAL(
        true,
        ((struct BkErrorInfo){
            .what = "Cannot link shader program",
            .why = BkString_CreateFormatted("GLSL link error: %s", info_log),
            .how = "Check shader stage compatibility and uniforms",
            .result = "Process aborted",
        }));
  }
}

void _BkShaderProgram_Release(BkShaderProgram** shader_program) {
  BK_ASSERT(BK_ISNULL(shader_program) || BK_ISNULL(*shader_program));

  glDeleteProgram((*shader_program)->id);

  free(*shader_program);
  *shader_program = NULL;
}

uint32 _BkShaderProgram_GetId(BkShaderProgram const* shader_program) {
  BK_ASSERT(BK_ISNULL(shader_program));
  return (uint32)shader_program->id;
}
