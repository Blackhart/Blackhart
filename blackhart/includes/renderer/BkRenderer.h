#ifndef __BK_RENDERER_H__
#define __BK_RENDERER_H__

/**
 * @file BkRenderer.h
 * @brief Draws the scene and optional viewport helpers.
 *
 * Blackhart does not decide for you what appears in the viewport. You compose
 * a frame from small drawing calls: clear the view, optionally draw a ground
 * grid, draw the point clouds in the scene, then any overlays you need
 * (object axes, bounding box, corner orientation gizmo).
 *
 * Typical frame:
 *
 *   BkRender_Clear();
 *   BkRender_DrawGrid(camera, cell_size);
 *   BkRender_DrawScene(scene, camera);
 *   BkRender_DrawAxes(camera, transform, length);
 *   BkRender_DrawAabb(camera, &aabb);
 *   BkRender_DrawOrientationGizmo(camera);
 *
 * Helpers (grid, gizmos, AABB) are not scene objects — call a draw function
 * when you want them. Point size is the one shared setting for how large
 * cloud points appear.
 *
 * Initialization runs inside BkInitialize once an OpenGL context exists.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkAtomicDataType.h"
#include "foundation/BkExport.h"

// ~~~~~ Type Definitions ~~~~~

/**
 * @typedef BkCamera
 * @brief Camera handle (see BkCamera.h).
 */
typedef struct BkCamera BkCamera;

/**
 * @typedef BkGpuCache
 * @brief Opaque GPU cache handle (see BkGpuCache.h).
 */
typedef struct BkGpuCache BkGpuCache;

/**
 * @typedef BkScene
 * @brief Opaque scene handle (see BkScene.h).
 */
typedef struct BkScene BkScene;

/**
 * @typedef BkAABB
 * @brief Axis-aligned bounding box (see BkAABB.h).
 */
typedef struct BkAABB BkAABB;

/**
 * @typedef BkTransform
 * @brief Position + orientation transform (see BkTransform.h).
 */
typedef struct BkTransform BkTransform;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Clears the viewport to a black background (color and depth).
 *
 * Call once per frame for the active viewport before drawing.
 */
extern BK_API void BkRender_Clear(void);

/**
 * @brief Draws every point cloud currently in the scene.
 *
 * Uploads clouds to the GPU on first use and frees GPU data for clouds that
 * left the scene since the last draw.
 *
 * @param scene Scene to draw. Must not be NULL.
 * @param camera Camera to look through. Must not be NULL.
 */
extern BK_API void BkRender_DrawScene(BkScene* scene, BkCamera* camera);

/**
 * @brief Sets how large each point appears on screen (pixels).
 *
 * Values are clamped to a practical range. Default is 2.
 *
 * @param size Desired point diameter in pixels.
 */
extern BK_API void BkRender_SetPointSize(real size);

/**
 * @brief Returns the current point size in pixels.
 */
extern BK_API real BkRender_GetPointSize(void);

/**
 * @brief Draws a ground reference grid (XZ plane, Y-up).
 *
 * Useful to judge scale and keep spatial context while navigating.
 *
 * @param camera Active camera. Must not be NULL.
 * @param cell_size Length of one grid square in world units (min 0.01).
 */
extern BK_API void BkRender_DrawGrid(BkCamera* camera, real cell_size);

/**
 * @brief Draws the corner orientation gizmo (camera axes).
 *
 * A small RGB triad in the corner of the viewport so you can read world
 * orientation while orbiting.
 *
 * @param camera Active camera. Must not be NULL.
 */
extern BK_API void BkRender_DrawOrientationGizmo(BkCamera* camera);

/**
 * @brief Draws RGB object axes at a transform (X red, Y green, Z blue).
 *
 * Useful to show where an object sits and how it is oriented.
 *
 * @param camera Active camera. Must not be NULL.
 * @param transform Object transform. Must not be NULL.
 * @param length Axis length in local units.
 */
extern BK_API void BkRender_DrawAxes(BkCamera* camera,
                                     struct BkTransform* transform,
                                     real length);

/**
 * @brief Draws a world-space bounding box as a wireframe.
 *
 * @param camera Active camera. Must not be NULL.
 * @param aabb World AABB. Must not be NULL.
 */
extern BK_API void BkRender_DrawAabb(BkCamera* camera,
                                     struct BkAABB const* aabb);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes the render context after an OpenGL context exists.
 *
 * Called from BkInitialize.
 */
extern void _BkRender_Initialize(void);

/**
 * @brief Shuts down the render context and releases its resources.
 *
 * Called from BkUninitialize before the OpenGL context is destroyed.
 */
extern void _BkRender_Uninitialize(void);

/**
 * @brief Returns the renderer-owned GPU cache, or NULL if not initialized.
 */
extern BkGpuCache* _BkRender_GetGpuCache(void);

#endif
