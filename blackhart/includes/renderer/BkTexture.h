#ifndef __BK_OPENGL_TEXTURE_H__
#define __BK_OPENGL_TEXTURE_H__

/**
 * @file BkTexture.h
 * @brief Defines texture structures for OpenGL rendering.
 *
 * This file provides structures and functions for managing OpenGL texture objects.
 * Note: Functions in this file are marked as INTERNAL and should not be used directly
 * by external code.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkTexture
 * @brief Structure representing an OpenGL texture object.
 *
 * Contains the OpenGL texture ID for managing GPU-side texture storage.
 * Textures are used to apply images or data to rendered surfaces.
 */
struct BkTexture
{
    GLuint  id;  /**< OpenGL texture object ID. */
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Creates an OpenGL texture object with image data.
 *
 * Allocates and initializes a new texture object, uploads the provided image data
 * to the GPU, and returns the texture structure. The texture can be used for
 * applying images to rendered surfaces.
 *
 * @param width The width of the texture in pixels.
 * @param height The height of the texture in pixels.
 * @param data Pointer to the image data to upload. The data format depends on
 *             the implementation (typically RGBA or RGB).
 * @return Pointer to the newly created texture object, or NULL if creation fails.
 */
extern struct BkTexture*  _BkTexture_Create(uint16 const width, uint16 const height, void const* data);

/**
 * @brief Releases a texture object and frees its resources.
 *
 * Deletes the OpenGL texture object and frees the memory allocated for the texture structure.
 * The texture pointer is set to NULL after release.
 *
 * @param texture Pointer to a pointer to the texture to release. The pointer will be set to NULL.
 */
extern void _BkTexture_Release(struct BkTexture** texture);

#endif