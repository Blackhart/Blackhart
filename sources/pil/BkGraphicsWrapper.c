#include "pil\BkGraphicsWrapper.h"
#include "core\BkString.h"
#include "core\BkShader.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void		_BkGraphicsAPI_Load(void);

extern BkResult	_BkOpenGL_Initialize(void);
extern void		_BkOpenGL_Uninitialize(void);
extern void		_BkOpenGL_Render(void);
extern void		_BkOpenGL_CreateShader(void** ppShader, BkShaderType const Type, char const* pShaderContent);
extern void		_BkOpenGL_ReleaseShader(void** ppShader);
extern void		_BkOpenGL_CreateShaderProgram(void** ppShaderProgram, void* pVertexShader, void* pPixelShader);
extern void		_BkOpenGL_ReleaseShaderProgram(void** ppShaderProgram);

// ~~~~~ Def(INTERNAL) ~~~~~

extern BkResult	(*_BkGraphicsAPI_Initialize)(void) = NULL;
extern void		(*_BkGraphicsAPI_Uninitialize)(void) = NULL;
extern void		(*_BkGraphicsAPI_Render)(void) = NULL;
extern void		(*_BkGraphicsAPI_CreateShader)(void** ppShader, BkShaderType const Type, char const* pShaderContent) = NULL;
extern void		(*_BkGraphicsAPI_ReleaseShader)(void** ppShader) = NULL;
extern void		(*_BkGraphicsAPI_CreateShaderProgram)(void** ppShaderProgram, void* pVertexShader, void* pPixelShader) = NULL;
extern void		(*_BkGraphicsAPI_ReleaseShaderProgram)(void** ppShaderProgram) = NULL;

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
}