#include "Blackhart.h"
#include "pil\BkGraphicWrapper.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	GwInitialize(BkGraphicsInfo const* const);
extern void	GwUninitialize(void);
extern void	FsInitialize(void);
extern void	FsUninitialize(void);

// ~~~~~ Def(ALL) ~~~~~

void	BkInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	FsInitialize();
	GwInitialize(pGraphicsInfo);
}

void	BkUninitialize(void)
{
	FsUninitialize();
	GwUninitialize();
}