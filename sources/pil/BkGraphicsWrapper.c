#include "pil\BkGraphicsWrapper.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void		_BkLoadGraphicsAPI(void);
extern BkResult	_BkInitializeOpenGL(void);
extern void		_BkUninitializeOpenGL(void);
extern void		_BkRenderOpenGL(void);

// ~~~~~ Def(INTERNAL) ~~~~~

extern BkResult	(*_BkInitializeGraphicsAPI)(void) = NULL;
extern void		(*_BkUninitializeGraphicsAPI)(void) = NULL;
extern void		(*_BkRender)(void) = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	_BkLoadGraphicsAPI(void)
{
	_BkInitializeGraphicsAPI = &_BkInitializeOpenGL;
	_BkUninitializeGraphicsAPI = &_BkUninitializeOpenGL;
	_BkRender = &_BkRenderOpenGL;
}