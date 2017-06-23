#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "pil\BkGraphicsWrapper.h"
#include "pil\BkVulkan.h"

// ~~~~~ Dcl(PROTECTED) ~~~~~

extern BkResult	_BkInitializeVulkan(void);
extern void		_BkUninitializeVulkan(void);

// ~~~~~ Dcl(PRIVATE) ~~~~~

static VkInstance	__vkInstance = NULL;

static void	Initialize_VkApplicationInfo(VkApplicationInfo* const);
static void	Initialize_VkInstanceCreateInfo(VkApplicationInfo const* const, VkInstanceCreateInfo* const, char const* const* pExtensions, uint8 const pExtensionCount);

// ~~~~~ Def(ALL) ~~~~~

BkResult	_BkInitializeVulkan()
{
	VkApplicationInfo		lAppInfo; // 28 bytes
	VkResult				lResult; // 4 bytes
	VkInstanceCreateInfo	lInstInfo; // 32 bytes

	Initialize_VkApplicationInfo(&lAppInfo);
//	Initialize_VkInstanceCreateInfo(&lAppInfo, &lInstInfo, pGraphicsInfo->extensions, pGraphicsInfo->extensionCount);

	lResult = vkCreateInstance(&lInstInfo, NULL, &__vkInstance);
	if (lResult != VK_SUCCESS)
		return BkError(BK_ERROR_LOCATION "Failed to initialize vulkan!\n");
	
	return BK_SUCCESS;
}

static void	Initialize_VkApplicationInfo(VkApplicationInfo* const pAppInfo)
{
	pAppInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	pAppInfo->pNext = NULL;
	pAppInfo->pApplicationName = NULL;
	pAppInfo->pEngineName = "Blackhart Engine | Vulkan Renderer";
	pAppInfo->engineVersion = VK_MAKE_VERSION(0, 1, 0);
	pAppInfo->apiVersion = VK_API_VERSION_1_0;
}

static void	Initialize_VkInstanceCreateInfo(VkApplicationInfo const* const pAppInfo, VkInstanceCreateInfo* const pInstInfo, char const* const* ppExtensions, uint8 const ExtensionCount)
{
	pInstInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	pInstInfo->pNext = NULL;
	pInstInfo->flags = 0;
	pInstInfo->pApplicationInfo = pAppInfo;
	pInstInfo->enabledExtensionCount = ExtensionCount;
	pInstInfo->ppEnabledExtensionNames = ppExtensions;
	pInstInfo->enabledLayerCount = 0;
	pInstInfo->ppEnabledLayerNames = NULL;
}

void	_BkUninitializeVulkan(void)
{
	vkDestroyInstance(__vkInstance, NULL);
}

void	BkGetSupportedExtensions(uint32* const pExtensionCount, char*** pppExtensions)
{
	VkExtensionProperties* lpExtensionsProp = NULL; // 4 bytes

	// Get supported extensions count
	BkGetSupportedExtensionCount(pExtensionCount);

	// Allocate memory block for the extension properties
	lpExtensionsProp = malloc(*pExtensionCount * sizeof(VkExtensionProperties));
	if (lpExtensionsProp == NULL)
		goto error;

	// Allocate memory block for the extensions array to return
	*pppExtensions = malloc(*pExtensionCount * sizeof(char*));
	if (*pppExtensions == NULL)
		goto cleanup_lpExtensionsProp;

	// Retrieve the list of extension properties supported by the device
	vkEnumerateInstanceExtensionProperties(NULL, pExtensionCount, lpExtensionsProp);

	for (uint32 lIndex = 0; lIndex < *pExtensionCount; ++lIndex)
	{
		// Get the length of the extension name
		size_t lLength = strlen(lpExtensionsProp[lIndex].extensionName) + 1;

		// Allocate memory block for the extension name
		(*pppExtensions)[lIndex] = malloc(lLength * sizeof(char));
		if ((*pppExtensions)[lIndex] == NULL)
			goto cleanup_pppExtensions;

		// Copy enxtension name from the extension property struct to the extensions array to return
		memcpy((*pppExtensions)[lIndex], lpExtensionsProp[lIndex].extensionName, lLength);
		(*pppExtensions)[lIndex][lLength] = '\0';
	}

	// Return the extensions array
	free(lpExtensionsProp);
	return;

cleanup_pppExtensions:
	for (uint32 i = 0; i < *pExtensionCount && (*pppExtensions)[i] != NULL; ++i)
			free((*pppExtensions)[i]);
	free(*pppExtensions);

cleanup_lpExtensionsProp:
	free(lpExtensionsProp);

error:
	return;
}

void	BkGetSupportedExtensionCount(uint32* const pExtensionCount)
{
	vkEnumerateInstanceExtensionProperties(NULL, pExtensionCount, NULL);
}