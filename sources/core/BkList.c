#include "core\BkList.h"
#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

void	BkSimpleLinkedList_Create(BkSimpleLinkedList** ppList, void* pElem)
{
	if (BK_ISNULL(ppList))
		BkDie(BK_ERROR_LOCATION "ppList == NULL");

	*ppList = malloc(sizeof(BkSimpleLinkedList));
	if (ppList == NULL)
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block!");
	(*ppList)->next = NULL;
	(*ppList)->elem = pElem;
}

void	BkSimpleLinkedList_PushBack(BkSimpleLinkedList** ppList, void* pElem)
{
	if (BK_ISNULL(ppList))
		BkDie(BK_ERROR_LOCATION "ppList == NULL");

	BkSimpleLinkedList*	lpList = NULL; // 4 bytes

	BkSimpleLinkedList_Create(&lpList, pElem);

	if (BK_ISNULL(*ppList))
	{
		(*ppList) = lpList;
		return;
	}

	while ((*ppList)->next != NULL)
		ppList = &(*ppList)->next;

	(*ppList)->next = lpList;
}

void	BkSimpleLinkedList_RemoveAll(BkSimpleLinkedList** ppList)
{
	if (BK_ISNULL(ppList))
		BkDie(BK_ERROR_LOCATION "ppList == NULL");

	if (BK_ISNULL(*ppList))
		return;

	BkSimpleLinkedList* lpCur = *ppList; // 4 bytes
	BkSimpleLinkedList* lpNext = NULL; // 4 bytes

	while (!BK_ISNULL(lpCur))
	{
		lpNext = lpCur->next;
		free(lpCur);
		lpCur = lpNext;
	}

	*ppList = NULL;
}

void	BkSimpleLinkedList_RemoveElem(BkSimpleLinkedList** ppList, void* ppElement)
{
	if (BK_ISNULL(ppList))
		BkDie(BK_ERROR_LOCATION "ppList == NULL");
	if (BK_ISNULL(ppElement))
		BkDie(BK_ERROR_LOCATION "ppElement == NULL");

	BkSimpleLinkedList*	lpPrev = NULL; // 4 bytes
	BkSimpleLinkedList*	lpCur = *ppList; // 4 bytes

	while (!BK_ISNULL(lpCur))
	{
		if (lpCur->elem == ppElement)
		{
			if (BK_ISNULL(lpPrev))
				*ppList = lpCur->next;
			else
				lpPrev->next = lpCur->next;
			free(lpCur);
			return;
		}

		lpPrev = lpCur;
		lpCur = lpCur->next;
	}
}

BkResult	BkSimpleLinkedList_Get(BkSimpleLinkedList const* pList, void** ppElement, uint32 const pIndex)
{
	if (BK_ISNULL(ppElement))
		BkDie(BK_ERROR_LOCATION "ppElement == NULL");

	uint32 lLength = 0; // 4 bytes
	BkSimpleLinkedList_Length(pList, &lLength);
	if (lLength <= pIndex)
		return BkError(BK_ERROR_LOCATION "pIndex > Linked list length");

	uint32	lIndex = 0; // 4 bytes
	while (!BK_ISNULL(pList))
	{
		if (lIndex == pIndex)
		{
			(*ppElement) = pList->elem;
			return BK_SUCCESS;
		}
		lIndex++;
		pList = pList->next;
	}

	(*ppElement) = NULL;
	return BK_SUCCESS;
}

void	BkSimpleLinkedList_Length(BkSimpleLinkedList const* pList, uint32* pLength)
{
	if (BK_ISNULL(pLength))
		BkDie(BK_ERROR_LOCATION "pLength == NULL");

	*pLength = 0;
	
	if (pList == NULL)
		return;

	while (pList != NULL)
	{
		*pLength++;
		pList = pList->next;
	}
}