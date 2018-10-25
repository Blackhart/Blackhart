// Standard headers.
#include <stdlib.h>

// Glew headers.
#include <GL\glew.h>

// blackhart headers.
#include "foundation\BkError.h"
#include "renderer\BkTexture.h"

// ~~~~~ Def(INTERNAL) ~~~~~

struct BkTexture*  _BkTexture_Create(uint16 const width, uint16 const height, void const* data)
{
    BK_ASSERT(width == 0 || width % 2 != 0);
    BK_ASSERT(height == 0 || height % 2 != 0);
    BK_ASSERT(BK_ISNULL(data));

    struct BkTexture* texture = malloc(sizeof(struct BkTexture));
    BK_ERROR(BK_ISNULL(texture), "Memory system failed to allocate memory block");

    glGenTextures(1, &(texture->id));
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, width, height);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_FLOAT, data);

    return texture;
}

void _BkTexture_Release(struct BkTexture** texture)
{
    BK_ASSERT(BK_ISNULL(texture));
    BK_ASSERT(BK_ISNULL(*texture));

    glDeleteTextures(1, &((*texture)->id));

    free(*texture);
    *texture = NULL;
}