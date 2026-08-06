#ifndef __BK_COLOR3_H__
#define __BK_COLOR3_H__

/**
 * @file BkColor3.h
 * @brief 8-bit RGB color for point attributes.
 *
 * Used as optional per-vertex color on CPU point clouds (PLY red/green/blue).
 * Values are in [0, 255]. On the GPU they are uploaded as unsigned bytes and
 * normalized to [0, 1] in the shader.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkColor3
 * @brief Opaque-free RGB triplet (one byte per channel).
 */
struct BkColor3 {
  uint8 r; /**< Red channel in [0, 255]. */
  uint8 g; /**< Green channel in [0, 255]. */
  uint8 b; /**< Blue channel in [0, 255]. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Returns opaque white (255, 255, 255).
 */
extern BK_API struct BkColor3 BkColor3_White(void);

/**
 * @brief Builds a color from red, green, and blue components.
 */
extern BK_API struct BkColor3 BkColor3_FromRGB(uint8 const r, uint8 const g,
                                               uint8 const b);

#endif
