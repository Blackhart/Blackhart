#ifndef __BK_OPENGL_SHADER_H__
#define __BK_OPENGL_SHADER_H__

/**
 * @file BkShader.h
 * @brief Defines shader and shader program structures for OpenGL rendering.
 *
 * This file provides structures and functions for managing OpenGL shaders and
 * shader programs. Note: Functions in this file are marked as INTERNAL and
 * should not be used directly by external code.
 */

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
 * @struct BkShader
 * @brief Structure representing an OpenGL shader object.
 *
 * Contains the OpenGL shader ID for managing individual shader objects
 * (vertex shaders, fragment shaders, etc.).
 */
struct BkShader {
  GLuint id; /**< OpenGL shader object ID. */
};

/**
 * @struct BkShaderProgram
 * @brief Structure representing an OpenGL shader program.
 *
 * Contains the OpenGL shader program ID that links multiple shaders together
 * to form a complete rendering pipeline.
 */
struct BkShaderProgram {
  GLuint id; /**< OpenGL shader program object ID. */
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Creates a shader from a source file.
 *
 * Loads the shader source code from the specified file path, compiles it as
 * the specified shader type, and returns a shader object.
 *
 * @param path Path to the shader source file.
 * @param shader_type The type of shader to create (vertex or fragment).
 * @return Pointer to the created shader object, or NULL if creation fails.
 */
extern struct BkShader* _BkShader_Create(char const* path,
                                         enum BkShaderType const shader_type);

/**
 * @brief Releases a shader object and frees its resources.
 *
 * Deletes the OpenGL shader object and frees the memory allocated for the
 * shader structure. The shader pointer is set to NULL after release.
 *
 * @param shader Pointer to a pointer to the shader to release. The pointer will
 * be set to NULL.
 */
extern void _BkShader_Release(struct BkShader** shader);

/**
 * @brief Creates a new shader program object.
 *
 * Allocates and initializes a new shader program structure. Shaders can then be
 * attached to this program using _BkShaderProgram_AttachShader.
 *
 * @return Pointer to the newly created shader program, or NULL if creation
 * fails.
 */
extern struct BkShaderProgram* _BkShaderProgram_Create(void);

/**
 * @brief Attaches a shader to a shader program.
 *
 * Attaches the specified shader to the shader program. The shader will be
 * included in the program when it is compiled. Multiple shaders of different
 * types can be attached to the same program.
 *
 * @param shader_program Pointer to the shader program.
 * @param shader Pointer to the shader to attach.
 */
extern void _BkShaderProgram_AttachShader(
    struct BkShaderProgram* shader_program, struct BkShader* shader);

/**
 * @brief Compiles and links a shader program.
 *
 * Compiles all attached shaders and links them into a complete shader program.
 * If compilation or linking fails, error information should be retrieved from
 * OpenGL.
 *
 * @param shader_program Pointer to the shader program to compile.
 */
extern void _BkShaderProgram_Compile(struct BkShaderProgram* shader_program);

/**
 * @brief Releases a shader program object and frees its resources.
 *
 * Deletes the OpenGL shader program object and frees the memory allocated for
 * the program structure. The program pointer is set to NULL after release.
 *
 * @param shader_program Pointer to a pointer to the shader program to release.
 *                       The pointer will be set to NULL.
 */
extern void _BkShaderProgram_Release(struct BkShaderProgram** shader_program);

#endif
