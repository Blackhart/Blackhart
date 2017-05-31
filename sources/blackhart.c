#include <assert.h>

#include "blackhart.h"
#include "pil\gw\gw.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	GwInitialize(GwGraphicsInfo const* const);
extern void	GwUninitialize(void);
extern void	GwGetSupportedExtensions(uint32* const pExtensionCount, char*** pppExtensions);
extern void	GwGetSupportedExtensionCount(uint32* const pExtensionCount);

// ~~~~~ Def(ALL) ~~~~~

void	BkInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	assert(pGraphicsInfo != NULL);
	assert(pGraphicsInfo->extensions == NULL && pGraphicsInfo->extensionCount > 0);

	GwInitialize(pGraphicsInfo);
}

void	BkUninitialize(void)
{
	GwUninitialize();
}

void	BkGetSupportedExtensions(uint32* const pExtensionCount, char*** pppExtensions)
{
	assert(*pppExtensions == NULL);

	GwGetSupportedExtensions(pExtensionCount, pppExtensions);
}

void	BkGetSupportedExtensionCount(uint32* const pExtensionCount)
{
	GwGetSupportedExtensionCount(pExtensionCount);
}