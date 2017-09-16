#ifndef __INTERNAL_BK_OPENGL_H__
#define __INTERNAL_BK_OPENGL_H__

#include "core\BkError.h"
#include "core\BkShader.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkResult	_BkOpenGL_Initialize(void);
extern void		_BkOpenGL_Uninitialize(void);
extern void		_BkOpenGL_Render(void* pBufferAPI, void* pMaterialAPI);
extern void		_BkOpenGL_CreateShader(void** ppShaderAPI, BkShaderType const Type, char const* pShaderContent);
extern void		_BkOpenGL_ReleaseShader(void** ppShaderAPI);
extern void		_BkOpenGL_CreateShaderProgram(void** ppMaterialAPI, void* pVertexShaderAPI, void* pPixelShaderAPI);
extern void		_BkOpenGL_ReleaseShaderProgram(void** ppMaterialAPI);
extern void		_BkOpenGL_CreateBuffer(void** ppBufferAPI, uint32 const Size, void const* pData);
extern void		_BkOpenGL_ReleaseBuffer(void** ppBufferAPI);

#endif
