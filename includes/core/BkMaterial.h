#ifndef __BK_MATERIAL_H__
#define __BK_MATERIAL_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "BkShader.h"

struct sMaterial
{
	BkShader const*	vertexShader;
	BkShader const*	pixelShader;
	void*			api;
};

typedef struct sMaterial	BkMaterial;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BkMaterial*	BkMaterial_Create(void);
extern void			BkMaterial_Release(BkMaterial** ppMaterial);
extern BkResult		BkMaterial_AttachShader(BkMaterial* pMaterial, BkShader const* pShader);
extern BkResult		BkMaterial_CompileShader(BkMaterial* pMaterial);

#endif