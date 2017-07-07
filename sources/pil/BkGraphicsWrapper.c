#include "pil\BkGraphicsWrapper.h"
#include "core\BkString.h"
#include "core\BkShader.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void		_BkGraphicsAPI_Load(void);

extern BkResult	_BkOpenGL_Initialize(void);
extern void		_BkOpenGL_Uninitialize(void);
extern void		_BkOpenGL_Render(void* pBufferAPI, void* pMaterialAPI);
extern void		_BkOpenGL_CreateShader(void** ppShaderAPI, BkShaderType const Type, char const* pShaderContent);
extern void		_BkOpenGL_ReleaseShader(void** ppShaderAPI);
extern void		_BkOpenGL_CreateShaderProgram(void** ppMaterialAPI, void* pVertexShaderAPI, void* pPixelShaderAPI);
extern void		_BkOpenGL_ReleaseShaderProgram(void** ppMaterialAPI);
extern void		_BkOpenGL_CreateBuffer(void** ppBufferAPI, uint32 const Size, void const* pData);
extern void		_BkOpenGL_ReleaseBuffer(void** ppBufferAPI);

// ~~~~~ Def(INTERNAL) ~~~~~

extern BkResult	(*_BkGraphicsAPI_Initialize)(void) = NULL;
extern void		(*_BkGraphicsAPI_Uninitialize)(void) = NULL;
extern void		(*_BkGraphicsAPI_Render)(void* pBufferAPI, void* pMaterialAPI) = NULL;
extern void		(*_BkGraphicsAPI_CreateShader)(void** ppShaderAPI, BkShaderType const Type, char const* pShaderContent) = NULL;
extern void		(*_BkGraphicsAPI_ReleaseShader)(void** ppShaderAPI) = NULL;
extern void		(*_BkGraphicsAPI_CreateShaderProgram)(void** ppMaterialAPI, void* pVertexShaderAPI, void* pPixelShaderAPI) = NULL;
extern void		(*_BkGraphicsAPI_ReleaseShaderProgram)(void** ppMaterialAPI) = NULL;
extern void		(*_BkGraphicsAPI_CreateBuffer)(void** ppBufferAPI, uint32 const Size, void const* pData) = NULL;
extern void		(*_BkGraphicsAPI_ReleaseBuffer)(void** ppBufferAPI) = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	_BkGraphicsAPI_Load(void)
{
	_BkGraphicsAPI_Initialize = &_BkOpenGL_Initialize;
	_BkGraphicsAPI_Uninitialize = &_BkOpenGL_Uninitialize;
	_BkGraphicsAPI_Render = &_BkOpenGL_Render;
	_BkGraphicsAPI_CreateShader = &_BkOpenGL_CreateShader;
	_BkGraphicsAPI_ReleaseShader = &_BkOpenGL_ReleaseShader;
	_BkGraphicsAPI_CreateShaderProgram = &_BkOpenGL_CreateShaderProgram;
	_BkGraphicsAPI_ReleaseShaderProgram = &_BkOpenGL_ReleaseShaderProgram;
	_BkGraphicsAPI_CreateBuffer = &_BkOpenGL_CreateBuffer;
	_BkGraphicsAPI_ReleaseBuffer = &_BkOpenGL_ReleaseBuffer;
}