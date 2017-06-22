#include "Blackhart.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern BkResult	GwInitialize();
extern void		GwUninitialize(void);
extern BkResult	LgInitialize(void);
extern BkResult	LgUninitialize(void);

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkInitialize()
{
	BkResult	lResult = BK_SUCCESS; // 1 byte

	lResult = LgInitialize();
	if (BK_FAILED(lResult))
		return lResult;

	lResult = GwInitialize();
	if (BK_FAILED(lResult))
		return lResult;
	
	return BK_SUCCESS;
}

void	BkUninitialize(void)
{
	LgUninitialize();
	GwUninitialize();
}