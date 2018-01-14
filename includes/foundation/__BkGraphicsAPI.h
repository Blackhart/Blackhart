#ifndef __INTERNAL_BK_GRAPHICSAPI_H__
#define __INTERNAL_BK_GRAPHICSAPI_H__

// Forward declarations.
struct BkCamera;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Loads the selected graphics API.
 *
 * For instance, OpenGL API only!
 */
extern void	_BkGraphicsAPI_Load(void);

/*! \brief Initializes the graphics API.
 */
extern void	(*_BkGraphicsAPI_Initialize)(void);

/*! \brief Uninitializes the graphics API.
 */
extern void	(*_BkGraphicsAPI_Uninitialize)(void);

/*! \brief Renders the scene.
 */
extern void	(*_BkGraphicsAPI_Render)(struct BkCamera*);

#endif
