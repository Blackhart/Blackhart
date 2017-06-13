#include "Blackhart.h"
#include "pil\BkGraphicWrapper.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern int8	GwInitialize(BkGraphicsInfo const* const);
extern void	GwUninitialize(void);
extern void	FsInitialize(void);
extern void	FsUninitialize(void);

// ~~~~~ Def(ALL) ~~~~~

int8	BkInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	FsInitialize();
	if (GwInitialize(pGraphicsInfo) != 0)
		return -1;
}

void	BkUninitialize(void)
{
	FsUninitialize();
	GwUninitialize();
}