#include "pil\BkOpenGL.h"
#include "core\BkString.h"
#include "core\BkShader.h"
#include "core\BkList.h"
#include "core\BkMaterial.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkResult	_BkInitializeOpenGL(void);
extern void		_BkUninitializeOpenGL(void);
extern void		_BkRenderOpenGL(void);
extern void		_BkCreateOpenGLShader(void** ppShader, BkShaderType const Type, BkStringBuf* pShaderContent);
extern void		_BkReleaseOpenGLShader(void** ppShader);
extern void		_BkCompileOpenGLShader(BkMaterial** ppMaterial);

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkInitializeOpenGL(void)
{
	GLenum	lResult = GLEW_OK; // 4 bytes

	lResult = glewInit();
	if (lResult != GLEW_OK)
		BkDie(BK_ERROR_LOCATION "Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(lResult));
	
	return BK_SUCCESS;
}

void	_BkUninitializeOpenGL(void)
{
}

void	_BkRenderOpenGL(void)
{
	static real const	lClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Float precision: 16 bytes | Double precision: 32 bytes
	
	glClearBufferfv(GL_COLOR, 0, lClearColor);
}

extern void		_BkCreateOpenGLShader(void** ppShader, BkShaderType const Type, BkStringBuf* pShaderContent)
{
	assert(!BK_ISNULL(ppShader));
	assert(!BK_ISNULL(pShaderContent));
	assert(Type == _BK_PIXEL_SHADER_ || Type == _BK_VERTEX_SHADER_);

	BkOpenGLShader*	lpShader = malloc(sizeof(BkOpenGLShader));
	if (lpShader == NULL)
	{
		BkReleaseStringBuf(pShaderContent);
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");
	}

	if (Type == _BK_VERTEX_SHADER_)
		lpShader->shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (Type == _BK_PIXEL_SHADER_)
		lpShader->shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(lpShader->shaderID, 1, &(pShaderContent->buf), NULL);
	glCompileShader(lpShader->shaderID);

	*ppShader = lpShader;
}

extern void		_BkReleaseOpenGLShader(void** ppShader)
{
	assert(!BK_ISNULL(ppShader));

	glDeleteShader(((BkOpenGLShader*)ppShader)->shaderID);

	free(*ppShader);
	*ppShader = NULL;
}

void	_BkCompileOpenGLShader(BkMaterial** ppMaterial)
{
	assert(!BK_ISNULL(ppMaterial));

	BkOpenGLShader*	lPixelShader = (*ppMaterial)->pixelShader->api;
	BkOpenGLShader*	lVertexShader = (*ppMaterial)->vertexShader->api;

	BkOpenGLProgram* lpProgram = malloc(sizeof(BkOpenGLProgram));
	if (BK_ISNULL(lpProgram))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpProgram->programID = glCreateProgram();
	glAttachShader(lpProgram->programID, lVertexShader->shaderID);
	glAttachShader(lpProgram->programID, lPixelShader->shaderID);
	glLinkProgram(lpProgram->programID);

	(*ppMaterial)->api = lpProgram;
}