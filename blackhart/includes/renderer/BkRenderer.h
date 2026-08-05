#ifndef __BK_RENDERER_H__
#define __BK_RENDERER_H__

/**
 * @file BkRenderer.h
 * @brief Draws a scene through a camera.
 *
 * Call BkRender every frame with your scene and camera. The renderer clears
 * the framebuffer, binds the default shader, asks the GPU cache for each
 * cloud (uploading if needed), and draws them as points.
 *
 * At the start of each frame it also flushes dirty GPU cache entries, so
 * clouds removed from the scene are unloaded from the GPU automatically.
 *
 * Initialization runs inside BkInitialize once an OpenGL context exists.
 * Applications do not manage shaders or the cache — they only load clouds,
 * put them in a scene, and call BkRender.
 */

// ~~~~~ Blackhart Headers ~~~~~

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

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Renders the scene using the specified camera.
 *
 * Flushes dirty GPU cache entries, then draws each point cloud in the scene
 * (lazy GPU upload via the internal cache).
 *
 * @param scene Scene containing point clouds to draw. Must not be NULL.
 * @param camera Camera to use for rendering. Must not be NULL.
 */
extern BK_API void BkRender(BkScene* scene, BkCamera* camera);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes the render context.
 *
 * Sets up the rendering infrastructure, including OpenGL context
 * initialization (GLEW), default shaders, and the GPU cache. This function
 * should be called during library initialization, after the OpenGL context
 * has been created.
 */
extern void _BkRender_Initialize(void);

/**
 * @brief Uninitializes the render context.
 *
 * Cleans up the rendering infrastructure and releases rendering resources
 * (GPU cache, shader program). This function should be called during library
 * cleanup, before destroying the OpenGL context.
 */
extern void _BkRender_Uninitialize(void);

/**
 * @brief Returns the renderer-owned GPU cache, or NULL if not initialized.
 */
extern BkGpuCache* _BkRender_GetGpuCache(void);

#endif
