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
	enum eGraphicsAPI	api;
};

typedef struct sGraphicsInfo	BkGraphicsInfo;

// ~~~~~ Dcl(PUBLIC) ~~~~~

extern void	Render();

#endif