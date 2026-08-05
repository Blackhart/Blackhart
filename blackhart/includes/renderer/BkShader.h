#ifndef __BK_OPENGL_SHADER_H__
#define __BK_OPENGL_SHADER_H__

/**
 * @file BkShader.h
 * @brief Compiles GLSL sources into a usable OpenGL program.
 *
 * A BkShader is one stage loaded from a `.glsl` file (vertex or fragment).
 * A BkShaderProgram combines several stages: you attach the shaders, compile
 * (link) the program, then bind it with its OpenGL id before drawing.
 *
 * Stages can be released after they are attached and linked; the program
 * keeps what it needs. Compile or link failures abort the process.
 *
 * Internal only — BkRenderer builds the default point-cloud program at
 * startup. A valid OpenGL context is required.
 */

// ~~~~~ Glew Headers ~~~~~

#include <GL/glew.h>

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @enum BkShaderType
 * @brief Enumeration of shader types supported by OpenGL.
 */
enum BkShaderType {
  _BK_VERTEX_SHADER_ = GL_VERTEX_SHADER, /**< Vertex shader type. */
  _BK_PIXEL_SHADER_ = GL_FRAGMENT_SHADER /**< Fragment (pixel) shader type. */
};

/**
 * @typedef BkShader
 * @brief Opaque handle to an OpenGL shader object (vertex, fragment, etc.).
 */
typedef struct BkShader BkShader;

/**
 * @typedef BkShaderProgram
 * @brief Opaque handle to an OpenGL shader program (linked pipeline stages).
 */
typedef struct BkShaderProgram BkShaderProgram;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Creates a shader from a source file.
 *
 * Loads the shader source code from the specified file path, compiles it as
 * the specified shader type, and returns a shader handle.
 *
 * @param path Path to the shader source file.
 * @param shader_type The type of shader to create (vertex or fragment).
 * @return Pointer to the created shader handle, or NULL if creation fails.
 */
extern BkShader* _BkShader_Create(char const* path,
                                  enum BkShaderType const shader_type);

/**
 * @brief Releases a shader object and frees its resources.
 *
 * Deletes the OpenGL shader object and frees the memory allocated for the
 * shader handle. The shader pointer is set to NULL after release.
 *
 * @param shader Pointer to a pointer to the shader to release.
 */
extern void _BkShader_Release(BkShader** shader);

/**
 * @brief Returns the OpenGL shader object name.
 *
 * @param shader Shader handle. Must not be NULL.
 * @return OpenGL shader ID.
 */
extern uint32 _BkShader_GetId(BkShader const* shader);

/**
 * @brief Creates a new shader program object.
 *
 * Allocates and initializes a new shader program handle. Shaders can then be
 * attached to this program using _BkShaderProgram_AttachShader.
 *
 * @return Pointer to the newly created shader program, or NULL if creation
 * fails.
 */
extern BkShaderProgram* _BkShaderProgram_Create(void);

/**
 * @brief Attaches a shader to a shader program.
 *
 * Attaches the specified shader to the shader program. The shader will be
 * included in the program when it is linked. Multiple shaders of different
 * types can be attached to the same program.
 *
 * @param shader_program Pointer to the shader program.
 * @param shader Pointer to the shader to attach.
 */
extern void _BkShaderProgram_AttachShader(BkShaderProgram* shader_program,
                                          BkShader* shader);

/**
 * @brief Compiles and links a shader program.
 *
 * Links all attached shaders into a complete shader program. If linking fails,
 * the process aborts with a structured error.
 *
 * @param shader_program Pointer to the shader program to compile.
 */
extern void _BkShaderProgram_Compile(BkShaderProgram* shader_program);

/**
 * @brief Releases a shader program object and frees its resources.
 *
 * Deletes the OpenGL shader program object and frees the memory allocated for
 * the program handle. The program pointer is set to NULL after release.
 *
 * @param shader_program Pointer to a pointer to the shader program to release.
 */
extern void _BkShaderProgram_Release(BkShaderProgram** shader_program);

/**
 * @brief Returns the OpenGL program object name.
 *
 * @param shader_program Program handle. Must not be NULL.
 * @return OpenGL program ID.
 */
extern uint32 _BkShaderProgram_GetId(BkShaderProgram const* shader_program);

#endif
