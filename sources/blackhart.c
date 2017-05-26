#include "blackhart.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	GwInitialize(BkGraphicsInfo const* const);
extern void	GwUninitialize();

// ~~~~~ Def(ALL) ~~~~~

void	BkInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	GwInitialize(pGraphicsInfo);
}

void	BkUninitialize()
{
	GwUninitialize();
}