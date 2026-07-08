#ifndef __BK_OPENGL_BUFFER_H__
#define __BK_OPENGL_BUFFER_H__

/**
 * @file BkBuffer.h
 * @brief Defines buffer structures for OpenGL rendering.
 *
 * This file provides structures and functions for managing OpenGL buffer objects
 * (vertex buffers, index buffers, etc.). Note: Functions in this file are marked
 * as INTERNAL and should not be used directly by external code.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkBuffer
 * @brief Structure representing an OpenGL buffer object.
 *
 * Contains the OpenGL buffer ID for managing GPU-side buffer storage
 * (vertex data, index data, uniform buffers, etc.).
 */
struct BkBuffer
{
	GLuint	id;  /**< OpenGL buffer object ID. */
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Creates an OpenGL buffer object with initial data.
 *
 * Allocates and initializes a new buffer object, uploads the provided data to the GPU,
 * and returns the buffer structure. The buffer can be used for vertex data, index data,
 * or other buffer purposes.
 *
 * @param size The size in bytes of the data to store in the buffer.
 * @param data Pointer to the data to upload to the buffer. Can be NULL to create
 *             an empty buffer.
 * @return Pointer to the newly created buffer object, or NULL if creation fails.
 */
extern struct BkBuffer*	_BkBuffer_Create(size_t const size, void const* data);

/**
 * @brief Releases a buffer object and frees its resources.
 *
 * Deletes the OpenGL buffer object and frees the memory allocated for the buffer structure.
 * The buffer pointer is set to NULL after release.
 *
 * @param buffer Pointer to a pointer to the buffer to release. The pointer will be set to NULL.
 */
extern void			_BkBuffer_Release(struct BkBuffer** buffer);

#endif