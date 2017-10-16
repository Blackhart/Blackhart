#include <stdlib.h>

#include "core\BkList.h"
#include "core\BkLogger.h"

// ~~~~~ Def(ALL) ~~~~~

struct BkList*	BkList_Front(struct BkList const* list)
{
	if (BK_ISNULL(list))
		return NULL;

	while (!BK_ISNULL(BkList_Previous(list)))
	{
		list = BkList_Previous(list);
	}

	return list;
}

struct BkList*	BkList_Back(struct BkList const* list)
{
	if (BK_ISNULL(list))
		return NULL;

	while (!BK_ISNULL(BkList_Next(list)))
	{
		list = BkList_Next(list);
	}

	return list;
}

uint32	BkList_Size(struct BkList const* list)
{
	uint32 size = 0;
	list = BkList_Front(list);

	while (!BK_ISNULL(list))
	{
		size++;
		list = BkList_Next(list);
	}

	return size;
}

void	BkList_Clear(struct BkList* list)
{
	struct BkList* tmp = NULL;
	list = BkList_Front(list);

	while (!BK_ISNULL(list))
	{
		tmp = BkList_Next(list);
		free(list);
		list = tmp;
	}
}

struct BkList*	BkList_Get(struct BkList* list, uint32 const index)
{
	uint32 i = 0;
	list = BkList_Front(list);

	while (i < index)
	{
		list = BkList_Next(list);
		
		if (BK_ISNULL(list))
			return NULL;

		i++;
	}

	return list;
}

struct BkList*	BkList_Insert(struct BkList* list, void const* data, uint32 const index)
{
	struct BkList* tmp = list;

	list = BkList_Get(list, index);

	if (BK_ISNULL(list))
		return BkList_PushBack(tmp, data);
	else
	{
		struct BkList* lpPrevious = BkList_Previous(list);

		list->previous = BkList_Alloc();
		list->previous->data = data;
		list->previous->next = list;
		list->previous->previous = lpPrevious;

		if (!BK_ISNULL(lpPrevious))
			lpPrevious->next = BkList_Previous(list);

		return BkList_Front(list);
	}
}

struct BkList*	BkList_Erase(struct BkList* list, void const* data)
{
	list = BkList_Front(list);

	while (!BK_ISNULL(list))
	{
		if (BkList_Data(list) == data)
		{
			return BkList_EraseLink(list);
		}

		list = BkList_Next(list);
	}

	return BkList_Front(list);
}

struct BkList*	BkList_EraseLink(struct BkList* link)
{
	struct BkList* previous = BkList_Previous(link);
	struct BkList* next = BkList_Next(link);

	free(link);

	if (!BK_ISNULL(next))
		next->previous = previous;

	if (!BK_ISNULL(previous))
		previous->next = next;

	return BkList_Front(previous != NULL ? previous : next);
}

struct BkList*	BkList_PushFront(struct BkList* list, void const* data)
{
	list = BkList_Front(list);

	if (BK_ISNULL(list))
	{
		list = BkList_Alloc();
		list->data = data;
		return list;
	}
	else
	{
		list->previous = BkList_Alloc();
		list->previous->data = data;
		list->previous->next = list;
		return BkList_Previous(list);
	}
}

struct BkList*	BkList_PushBack(struct BkList* list, void const* data)
{
	list = BkList_Back(list);

	if (BK_ISNULL(list))
	{
		list = BkList_Alloc();
		list->data = data;
		return list;
	}
	else
	{
		list->next = BkList_Alloc();
		list->next->data = data;
		list->next->previous = list;
		return BkList_Front(list);
	}
}

struct BkList*	BkList_PopFront(struct BkList* list)
{
	list = BkList_Front(list);

	if (!BK_ISNULL(BkList_Next(list)))
	{
		list = BkList_Next(list);
		free(BkList_Previous(list));
		list->previous = NULL;
	}
	else
	{
		free(list);
		list = NULL;
	}

	return list;
}

struct BkList*	BkList_PopBack(struct BkList* list)
{
	list = BkList_Back(list);

	if (!BK_ISNULL(BkList_Previous(list)))
	{
		list = BkList_Previous(list);
		free(BkList_Next(list));
		list->next = NULL;
	}
	else
	{
		free(list);
		list = NULL;
	}

	return BkList_Front(list);
}

struct BkList*	BkList_Alloc(void)
{
	struct BkList* list = malloc(sizeof(struct BkList));

	if (BK_ISNULL(list))
		BkDie(BK_ERROR_LOCATION "Memory system failed to allocate memory block");

	list->data = NULL;
	list->next = NULL;
	list->previous = NULL;

	return list;
}