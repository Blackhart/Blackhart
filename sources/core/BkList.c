#include <stdlib.h>

#include "core\BkList.h"
#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

BkList*	BkList_Front(BkList const* pList)
{
	if (BK_ISNULL(pList))
		return NULL;

	while (!BK_ISNULL(BkList_Previous(pList)))
	{
		pList = BkList_Previous(pList);
	}

	return pList;
}

BkList*	BkList_Back(BkList const* pList)
{
	if (BK_ISNULL(pList))
		return NULL;

	while (!BK_ISNULL(BkList_Next(pList)))
	{
		pList = BkList_Next(pList);
	}

	return pList;
}

uint32	BkList_Size(BkList const* pList)
{
	uint32 lSize = 0;
	pList = BkList_Front(pList);

	while (!BK_ISNULL(pList))
	{
		lSize++;
		pList = BkList_Next(pList);
	}

	return lSize;
}

void	BkList_Clear(BkList* pList)
{
	BkList* lpListP = NULL;
	pList = BkList_Front(pList);

	while (!BK_ISNULL(pList))
	{
		lpListP = BkList_Next(pList);
		free(pList);
		pList = lpListP;
	}
}

BkList*	BkList_Get(BkList* pList, uint32 const index)
{
	uint32 lIndex = 0;
	pList = BkList_Front(pList);

	while (lIndex < index)
	{
		pList = BkList_Next(pList);
		
		if (BK_ISNULL(pList))
			return NULL;

		lIndex++;
	}

	return pList;
}

BkList*	BkList_Insert(BkList* pList, void const* pData, uint32 const index)
{
	BkList* lpList = pList;

	pList = BkList_Get(pList, index);

	if (BK_ISNULL(pList))
		return BkList_PushBack(lpList, pData);
	else
	{
		BkList* lpPrevious = BkList_Previous(pList);

		pList->previous = BkList_Alloc();
		pList->previous->elem = pData;
		pList->previous->next = pList;
		pList->previous->previous = lpPrevious;

		if (!BK_ISNULL(lpPrevious))
			lpPrevious->next = BkList_Previous(pList);

		return BkList_Front(pList);
	}
}

BkList*	BkList_Erase(BkList* pList, void const* pData)
{
	pList = BkList_Front(pList);

	while (!BK_ISNULL(pList))
	{
		if (BkList_Data(pList) == pData)
		{
			return BkList_EraseLink(pList);
		}

		pList = BkList_Next(pList);
	}

	return BkList_Front(pList);
}

BkList*	BkList_EraseLink(BkList* pLink)
{
	BkList* lpPrevious = BkList_Previous(pLink);
	BkList* lpNext = BkList_Next(pLink);

	free(pLink);

	if (!BK_ISNULL(lpNext))
		lpNext->previous = lpPrevious;

	if (!BK_ISNULL(lpPrevious))
		lpPrevious->next = lpNext;

	return BkList_Front(lpPrevious != NULL ? lpPrevious : lpNext);
}

BkList*	BkList_PushFront(BkList* pList, void const* pData)
{
	pList = BkList_Front(pList);

	if (BK_ISNULL(pList))
	{
		pList = BkList_Alloc();
		pList->elem = pData;
		return pList;
	}
	else
	{
		pList->previous = BkList_Alloc();
		pList->previous->elem = pData;
		pList->previous->next = pList;
		return BkList_Previous(pList);
	}
}

BkList*	BkList_PushBack(BkList* pList, void const* pData)
{
	pList = BkList_Back(pList);

	if (BK_ISNULL(pList))
	{
		pList = BkList_Alloc();
		pList->elem = pData;
		return pList;
	}
	else
	{
		pList->next = BkList_Alloc();
		pList->next->elem = pData;
		pList->next->previous = pList;
		return BkList_Front(pList);
	}
}

BkList*	BkList_PopFront(BkList* pList)
{
	pList = BkList_Front(pList);

	if (!BK_ISNULL(BkList_Next(pList)))
	{
		pList = BkList_Next(pList);
		free(BkList_Previous(pList));
		pList->previous = NULL;
	}
	else
	{
		free(pList);
		pList = NULL;
	}

	return pList;
}

BkList*	BkList_PopBack(BkList* pList)
{
	pList = BkList_Back(pList);

	if (!BK_ISNULL(BkList_Previous(pList)))
	{
		pList = BkList_Previous(pList);
		free(BkList_Next(pList));
		pList->next = NULL;
	}
	else
	{
		free(pList);
		pList = NULL;
	}

	return BkList_Front(pList);
}

BkList*	BkList_Alloc(void)
{
	BkList* lpList = malloc(sizeof(BkList));

	if (BK_ISNULL(lpList))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	lpList->elem = NULL;
	lpList->next = NULL;
	lpList->previous = NULL;

	return lpList;
}