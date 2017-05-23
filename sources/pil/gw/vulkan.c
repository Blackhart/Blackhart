#include "../includes/pil/gw/gw.h"
#include "../../../includes/pil/gw/vulkan.h"

static VkInstance	__vkInstance = NULL;

// ~~~~~ Dcl(INTERNAL | PRIVATE) ~~~~~

extern void	Initialize_VkApplicationInfo(VkApplicationInfo* const);
extern void	Initialize_VkInstanceCreateInfo(VkInstanceCreateInfo* const, VkApplicationInfo const* const, char const* const pExtensions, uint8 const pExtensionCount);

// ~~~~~ Def(ALL) ~~~~~

void	GwInitialize(char const* const pExtensions, uint8 const pExtensionCount)
{
	VkApplicationInfo lAppInfo;
	VkInstanceCreateInfo lInstInfo;
	Initialize_VkApplicationInfo(&lAppInfo);
	Initialize_VkInstanceCreateInfo(&lInstInfo, &lAppInfo, pExtensions, pExtensionCount);
	VkResult lResult = vkCreateInstance(&lInstInfo, NULL, &__vkInstance);
	if (lResult != VK_SUCCESS)
		return;
}

void	GwUninitialize(void)
{
	vkDestroyInstance(__vkInstance, NULL);
}

void	Initialize_VkApplicationInfo(VkApplicationInfo* const ptr)
{
	ptr->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ptr->pEngineName = "Blackhart Engine | Vulkan Renderer";
	ptr->engineVersion = VK_MAKE_VERSION(0, 1, 0);
	ptr->apiVersion = VK_API_VERSION_1_0;
}

void	Initialize_VkInstanceCreateInfo(VkInstanceCreateInfo* const ptr, VkApplicationInfo const* const pAppInfo, char const* const pExtensions, uint8 const pExtensionCount)
{
	ptr->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ptr->pApplicationInfo = pAppInfo;
	ptr->enabledExtensionCount = pExtensionCount;
	ptr->ppEnabledExtensionNames = pExtensions;
	ptr->enabledLayerCount = 0;
}