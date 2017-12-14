#include "foundation\BkQueue.h"


// ~~~~~ Def(ALL) ~~~~~

void*	BkQueue_Front(struct BkQueue* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	if (BK_ISTRUE(BkQueue_Empty(queue)))
		return NULL;
	else
		return BkList_Data(BkList_Front(queue->list));
}

void*	BkQueue_Back(struct BkQueue* queue)
{
	BK_ASSERT(BK_ISNULL(queue));

	if (BK_ISTRUE(BkQueue_Empty(queue)))
		return NULL;
	else
		return BkList_Data(BkList_Back(queue->list));
}