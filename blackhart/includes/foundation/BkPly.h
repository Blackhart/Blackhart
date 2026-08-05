#ifndef __BK_PLY_H__
#define __BK_PLY_H__

/**
 * @file BkPly.h
 * @brief PLY file loading helpers for point cloud data.
 *
 * Thin wrapper around RPly that reads vertex positions from PLY files
 * into Blackhart containers. Faces and other elements are ignored.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkArray.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Loads vertex positions from a PLY file.
 *
 * Reads the `vertex` element properties `x`, `y` and `z` into a newly allocated
 * BkArray of BkPoint3. Other elements (including faces) are ignored.
 *
 * The caller owns the returned array and must destroy it with BkArray_Destroy()
 * then free() the BkArray pointer itself.
 *
 * @param filename Path to the PLY file to load.
 * @return Pointer to a BkArray filled with BkPoint3 vertices, or NULL on
 * failure (NULL path, missing/unreadable file, invalid PLY, missing
 * header/vertices).
 */
extern struct BkArray* _BkPly_LoadPoints(char const* filename);

#endif
