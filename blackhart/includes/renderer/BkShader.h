#ifndef __BK_OPENGL_SHADER_H__
#define __BK_OPENGL_SHADER_H__

// Type definitions.
enum BkShaderType
{
	_BK_VERTEX_SHADER_ = GL_VERTEX_SHADER,
    _BK_GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
	_BK_PIXEL_SHADER_ = GL_FRAGMENT_SHADER
};

struct BkShader
{
	GLuint	id;
};

struct BkShaderProgram
{
	GLuint	id;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Create a shader.
 *
 * \param path The path to the shader source.
 * \param shader_type The type of the shader.
 * \return The shader.
 */
extern struct BkShader*   _BkShader_Create(char const* path, enum BkShaderType const shader_type);

/*! \brief Release a shader.
 *
 * \param shader The shader to release.
 */
extern void _BkShader_Release(struct BkShader** shader);

/*! \brief Creates a shader program.
 *
 * \return The shader program.
 */
extern struct BkShaderProgram*    _BkShaderProgram_Create(void);

/*! \brief Attach a shader to a shader program.
*
* \param shader_program The shader program.
* \param shader The shader to attach.
*/
extern void _BkShaderProgram_AttachShader(struct BkShaderProgram* shader_program, struct BkShader* shader);

/*! \brief Compile a shader program.
*
* \param shader_program The shader program.
*/
extern void _BkShaderProgram_Compile(struct BkShaderProgram* shader_program);

/*! \brief Release a shader program.
 *
 * \param shader_program The shader program to release.
 */
extern void _BkShaderProgram_Release(struct BkShaderProgram** shader_program);

#endif
