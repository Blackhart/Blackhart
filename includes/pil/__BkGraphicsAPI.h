#ifndef __INTERNAL_BK_GRAPHICSAPI_H__
#define __INTERNAL_BK_GRAPHICSAPI_H__

#include "core\BkError.h"

extern void	_BkGraphicsAPI_Load(void);
extern BkResult	(*_BkGraphicsAPI_Initialize)(void);
extern void	(*_BkGraphicsAPI_Uninitialize)(void);
extern void	(*_BkGraphicsAPI_Render)(void);

#endif
