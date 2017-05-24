#include <stdlib.h>
#include <stdio.h>

#include "../includes/pil/gw/gw.h"
#include "../../../includes/pil/gw/vulkan.h"
#include "../../../includes/pil/adt.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern void	GwInitialize(BkGraphicsInfo const* const);
extern void	GwUninitialize();

// ~~~~~ Dcl(PRIVATE) ~~~~~

static VkInstance	__vkInstance = NULL;

static void	Initialize_VkApplicationInfo(VkApplicationInfo* const);
static void	Initialize_VkInstanceCreateInfo(VkInstanceCreateInfo* const, VkApplicationInfo const* const, char const* const* pExtensions, uint8 const pExtensionCount);

// ~~~~~ Def(ALL) ~~~~~

void	GwInitialize(BkGraphicsInfo const* const pGraphicsInfo)
{
	VkApplicationInfo lAppInfo;
	VkInstanceCreateInfo lInstInfo;
	Initialize_VkApplicationInfo(&lAppInfo);
	Initialize_VkInstanceCreateInfo(&lInstInfo, &lAppInfo, pGraphicsInfo->extensions, pGraphicsInfo->extensionCount);
	VkResult lResult = vkCreateInstance(&lInstInfo, NULL, &__vkInstance);
	if (lResult != VK_SUCCESS)
		return;
}

void	GwUninitialize()
{
	vkDestroyInstance(__vkInstance, NULL);
}

void	BkGetSupportedExtensions(char** const* const dst)
{
	VkExtensionProperties*	lExtensions = NULL;
	uint32	lExtensionCount = 0;

	BkGetSupportedExtensionCount(&lExtensionCount);
	lExtensions = malloc(lExtensionCount * sizeof(VkExtensionProperties));
	if (lExtensions == NULL)
		return;
	vkEnumerateInstanceExtensionProperties(NULL, &lExtensionCount, lExtensions);
	for (uint32 lIndex = 0; lIndex < lExtensionCount; ++lIndex)
		(*dst)[lIndex] = lExtensions[lIndex].extensionName;
	for (uint32 lIndex = 0; lIndex < lExtensionCount; ++lIndex)
		printf("%s\n", (*dst)[lIndex]);
	free(lExtensions);
}

void	BkGetSupportedExtensionCount(uint32* const pExtensionCount)
{
	vkEnumerateInstanceExtensionProperties(NULL, pExtensionCount, NULL);
}

static void	Initialize_VkApplicationInfo(VkApplicationInfo* const ptr)
{
	ptr->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ptr->pNext = NULL;
	ptr->pApplicationName = NULL;
	ptr->pEngineName = "Blackhart Engine | Vulkan Renderer";
	ptr->engineVersion = VK_MAKE_VERSION(0, 1, 0);
	ptr->apiVersion = VK_API_VERSION_1_0;
}

static void	Initialize_VkInstanceCreateInfo(VkInstanceCreateInfo* const ptr, VkApplicationInfo const* const pAppInfo, char const* const* pExtensions, uint8 const pExtensionCount)
{
	ptr->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ptr->pNext = NULL;
	ptr->flags = 0;
	ptr->pApplicationInfo = pAppInfo;
	ptr->enabledExtensionCount = pExtensionCount;
	ptr->ppEnabledExtensionNames = pExtensions;
	ptr->enabledLayerCount = 0;
	ptr->ppEnabledLayerNames = NULL;
}