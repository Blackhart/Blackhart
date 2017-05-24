#include "../includes/blackhart.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	GwInitialize(char const* const pExtensions, uint8 const pExtensionCount);
extern void	GwUninitialize();

// ~~~~~ Def(ALL) ~~~~~

void	BkInitialize()
{
	GwInitialize(NULL, 0);
}

void	BkUninitialize()
{
	GwUninitialize();
}