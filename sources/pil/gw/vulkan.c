#include "gw.h"
#include "../../../includes/pil/gw/vulkan.h"

static VkInstance	__vkInstance = NULL;

// ~~~~~ Dcl(INTERNAL | PRIVATE) ~~~~~

extern void	Initialize_VkApplicationInfo(VkApplicationInfo*);

// ~~~~~ Def(ALL) ~~~~~

void	GwInitialize(void)
{
	VkApplicationInfo lInfo;
	Initialize_VkApplicationInfo(&lInfo);
}

void	GwUninitialize(void)
{

}

void	Initialize_VkApplicationInfo(VkApplicationInfo* ptr)
{
	ptr->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ptr->pApplicationName = "";
	ptr->applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	ptr->pEngineName = "Blackhart Engine | Vulkan Renderer";
	ptr->engineVersion = VK_MAKE_VERSION(0, 1, 0);
	ptr->apiVersion = VK_API_VERSION_1_0;
}