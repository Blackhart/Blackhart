#ifndef __BK_RENDERER_H__
#define __BK_RENDERER_H__

// blackhart headers.
#include "foundation\BkExport.h"

// Forward declarations.
struct BkCamera;

// ~~~~~ Dcl(PUBLIC) ~~~~~

/*! \brief Renders the scene.
 */
extern BK_API void	BkRender(struct BkCamera*);

#endif