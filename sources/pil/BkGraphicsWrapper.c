#include "pil\BkGraphicsWrapper.h"
#include "core\BkString.h"
#include "core\BkShader.h"
#include "core\BkMaterial.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void		_BkLoadGraphicsAPI(void);

extern BkResult	_BkInitializeOpenGL(void);
extern void		_BkUninitializeOpenGL(void);
extern void		_BkRenderOpenGL(void);
extern void		_BkCreateOpenGLShader(void** ppShader, BkShaderType const Type, BkStringBuf* pShaderContent);
extern void		_BkReleaseOpenGLShader(void** ppShader);
extern void		_BkCompileOpenGLShader(BkMaterial** ppMaterial);

// ~~~~~ Def(INTERNAL) ~~~~~

extern BkResult	(*_BkInitializeGraphicsAPI)(void) = NULL;
extern void		(*_BkUninitializeGraphicsAPI)(void) = NULL;
extern void		(*_BkGraphicsAPIRender)(void) = NULL;
extern void		(*_BkCreateGraphicsAPIShader)(void** ppShader, BkShaderType const Type, BkStringBuf* pShaderContent) = NULL;
extern void		(*_BkReleaseGraphicsAPIShader)(void** ppShader) = NULL;
extern void		(*_BkCompileGraphicsAPIShader)(BkMaterial** ppMaterial) = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	_BkLoadGraphicsAPI(void)
{
	_BkInitializeGraphicsAPI = &_BkInitializeOpenGL;
	_BkUninitializeGraphicsAPI = &_BkUninitializeOpenGL;
	_BkGraphicsAPIRender = &_BkRenderOpenGL;
	_BkCreateGraphicsAPIShader = &_BkCreateOpenGLShader;
	_BkReleaseGraphicsAPIShader = &_BkReleaseOpenGLShader;
	_BkCompileGraphicsAPIShader = &_BkCompileOpenGLShader;
}