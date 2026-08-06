#ifndef __BK_PLY_H__
#define __BK_PLY_H__

/**
 * @file BkPly.h
 * @brief PLY file loading helpers for point cloud data.
 *
 * Thin wrapper around RPly that reads vertex positions and optional RGB
 * colors from PLY files into Blackhart containers. Faces and other elements
 * are ignored.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkArray.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Loads vertex positions from a PLY file.
 *
 * Reads the `vertex` element properties `x`, `y` and `z` into a newly allocated
 * BkArray of BkPoint3. Other elements (including faces) and color properties
 * are ignored.
 *
 * The caller owns the returned array and must release it with BkArray_Release().
 *
 * @param filename Path to the PLY file to load.
 * @return Pointer to a BkArray filled with BkPoint3 vertices, or NULL on
 * failure (NULL path, missing/unreadable file, invalid PLY, missing
 * header/vertices).
 */
extern BkArray* _BkPly_LoadPoints(char const* filename);

/**
 * @brief Loads vertex colors from a PLY file.
 *
 * Reads `red`, `green` and `blue` on the `vertex` element into a newly
 * allocated BkArray of BkColor3. Returns NULL (without treating it as a hard
 * failure) when those properties are absent. Other elements are ignored.
 *
 * The caller owns the returned array and must release it with BkArray_Release().
 *
 * @param filename Path to the PLY file to load.
 * @return Pointer to a BkArray filled with BkColor3, or NULL if colors are
 * missing or on failure.
 */
extern BkArray* _BkPly_LoadColors(char const* filename);

#endif
