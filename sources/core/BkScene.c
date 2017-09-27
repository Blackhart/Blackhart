#include "core\BkScene.h"

// ~~~~~ Dcl(INTERNAL) ~~~~~

static BkSimpleLinkedList* __BkScene_Entities = NULL;

// ~~~~~ Def(ALL) ~~~~~

void	BkScene_AddEntity(BkEntity* pEntity)
{
	if (BK_ISNULL(pEntity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	BkSimpleLinkedList_PushBack(&__BkScene_Entities, pEntity);
}

void	BkScene_RemoveEntity(BkEntity* pEntity)
{
	if (BK_ISNULL(pEntity))
	{
		BK_ERROR(BK_ERROR_LOCATION "pEntity == NULL");
		return;
	}

	BkSimpleLinkedList_RemoveElem(&__BkScene_Entities, pEntity);
}

BkSimpleLinkedList const*	BkScene_GetEntities(void)
{
	return __BkScene_Entities;
}