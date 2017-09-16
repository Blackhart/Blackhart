#include "pil\BkGraphicsAPI.h"
#include "core\BkString.h"
#include "core\BkShader.h"

#include "pil\__BkGraphicsAPI.h"
#include "pil\__BkOpenGL.h"

// ~~~~~ Def(INTERNAL) ~~~~~

BkResult	(*_BkGraphicsAPI_Initialize)(void) = NULL;
void		(*_BkGraphicsAPI_Uninitialize)(void) = NULL;
void		(*_BkGraphicsAPI_Render)(void* pBufferAPI, void* pMaterialAPI) = NULL;
void		(*_BkGraphicsAPI_CreateShader)(void** ppShaderAPI, BkShaderType const Type, char const* pShaderContent) = NULL;
void		(*_BkGraphicsAPI_ReleaseShader)(void** ppShaderAPI) = NULL;
void		(*_BkGraphicsAPI_CreateShaderProgram)(void** ppMaterialAPI, void* pVertexShaderAPI, void* pPixelShaderAPI) = NULL;
void		(*_BkGraphicsAPI_ReleaseShaderProgram)(void** ppMaterialAPI) = NULL;
void		(*_BkGraphicsAPI_CreateBuffer)(void** ppBufferAPI, uint32 const Size, void const* pData) = NULL;
void		(*_BkGraphicsAPI_ReleaseBuffer)(void** ppBufferAPI) = NULL;

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