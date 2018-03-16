// Standard headers.
#include <stdlib.h>

// Blackhart.foundation headers.
#include "foundation\BkError.h"
#include "foundation\BkList.h"
#include "foundation\BkLogger.h"

// ~~~~~ Def(PUBLIC) ~~~~~

struct BkList*	BkList_Front(struct BkList* obj)
{
	if (BK_ISNULL(obj))
		return NULL;

	while (!BK_ISNULL(BkList_Previous(obj)))
	{
		obj = BkList_Previous(obj);
	}

	return obj;
}

struct BkList*	BkList_Back(struct BkList* obj)
{
	if (BK_ISNULL(obj))
		return NULL;

	while (!BK_ISNULL(BkList_Next(obj)))
	{
		obj = BkList_Next(obj);
	}

	return obj;
}

uint32	BkList_Size(struct BkList* obj)
{
	uint32 size = 0;
	obj = BkList_Front(obj);

	while (!BK_ISNULL(obj))
	{
		size++;
		obj = BkList_Next(obj);
	}

	return size;
}

void	BkList_Clear(struct BkList* obj)
{
	struct BkList* tmp = NULL;
	obj = BkList_Front(obj);

	while (!BK_ISNULL(obj))
	{
		tmp = BkList_Next(obj);
		free(obj);
		obj = tmp;
	}
}

struct BkList*	BkList_Get(struct BkList* obj, uint32 const index)
{
	uint32 i = 0;
	obj = BkList_Front(obj);

	while (i < index)
	{
		obj = BkList_Next(obj);
		
		if (BK_ISNULL(obj))
			return NULL;

		i++;
	}

	return obj;
}

struct BkList*	BkList_Insert(struct BkList* obj, void* data, uint32 const index)
{
	struct BkList* tmp = obj;

	obj = BkList_Get(obj, index);

	if (BK_ISNULL(obj))
		return BkList_PushBack(tmp, data);
	else
	{
		struct BkList* lpPrevious = BkList_Previous(obj);

		obj->previous = BkList_Alloc();
		obj->previous->data = data;
		obj->previous->next = obj;
		obj->previous->previous = lpPrevious;

		if (!BK_ISNULL(lpPrevious))
			lpPrevious->next = BkList_Previous(obj);

		return BkList_Front(obj);
	}
}

struct BkList*	BkList_Erase(struct BkList* obj, void* data)
{
	obj = BkList_Front(obj);

	while (!BK_ISNULL(obj))
	{
		if (BkList_Data(obj) == data)
		{
			return BkList_EraseLink(obj);
		}

		obj = BkList_Next(obj);
	}

	return BkList_Front(obj);
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

struct BkList*	BkList_PushFront(struct BkList* obj, void* data)
{
	obj = BkList_Front(obj);

	if (BK_ISNULL(obj))
	{
		obj = BkList_Alloc();
		obj->data = data;
		return obj;
	}
	else
	{
		obj->previous = BkList_Alloc();
		obj->previous->data = data;
		obj->previous->next = obj;
		return BkList_Previous(obj);
	}
}

struct BkList*	BkList_PushBack(struct BkList* obj, void* data)
{
	obj = BkList_Back(obj);

	if (BK_ISNULL(obj))
	{
		obj = BkList_Alloc();
		obj->data = data;
		return obj;
	}
	else
	{
		obj->next = BkList_Alloc();
		obj->next->data = data;
		obj->next->previous = obj;
		return BkList_Front(obj);
	}
}

struct BkList*	BkList_PopFront(struct BkList* obj)
{
	obj = BkList_Front(obj);

	if (!BK_ISNULL(BkList_Next(obj)))
	{
		obj = BkList_Next(obj);
		free(BkList_Previous(obj));
		obj->previous = NULL;
	}
	else
	{
		free(obj);
		obj = NULL;
	}

	return obj;
}

struct BkList*	BkList_PopBack(struct BkList* obj)
{
	obj = BkList_Back(obj);

	if (!BK_ISNULL(BkList_Previous(obj)))
	{
		obj = BkList_Previous(obj);
		free(BkList_Next(obj));
		obj->next = NULL;
	}
	else
	{
		free(obj);
		obj = NULL;
	}

	return BkList_Front(obj);
}

struct BkList*	BkList_Alloc(void)
{
	struct BkList* list = malloc(sizeof(struct BkList));
	BK_ERROR(BK_ISNULL(list), "Memory system failed to allocate memory block");

	list->data = NULL;
	list->next = NULL;
	list->previous = NULL;

	return list;
}