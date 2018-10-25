#ifndef __BK_OPENGL_TEXTURE_H__
#define __BK_OPENGL_TEXTURE_H__

// blackhart headers.
#include "foundation\BkAtomicDataType.h"

// Type definitions.
struct BkTexture
{
    GLuint  id;
};

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Create a texture.
 *
 * \param width The width of the texture.
 * \param height The height of the texture.
 * \param data The data to add to the texture.
 * \return The texture.
 */
extern struct BkTexture*  _BkTexture_Create(uint16 const width, uint16 const height, void const* data);

/*! \brief Release a texture.
 *
 * \param texture The texture to release.
 */
extern void _BkTexture_Release(struct BkTexture** texture);

#endif