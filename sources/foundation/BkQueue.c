// Blackhart.foundation headers.
#include "foundation\BkQueue.h"

// ~~~~~ Def(PUBLIC) ~~~~~

void*	BkQueue_Front(struct BkQueue* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	if (BK_ISTRUE(BkQueue_Empty(obj)))
		return NULL;
	else
		return BkList_Data(BkList_Front(obj->list));
}

void*	BkQueue_Back(struct BkQueue* obj)
{
	BK_ASSERT(BK_ISNULL(obj));

	if (BK_ISTRUE(BkQueue_Empty(obj)))
		return NULL;
	else
		return BkList_Data(BkList_Back(obj->list));
}