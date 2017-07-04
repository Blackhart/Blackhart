#include "core\BkMaterial.h"
#include "core\BkList.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void	_BkGetShader(BkShader** ppShader, char const* pName);
extern void	(*_BkCompileGraphicsAPIShader)(BkMaterial** ppMaterial);

// ~~~~~ Def(ALL) ~~~~~

BkMaterial*	BkMaterial_Create(void)
{
	BkMaterial* lpMaterial = malloc(sizeof(BkMaterial));
	if (BK_ISNULL(lpMaterial))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpMaterial->pixelShader = NULL;
	lpMaterial->vertexShader = NULL;

	return lpMaterial;
}

void	BkMaterial_Release(BkMaterial** ppMaterial)
{
	if (BK_ISNULL(ppMaterial))
		return (void)BkWarning(BK_ERROR_LOCATION "ppMaterial is null");

	(*ppMaterial)->pixelShader = NULL;
	(*ppMaterial)->vertexShader = NULL;

	free(*ppMaterial);
	*ppMaterial = NULL;
}

BkResult	BkMaterial_AttachShader(BkMaterial** ppMaterial, char const* pShaderName)
{
	if (BK_ISNULL(ppMaterial))
		BkDie(BK_ERROR_LOCATION "ppMaterial is null");
	if (BK_ISNULL(pShaderName))
		BkDie(BK_ERROR_LOCATION "pShaderName is null");

	BkShader*	lpShader = NULL; // 4 bytes
	_BkGetShader(&lpShader, pShaderName);
	if (BK_ISNULL(lpShader))
		return BkError(BK_ERROR_LOCATION "Invalid shader name");

	switch (lpShader->type)
	{
	case _BK_VERTEX_SHADER_:
		(*ppMaterial)->vertexShader = lpShader;
		break;
	case _BK_PIXEL_SHADER_:
		(*ppMaterial)->pixelShader = lpShader;
		break;
	default:
		return BkError(BK_ERROR_LOCATION "Invalid shader type");
	}

	return BK_SUCCESS;
}

BkResult	BkMaterial_CompileShader(BkMaterial** ppMaterial)
{
	if (BK_ISNULL(ppMaterial))
		BkDie(BK_ERROR_LOCATION "ppMaterial is null");

	if (BK_ISNULL((*ppMaterial)->pixelShader) || BK_ISNULL((*ppMaterial)->vertexShader))
		return BkError(BK_ERROR_LOCATION "Invalid pixel or vertex shader");

	_BkCompileGraphicsAPIShader(ppMaterial);

	return BK_SUCCESS;
}