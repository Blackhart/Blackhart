#include "Blackhart.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

extern void		_BkLoadGraphicsAPI(void);
extern BkResult	(*_BkInitializeGraphicsAPI)(void);
extern void		(*_BkUninitializeGraphicsAPI)(void);
extern BkResult	_BkInitializeLogger(void);
extern BkResult	_BkUninitializeLogger(void);

// ~~~~~ Def(ALL) ~~~~~

BkResult	BkInitialize()
{
	if (BK_ERROR(_BkInitializeLogger()))
		return BK_FAILURE;

	_BkLoadGraphicsAPI();

	if (BK_ERROR(_BkInitializeGraphicsAPI()))
		return BkError(BK_ERROR_LOCATION "Failed to initialize the graphics API!");
	
	return BK_SUCCESS;
}

void	BkUninitialize(void)
{
	_BkUninitializeLogger();
	_BkUninitializeGraphicsAPI();
}