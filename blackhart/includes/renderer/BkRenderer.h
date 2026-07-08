#ifndef __BK_RENDERER_H__
#define __BK_RENDERER_H__

/**
 * @file BkRenderer.h
 * @brief Defines rendering functions for the Blackhart renderer.
 *
 * This file provides functions for rendering scenes using a camera and the
 * OpenGL rendering pipeline. The renderer must be initialized before use.
 */

// ~~~~~ Blackhart Headers ~~~~~

#include "foundation/BkExport.h"

// ~~~~~ Forward declarations ~~~~~

struct BkCamera;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/**
 * @brief Renders the scene using the specified camera.
 *
 * Performs a complete rendering pass of the scene using the provided camera's
 * view and projection matrices. All objects in the scene are rendered according
 * to the camera's perspective.
 *
 * @param camera Pointer to the BkCamera object to use for rendering.
 */
extern BK_API void	BkRender(struct BkCamera* camera);

// ~~~~~ Dcl(INTERNAL) ~~~~~

/**
 * @brief Initializes the render context.
 *
 * Sets up the rendering infrastructure, including OpenGL context initialization.
 * This function should be called during library initialization, after the
 * OpenGL context has been created.
 */
extern void _BkRender_Initialize(void);

/**
 * @brief Uninitializes the render context.
 *
 * Cleans up the rendering infrastructure and releases rendering resources.
 * This function should be called during library cleanup, before destroying
 * the OpenGL context.
 */
extern void _BkRender_Uninitialize(void);

#endif