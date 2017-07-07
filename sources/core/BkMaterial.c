#include "core\BkMaterial.h"
#include "core\BkList.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	(*_BkGraphicsAPI_CreateShaderProgram)(void** ppShaderProgram, void* pVertexShader, void* pPixelShader);
extern void	(*_BkGraphicsAPI_ReleaseShaderProgram)(void** ppShaderProgram);

// ~~~~~ Def(ALL) ~~~~~

BkMaterial*	BkMaterial_Create(void)
{
	BkMaterial* lpMaterial = malloc(sizeof(BkMaterial));
	if (BK_ISNULL(lpMaterial))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpMaterial->pixelShader = NULL;
	lpMaterial->vertexShader = NULL;
	lpMaterial->api = NULL;

	return lpMaterial;
}

void	BkMaterial_Release(BkMaterial** ppMaterial)
{
	if (BK_ISNULL(ppMaterial))
		return (void)BkWarning(BK_ERROR_LOCATION "ppMaterial is null");

	(*ppMaterial)->pixelShader = NULL;
	(*ppMaterial)->vertexShader = NULL;

	_BkGraphicsAPI_ReleaseShaderProgram(&(*ppMaterial)->api);
	(*ppMaterial)->api = NULL;

	free(*ppMaterial);
	*ppMaterial = NULL;
}

BkResult	BkMaterial_AttachShader(BkMaterial* pMaterial, BkShader const* pShader)
{
	if (BK_ISNULL(pMaterial))
		return BkError(BK_ERROR_LOCATION "pMaterial is null");
	if (BK_ISNULL(pShader))
		return BkError(BK_ERROR_LOCATION "pShader is null");

	switch (pShader->type)
	{
	case _BK_VERTEX_SHADER_:
		pMaterial->vertexShader = pShader;
		break;
	case _BK_PIXEL_SHADER_:
		pMaterial->pixelShader = pShader;
		break;
	default:
		return BkError(BK_ERROR_LOCATION "Invalid shader type");
	}

	return BK_SUCCESS;
}

BkResult	BkMaterial_CompileShader(BkMaterial* pMaterial)
{
	if (BK_ISNULL(pMaterial))
		return BkError(BK_ERROR_LOCATION "pMaterial is null");

	if (BK_ISNULL(pMaterial->pixelShader) || BK_ISNULL(pMaterial->vertexShader))
		return BkError(BK_ERROR_LOCATION "Invalid pixel or vertex shader");

	_BkGraphicsAPI_CreateShaderProgram(&(pMaterial->api), pMaterial->vertexShader->api, pMaterial->pixelShader->api);

	return BK_SUCCESS;
}