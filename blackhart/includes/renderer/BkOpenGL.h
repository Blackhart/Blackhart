#ifndef __INTERNAL_BK_OPENGL_H__
#define __INTERNAL_BK_OPENGL_H__

// Forward declarations.
struct BkCamera;

// ~~~~~ Dcl(INTERNAL) ~~~~~

/*! \brief Initializes the OpenGL context.
 */
extern void	_BkOpenGL_Initialize(void);

/*! \brief Uninitializes the OpenGL context.
 */
extern void	_BkOpenGL_Uninitialize(void);

/*! \brief Renders the scene with OpenGL API.
 */
extern void	_BkOpenGL_Render(struct BkCamera*);

#endif
