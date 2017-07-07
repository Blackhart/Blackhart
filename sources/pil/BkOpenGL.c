#include "pil\BkOpenGL.h"
#include "core\BkShader.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern BkResult	_BkOpenGL_Initialize(void);
extern void		_BkOpenGL_Uninitialize(void);
extern void		_BkOpenGL_Render(void);
extern void		_BkOpenGL_CreateShader(void** ppShader, BkShaderType const Type, char const* pShaderContent);
extern void		_BkOpenGL_ReleaseShader(void** ppShader);
extern void		_BkOpenGL_CreateShaderProgram(void** ppShaderProgram, void* pVertexShader, void* pPixelShader);
extern void		_BkOpenGL_ReleaseShaderProgram(void** ppShaderProgram);

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkOpenGL_Initialize(void)
{
	GLenum	lResult = GLEW_OK; // 4 bytes

	lResult = glewInit();
	if (lResult != GLEW_OK)
		BkDie(BK_ERROR_LOCATION "Glew error : %s\nFailed to initialize OpenGL!", glewGetErrorString(lResult));
	
	return BK_SUCCESS;
}

void	_BkOpenGL_Uninitialize(void)
{
}

void	_BkOpenGL_Render(void)
{
	static real const	lClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Float precision: 16 bytes | Double precision: 32 bytes
	
	glClearBufferfv(GL_COLOR, 0, lClearColor);
}

void	_BkOpenGL_CreateShader(void** ppShader, BkShaderType const Type, char const* pShaderContent)
{
	assert(!BK_ISNULL(ppShader));
	assert(!BK_ISNULL(pShaderContent));
	assert(Type == _BK_PIXEL_SHADER_ || Type == _BK_VERTEX_SHADER_);

	BkOpenGLShader*	lpShader = malloc(sizeof(BkOpenGLShader)); // 4 bytes
	if (lpShader == NULL)
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory");

	if (Type == _BK_VERTEX_SHADER_)
		lpShader->shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (Type == _BK_PIXEL_SHADER_)
		lpShader->shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(lpShader->shaderID, 1, &pShaderContent, NULL);
	glCompileShader(lpShader->shaderID);

	*ppShader = lpShader;
}

void	_BkOpenGL_ReleaseShader(void** ppShader)
{
	assert(!BK_ISNULL(ppShader));
	assert(!BK_ISNULL(*ppShader));

	BkOpenGLShader*	lpShader = *ppShader; // 4 bytes

	glDeleteShader(lpShader->shaderID);

	free(*ppShader);
	*ppShader = NULL;
}

void	_BkOpenGL_CreateShaderProgram(void** ppShaderProgram, void* pVertexShader, void* pPixelShader)
{
	assert(!BK_ISNULL(ppShaderProgram));
	assert(!BK_ISNULL(pVertexShader));
	assert(!BK_ISNULL(pPixelShader));

	BkOpenGLShader*		lPixelShader = pPixelShader; // 4 bytes
	BkOpenGLShader*		lVertexShader = pVertexShader; // 4 bytes

	BkOpenGLProgram*	lpProgram = malloc(sizeof(BkOpenGLProgram)); // 4 bytes
	if (BK_ISNULL(lpProgram))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpProgram->programID = glCreateProgram();
	glAttachShader(lpProgram->programID, lVertexShader->shaderID);
	glAttachShader(lpProgram->programID, lPixelShader->shaderID);
	glLinkProgram(lpProgram->programID);

	*ppShaderProgram = lpProgram;
}

void	_BkOpenGL_ReleaseShaderProgram(void** ppShaderProgram)
{
	assert(!BK_ISNULL(ppShaderProgram));
	assert(!BK_ISNULL(*ppShaderProgram));

	BkOpenGLProgram*	lProgram = *ppShaderProgram; // 4 bytes

	glDeleteProgram(lProgram->programID);

	free(*ppShaderProgram);
	*ppShaderProgram = NULL;
}