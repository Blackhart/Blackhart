#ifndef __INTERNAL_BK_GRAPHICSAPI_H__
#define __INTERNAL_BK_GRAPHICSAPI_H__

#include "core\BkError.h"
#include "core\BkShader.h"

extern void		_BkGraphicsAPI_Load(void);
extern BkResult	(*_BkGraphicsAPI_Initialize)(void);
extern void		(*_BkGraphicsAPI_Uninitialize)(void);
extern void		(*_BkGraphicsAPI_Render)(void* pBufferAPI, void* pMaterialAPI);
extern void		(*_BkGraphicsAPI_CreateShader)(void** ppShaderAPI, BkShaderType const Type, char const* pShaderContent);
extern void		(*_BkGraphicsAPI_ReleaseShader)(void** ppShaderAPI);
extern void		(*_BkGraphicsAPI_CreateShaderProgram)(void** ppMaterialAPI, void* pVertexShaderAPI, void* pPixelShaderAPI);
extern void		(*_BkGraphicsAPI_ReleaseShaderProgram)(void** ppMaterialAPI);
extern void		(*_BkGraphicsAPI_CreateBuffer)(void** ppBufferAPI, uint32 const Size, void const* pData);
extern void		(*_BkGraphicsAPI_ReleaseBuffer)(void** ppBufferAPI);

#endif
