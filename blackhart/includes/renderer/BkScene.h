#ifndef __BK_SCENE_H__
#define __BK_SCENE_H__

/**
 * @file BkScene.h
 * @brief Defines the BkScene structure and functions for scene management in 3D
 * rendering.
 *
 * This file provides the definition of the BkScene struct, which represents a
 * scene with a list of objects. It includes functions for initializing, adding,
 * and removing objects from the scene.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"
#include "foundation/BkList.h"

#include "renderer/BkModel.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @struct BkScene
 * @brief Structure representing a scene in 3D rendering.
 *
 * The scene contains a list of models that can be rendered.
 */
struct BkScene {
  struct BkList *models; /**< List of models in the scene. */
};

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Adds a model to the scene.
 *
 * Adds a model to the scene's model list.
 *
 * @param scene Pointer to the BkScene object to add the model to.
 * @param model Pointer to the BkModel object to add to the scene.
 */
extern BK_API void BkScene_AddModel(struct BkScene *scene, struct BkModel *model);

/**
 * @brief Removes a model from the scene.
 *
 * Removes a model from the scene's model list.
 *
 * @param scene Pointer to the BkScene object to remove the model from.
 * @param model Pointer to the BkModel object to remove from the scene.
 */
extern BK_API void BkScene_RemoveModel(struct BkScene *scene,
                                       struct BkModel *model);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes and returns a new BkScene object.
 *
 * Allocates and initializes a new scene with an empty model list.
 * The caller is responsible for releasing the scene using
 * BkScene_Uninitialize().
 *
 * @return A new BkScene object with an initialized model list.
 */
extern BK_API struct BkScene BkScene_Initialize(void);

/**
 * @brief Uninitializes a BkScene object and releases its resources.
 *
 * Frees the model list and any associated resources within the scene.
 * After this call, the BkScene object should not be used unless reinitialized.
 *
 * @param obj Pointer to the BkScene object to uninitialize.
 */
extern BK_API void BkScene_Uninitialize(struct BkScene *obj);

#endif