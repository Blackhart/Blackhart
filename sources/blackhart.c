#include "Blackhart.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern int8	GwInitialize(BkGraphicsInfo const* const);
extern void	GwUninitialize(void);
extern void	LgInitialize(void);
extern void	LgUninitialize(void);

// ~~~~~ Def(ALL) ~~~~~

int8	BkInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	LgInitialize();
	if (GwInitialize(pGraphicsInfo) != 0)
		return -1;
	return 0;
}

void	BkUninitialize(void)
{
	LgUninitialize();
	GwUninitialize();
}