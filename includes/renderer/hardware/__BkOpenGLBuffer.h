#ifndef __BK_OPENGL_BUFFER_H__
#define __BK_OPENGL_BUFFER_H__

// Blackhart.foundation headers.
#include "foundation\BkAtomicDataType.h"

// Type definitions.
struct BkOpenGLBuffer
{
	GLuint	id;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Creates an OpenGL buffer.
 *
 * \param size The size of the buffer.
 * \param data The data to add to the OpenGL buffer.
 * \return The OpenGL buffer.
 */
extern struct BkOpenGLBuffer*	_BkOpenGL_CreateBuffer(uint32 const size, void const* data);

/*! \brief Destroy an OpenGL buffer.
 *
 * \param opengl_buffer The OpenGL buffer to destroy.
 */
extern void			_BkOpenGL_ReleaseBuffer(struct BkOpenGLBuffer** opengl_buffer);

#endif