#ifndef __BK_MODEL_H__
#define __BK_MODEL_H__

/**
 * @file BkModel.h
 * @brief Defines the BkModel structure and functions for model management in 3D rendering.
 *
 * This file provides the definition of the BkModel struct, which represents a model with a list of meshes.
 * It includes functions for initializing, adding, and removing meshes from the model.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkArray.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkModel
 * @brief Structure representing a model in 3D rendering.
 *
 * The model contains a list of meshes that can be rendered.
 */
struct BkModel
{
    struct BkArray* meshes; /**< List of meshes in the model. */
};

#endif