#ifndef __BK_MATERIAL_H__
#define __BK_MATERIAL_H__

#include "pil\BkAtomicDataType.h"
#include "BkError.h"
#include "BkShader.h"

#include "pil\__BkExport.h"

struct sMaterial
{
	BkShader const*	vertexShader;
	BkShader const*	pixelShader;
	void*			api;
};

typedef struct sMaterial	BkMaterial;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern BK_API BkMaterial*	BkMaterial_Create(void);
extern BK_API void			BkMaterial_Release(BkMaterial** ppMaterial);
extern BK_API BkResult		BkMaterial_AttachShader(BkMaterial* pMaterial, BkShader const* pShader);
extern BK_API BkResult		BkMaterial_CompileShader(BkMaterial* pMaterial);

#endif