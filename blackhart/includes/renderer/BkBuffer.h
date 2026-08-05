#ifndef __BK_OPENGL_BUFFER_H__
#define __BK_OPENGL_BUFFER_H__

/**
 * @file BkBuffer.h
 * @brief Holds a block of data on the GPU.
 *
 * BkBuffer wraps an OpenGL buffer object (usually a VBO). You create one with
 * a size and a pointer to CPU data; the bytes are uploaded to the GPU. Later
 * you can ask for its OpenGL id when you need to bind it, then release the
 * handle when you no longer need that GPU memory.
 *
 * Internal only — used by other renderer modules such as BkGpuPointCloud.
 * A valid OpenGL context is required.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkBuffer
 * @brief Opaque handle to an OpenGL buffer object (VBO, etc.).
 */
typedef struct BkBuffer BkBuffer;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Creates an OpenGL buffer object with initial data.
 *
 * Allocates and initializes a new buffer object, uploads the provided data to
 * the GPU, and returns the buffer handle. The buffer can be used for vertex
 * data, index data, or other buffer purposes.
 *
 * @param size The size in bytes of the data to store in the buffer.
 * @param data Pointer to the data to upload to the buffer. Must not be NULL.
 * @return Pointer to the newly created buffer handle, or NULL if creation
 * fails.
 */
extern BkBuffer* _BkBuffer_Create(size_t const size, void const* data);

/**
 * @brief Releases a buffer object and frees its resources.
 *
 * Deletes the OpenGL buffer object and frees the memory allocated for the
 * buffer handle. The buffer pointer is set to NULL after release.
 *
 * @param buffer Pointer to a pointer to the buffer to release.
 */
extern void _BkBuffer_Release(BkBuffer** buffer);

/**
 * @brief Returns the OpenGL buffer object name.
 *
 * @param buffer Buffer handle. Must not be NULL.
 * @return OpenGL buffer ID.
 */
extern uint32 _BkBuffer_GetId(BkBuffer const* buffer);

#endif
