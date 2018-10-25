#ifndef __BK_OPENGL_BUFFER_H__
#define __BK_OPENGL_BUFFER_H__

// blackhart headers.
#include "foundation\BkAtomicDataType.h"

// Type definitions.
struct BkBuffer
{
	GLuint	id;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Create a buffer.
 *
 * \param size The size of the buffer.
 * \param data The data to add to the buffer.
 * \return The buffer.
 */
extern struct BkBuffer*	_BkBuffer_Create(size_t const size, void const* data);

/*! \brief Release a buffer.
 *
 * \param buffer The buffer to destroy.
 */
extern void			_BkBuffer_Release(struct BkBuffer** buffer);

#endif