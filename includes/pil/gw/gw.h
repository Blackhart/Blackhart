#ifndef __BK_GW_H__
#define __BK_GW_H__

#include "pil\adt.h"

enum eGraphicsAPI
{
	BK_GRAPHICS_API_VULKAN
};

struct sGraphicsInfo
{
	enum eGraphicsAPI	api;
	char const* const*	extensions;
	uint32				extensionCount;
};

typedef struct sGraphicsInfo	BkGraphicsInfo;

// ~~~~~ IMPL ~~~~~

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void		BkGetSupportedExtensions(char** const* const pExtensions);
extern void		BkGetSupportedExtensionCount(uint32* const pExtensionCount);

#endif