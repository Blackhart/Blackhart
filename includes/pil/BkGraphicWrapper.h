#ifndef __BK_GW_H__
#define __BK_GW_H__

#include "BkAtomicDataType.h"

enum eGraphicsAPI
{
	BK_GRAPHICS_API_VULKAN,
	BK_GRAPHICS_API_OPENGL,
	BK_GRAPHICS_API_DIRECTX
};

struct sGraphicsInfo
{
	char const* const*	extensions;
	uint32				extensionCount;
	enum eGraphicsAPI	api;
};

typedef struct sGraphicsInfo	BkGraphicsInfo;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	BkGetSupportedExtensions(uint32* const pExtensionCount, char*** pppExtensions);
extern void	BkGetSupportedExtensionCount(uint32* const pExtensionCount);

#endif