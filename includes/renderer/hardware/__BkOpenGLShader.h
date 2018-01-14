#ifndef __BK_OPENGL_SHADER_H__
#define __BK_OPENGL_SHADER_H__

// Type definitions.
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

/*! \brief Creates an OpenGL shader.
 *
 * \param path The path to the shader source.
 * \param shader_type The type of the shader.
 * \return The OpenGL shader.
 */
struct BkOpenGLShader*		_BkOpenGL_CreateShader(char const* path, enum BkShaderType const shader_type);

/*! \brief Destroy an OpenGL shader.
 *
 * \param shader The OpenGL shader to destroy.
 */
void				_BkOpenGL_ReleaseShader(struct BkOpenGLShader** shader);

/*! \brief Creates an OpenGL shader program.
 *
 * \param vertex_shader The vertex shader.
 * \param pixel_shader The pixel shader.
 * \return The OpenGL shader program.
 */
struct BkOpenGLShaderProgram*	_BkOpenGL_CreateShaderProgram(struct BkOpenGLShader* vertex_shader, struct BkOpenGLShader* pixel_shader);

/*! \brief Destroy an OpenGL shader program.
 *
 * \param shader_program The OpenGL shader program to destroy.
 */
void				_BkOpenGL_ReleaseShaderProgram(struct BkOpenGLShaderProgram** shader_program);

#endif
