#include "Blackhart.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern BkResult	GwInitialize();
extern void		GwUninitialize(void);
extern BkResult	LgInitialize(void);
extern BkResult	LgUninitialize(void);

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkInitialize()
{
	if (BK_FAILED(LgInitialize()))
		return BK_FAILURE;

	if (BK_FAILED(GwInitialize()))
		return BkError(BK_ERROR_LOCATION "Failed to initialize the graphics wrapper!");
	
	return BK_SUCCESS;
}

void	BkUninitialize(void)
{
	LgUninitialize();
	GwUninitialize();
}