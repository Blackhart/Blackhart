#ifndef __BK_MATERIAL_H__
#define __BK_MATERIAL_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "BkShader.h"

struct sMaterial
{
	BkShader*	vertexShader;
	BkShader*	pixelShader;
	void*		api;
};

typedef struct sMaterial	BkMaterial;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkMaterial*	BkMaterial_Create(void);
extern void			BkMaterial_Release(BkMaterial** ppMaterial);
extern BkResult		BkMaterial_AttachShader(BkMaterial** ppMaterial, char const* pShaderName);
extern BkResult		BkMaterial_CompileShader(BkMaterial** ppMaterial);

#endif